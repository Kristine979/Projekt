#include "stm32f30x.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"
#include <stdint.h>
#include "accelerometer.h"

/* ===== MMA7660 (accelerometer) constants ===== */
#define MMA_ADDR   (0x98)   // I2C address of MMA7660 (shifted format)
#define REG_X      0x00          // sensor register for X axis
#define REG_Y      0x01          // sensor register for Y axis
#define REG_Z      0x02          // sensor register for Z axis
#define REG_MODE   0x07          // sensor register for MODE (sleep/active)

/* ===== I2C timing (speed setup) ===== */
#define I2C_TIMING  0x00B01A4B   // I2C TIMINGR value (sets ~100kHz etc.)

/* ===== simple delay ===== */
void acc_delay_ms(int ms) {
    volatile uint32_t n = (SystemCoreClock/8000) * (uint32_t)ms; // rough loop count
    while (n--) __NOP();                                        // do nothing, just wait
}

/* ===== small "wait" helpers (makes code easier to read) ===== */
static void wait_not_busy(void) {
    while (I2C1->ISR & I2C_ISR_BUSY) { }        // wait until I2C bus is free
}

static void clear_i2c_flags(void) {
    I2C1->ICR = 0x3F38;                         // clear old STOP/NACK/ERR flags
}

static void wait_txis(void) {
    while (!(I2C1->ISR & I2C_ISR_TXIS)) { }     // wait until we can write next byte
}

static void wait_rxne(void) {
    while (!(I2C1->ISR & I2C_ISR_RXNE)) { }     // wait until a byte is received
}

static void wait_tc(void) {
    while (!(I2C1->ISR & I2C_ISR_TC)) { }       // wait until transfer stage is complete
}

static void wait_stop_and_clear(void) {
    while (!(I2C1->ISR & I2C_ISR_STOPF)) { }    // wait until STOP happened
    I2C1->ICR = I2C_ICR_STOPCF;                 // clear STOP flag
}

/* ===== init I2C pins + I2C peripheral ===== */
static void i2c1_init(void) {

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE); // enable clock for GPIOB
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,  ENABLE); // enable clock for I2C1

    GPIO_InitTypeDef g;                                // structure for pin setup
    g.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9;             // PB8=SCL and PB9=SDA
    g.GPIO_Mode  = GPIO_Mode_AF;                        // Alternate Function mode (not normal GPIO)
    g.GPIO_OType = GPIO_OType_OD;                       // Open-Drain (I2C needs this)
    g.GPIO_PuPd  = GPIO_PuPd_UP;                        // Pull-up (I2C needs pull-ups)
    g.GPIO_Speed = GPIO_Speed_50MHz;                    // pin speed
    GPIO_Init(GPIOB, &g);                               // apply setup to port B

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_4); // PB8 uses AF4 = I2C1 SCL
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_4); // PB9 uses AF4 = I2C1 SDA

    I2C1->CR1 &= ~I2C_CR1_PE;                           // disable I2C before changing timing
    I2C1->TIMINGR = I2C_TIMING;                         // set I2C speed / timing
    I2C1->CR1 = I2C_CR1_PE;                             // enable I2C (PE = 1)
}

/* ===== write: send (reg, val) to the sensor ===== */
static void i2c_write_reg(uint8_t reg, uint8_t val) {

    wait_not_busy();                                    // wait bus free
    clear_i2c_flags();                                  // clear old flags

    I2C1->CR2 = (MMA_ADDR)                              // target sensor address
              | (2u << 16)                              // send 2 bytes (reg + val)
              | I2C_CR2_AUTOEND                         // auto STOP after bytes sent
              | I2C_CR2_START;                          // generate START now

    wait_txis(); I2C1->TXDR = reg;                      // byte 1: which sensor register
    wait_txis(); I2C1->TXDR = val;                      // byte 2: value for that register

    wait_stop_and_clear();                              // wait STOP and clear it
}

/* ===== read: first write register index, then read one byte ===== */
static uint8_t i2c_read_reg(uint8_t reg) {

    uint8_t v;                                          // here we will store received byte

    wait_not_busy();                                    // wait bus free
    clear_i2c_flags();                                  // clear old flags

    /* step 1: write 1 byte = register index (no STOP yet) */
    I2C1->CR2 = (MMA_ADDR)                              // target sensor address
              | (1u << 16)                              // send 1 byte
              | I2C_CR2_START;                          // START (write mode by default)

    wait_txis(); I2C1->TXDR = reg;                      // send register number
    wait_tc();                                          // wait stage complete (no STOP)

    /* step 2: read 1 byte from that register (with STOP at end) */
    I2C1->CR2 = (MMA_ADDR)                              // target sensor address
              | (1u << 16)                              // read 1 byte
              | I2C_CR2_RD_WRN                           // set direction = READ
              | I2C_CR2_AUTOEND                          // auto STOP after read
              | I2C_CR2_START;                           // repeated START

    wait_rxne(); v = (uint8_t)I2C1->RXDR;               // read received byte
    wait_stop_and_clear();                              // wait STOP and clear it

    return v;                                           // return the byte to caller
}

/* ===== MMA7660 gives 6-bit signed values, convert to normal int8 ===== */
static int8_t decode_mma6(uint8_t raw) {
    raw &= 0x3F;                                        // keep only lower 6 bits
    if (raw & 0x20) raw |= 0xC0;                        // if sign bit set, extend sign
    return (int8_t)raw;                                 // now it's -32..31 (roughly)
}

/* ===== public: init sensor ===== */
void acc_init(void) {

    i2c1_init();                                        // setup pins + I2C hardware
    i2c_write_reg(REG_MODE, 0x01);                      // MODE=1 -> sensor active
    acc_delay_ms(10);                                   // small wait after enabling
}

/* ===== public: return 0 (still) or 1 (moving) ===== */
int acc_motion_bit(void) {

    static int8_t px = 0, py = 0, pz = 0;               // previous X/Y/Z (kept between calls)

    int8_t x = decode_mma6(i2c_read_reg(REG_X));         // read + decode X
    int8_t y = decode_mma6(i2c_read_reg(REG_Y));         // read + decode Y
    int8_t z = decode_mma6(i2c_read_reg(REG_Z));         // read + decode Z

    int dx = x - px; if (dx < 0) dx = -dx;              // abs difference for X
    int dy = y - py; if (dy < 0) dy = -dy;              // abs difference for Y
    int dz = z - pz; if (dz < 0) dz = -dz;              // abs difference for Z

    px = x; py = y; pz = z;                             // update "previous" values

    return (dx + dy + dz) > 20;                          // threshold: >4 means "moving"
}
