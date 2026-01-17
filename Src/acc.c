/*
 * acc.c
 *
 *  Created on: 16. jan. 2026
 *      Author: carol
 */
/*
int main(void){
    uart_init(230400);
    acc_init();

    int fast = 1; // 1 = sidder fast, 0 = brudt løs

    while(1){
        int m = acc_motion_bit();   // 0 eller 1

        if (fast && m == 1) {
            fast = 0;              // bryd løs ved første bevægelse
        }

        // Udskriv begge (til debug)
        printf("motion=%d, fast=%d\r\n", m, fast);

        acc_delay_ms(100);
    }
}
*/
