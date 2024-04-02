/*
 * File:   main.c
 * Author: Adrian
 *
 * Created on February 28, 2024, 10:57 AM
 */

// CONFIG
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include <stdlib.h>
#define _XTAL_FREQ 4000000

/* LEDs on PORT B:
 * 0   1   2
 *     3    
 * 4   5   6
 */

char number_pattern[] = {
0b00001000,
0b00010100,
0b00011100,
0b01010101,
0b01011101,
0b01110111
};

void delay_ms(unsigned int ms) {
    while (ms--) __delay_ms(1);
}

void throw_dice() {
    for (int i = 0; i < 100; i += 4) {
        PORTB = number_pattern[TMR0 % 6];
        delay_ms(i);
    }
}

void main(void) {
    TRISB = 0x00; // PORTB as output
    CMCON = 0x07; // Disable comparator
    OPTION_REG = 0b11000010; // Internal oscillator as timer0 source
    while(1) if (!(PORTA & 0x02)) throw_dice();
    return;
}
