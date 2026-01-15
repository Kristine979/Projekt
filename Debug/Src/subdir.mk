################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/30010_io.c \
../Src/ADC.c \
../Src/HighScore.c \
../Src/ansi.c \
../Src/charset.c \
../Src/clock.c \
../Src/lcd_write.c \
../Src/main.c \
../Src/menu.c \
../Src/screens.c \
../Src/ship.c \
../Src/sprites.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f30x.c \
../Src/window.c 

OBJS += \
./Src/30010_io.o \
./Src/ADC.o \
./Src/HighScore.o \
./Src/ansi.o \
./Src/charset.o \
./Src/clock.o \
./Src/lcd_write.o \
./Src/main.o \
./Src/menu.o \
./Src/screens.o \
./Src/ship.o \
./Src/sprites.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f30x.o \
./Src/window.o 

C_DEPS += \
./Src/30010_io.d \
./Src/ADC.d \
./Src/HighScore.d \
./Src/ansi.d \
./Src/charset.d \
./Src/clock.d \
./Src/lcd_write.d \
./Src/main.d \
./Src/menu.d \
./Src/screens.d \
./Src/ship.d \
./Src/sprites.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f30x.d \
./Src/window.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F302R8Tx -DSTM32F3 -DNUCLEO_F302R8 -DDEBUG -DUSE_STDPERIPH_DRIVER=1 -c -I"C:/Users/Bruger/Desktop/DTU/Programmeringsprojekt/Spil/Projekt/SPL/inc" -I"C:/Users/Bruger/Desktop/DTU/Programmeringsprojekt/Spil/Projekt/Inc" -I"C:/Users/Bruger/Desktop/DTU/Programmeringsprojekt/Spil/Projekt/cmsis" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/30010_io.d ./Src/30010_io.o ./Src/ADC.d ./Src/ADC.o ./Src/HighScore.d ./Src/HighScore.o ./Src/ansi.d ./Src/ansi.o ./Src/charset.d ./Src/charset.o ./Src/clock.d ./Src/clock.o ./Src/lcd_write.d ./Src/lcd_write.o ./Src/main.d ./Src/main.o ./Src/menu.d ./Src/menu.o ./Src/screens.d ./Src/screens.o ./Src/ship.d ./Src/ship.o ./Src/sprites.d ./Src/sprites.o ./Src/syscalls.d ./Src/syscalls.o ./Src/sysmem.d ./Src/sysmem.o ./Src/system_stm32f30x.d ./Src/system_stm32f30x.o ./Src/window.d ./Src/window.o

.PHONY: clean-Src

