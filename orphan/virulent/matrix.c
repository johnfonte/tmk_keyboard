/* Copyright 2012 Jun Wako <wakojun@gmail.com>
 *
 * This is heavily based on phantom/board.{c|h}.
 * https://github.com/BathroomEpiphanies/AVR-Keyboard
 *
 * Copyright (c) 2012 Fredrik Atmer, Bathroom Epiphanies Inc
 * http://bathroomepiphanies.com
 *
 * As for liscensing consult with the original files or its author.
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	300
#endif
static uint8_t debouncing = DEBOUNCE;

// bit array of key state(1:on, 0:off)
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(void);
static void init_rows(void);
static void unselect_cols(void);
static void select_col(uint8_t col);

#ifndef SLEEP_LED_ENABLE
/* LEDs are on output compare pins OC1B OC1C
   This activates fast PWM mode on them.
   Prescaler 256 and 8-bit counter results in
   16000000/256/256 = 244 Hz blink frequency.
   LED_A: Caps Lock
   LED_B: Scroll Lock  */
/* Output on PWM pins are turned off when the timer 
   reaches the value in the output compare register,
   and are turned on when it reaches TOP (=256). */
static
void setup_leds(void)
{
    TCCR1A |=      // Timer control register 1A
        (1<<WGM10) | // Fast PWM 8-bit
        (1<<COM1B1)| // Clear OC1B on match, set at TOP
        (1<<COM1C1); // Clear OC1C on match, set at TOP
    TCCR1B |=      // Timer control register 1B
        (1<<WGM12) | // Fast PWM 8-bit
        (1<<CS12);   // Prescaler 256
    OCR1B = LED_BRIGHTNESS;    // Output compare register 1B
    OCR1C = LED_BRIGHTNESS;    // Output compare register 1C
    // LEDs: LED_A -> PORTB6, LED_B -> PORTB7
    DDRB  |= (1<<6) | (1<<7);
    PORTB  &= ~((1<<6) | (1<<7));
}
#endif

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    // To use PORTF disable JTAG with writing JTD bit twice within four cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);
	
    // initialize row and col
    unselect_cols();
    init_rows();
#ifndef SLEEP_LED_ENABLE
    // setup_leds();
#endif

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++)  {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {  // 0-16
        select_col(col);
        _delay_us(3);       // without this wait it won't read stable value.
        uint8_t rows = read_rows();
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {  // 0-5
            bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
            bool curr_bit = rows & (1<<row);
            if (prev_bit != curr_bit) {
                matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
                if (debouncing) {
                    dprint("bounce!: "); dprintf("%02X", debouncing); dprintln();
                }
                debouncing = DEBOUNCE;
            }
        }
        unselect_cols();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop32(matrix[i]);
    }
    return count;
}

/* Row pin configuration
 * row: 0   1   2   3   4   5
 * pin: D6  D7  E0  E1  C0  C1
 */
static void init_rows(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRD  &= ~0b11000000;
    PORTD |= 0b11000000;
    DDRE  &= ~0b00000011;
    PORTE |= 0b00000011;
    DDRC  &= ~0b00000011;
    PORTC |= 0b00000011;
}

static uint8_t read_rows(void)
{
    // return (PIND&(1<<6) ? 0 : (1<<0)) |
    //        (PIND&(1<<7) ? 0 : (1<<1)) |
    //        (PINE&(1<<0) ? 0 : (1<<2)) |
    //        (PINE&(1<<1) ? 0 : (1<<3)) |
    //        (PINC&(1<<0) ? 0 : (1<<4)) |
    //        (PINC&(1<<1) ? 0 : (1<<5));
    return (PINC&(1<<1) ? 0 : (1<<0)) |
           (PINC&(1<<0) ? 0 : (1<<1)) |
           (PINE&(1<<1) ? 0 : (1<<2)) |
           (PINE&(1<<0) ? 0 : (1<<3)) |
           (PIND&(1<<7) ? 0 : (1<<4)) |
           (PIND&(1<<6) ? 0 : (1<<5));
}

/* Column pin configuration
 * col: 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18
 * pin: B2  B1  B0  D4  D5  C2  C3  C4  C5  C6  C7  F0  F1  F2  F3  F4  F5  F6  F7
 */
static void unselect_cols(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRC  |= 0b11111100; // PC: 7 6 5 4 3 2
    PORTC |= 0b11111100;
    DDRD  |= 0b00110000; //PD: 5 4
    PORTD |= 0b00110000;
    // DDRE  |= 0b01000000; // PE: x
    // PORTE |= 0b01000000;
    DDRF  |= 0b11111111; // PF: 7 6 5 4 3 2 1 0
    PORTF |= 0b11111111;
    DDRB  |= 0b00000111; // PB: 2 1 0
    PORTB |= 0b00000111;
}

static void select_col(uint8_t col)
{
    // Output low(DDR:1, PORT:0) to select
    switch (col) {
        case 0:
            DDRB  |= (1<<2);
            PORTB &= ~(1<<2);
            break;
        case 1:
            DDRB  |= (1<<1);
            PORTB &= ~(1<<1);
            break;
        case 2:
            DDRB  |= (1<<0);
            PORTB &= ~(1<<0);
            break;
        case 3:
            DDRD  |= (1<<4);
            PORTD &= ~(1<<4);
            break;
        case 4:
            DDRD  |= (1<<5);
            PORTD &= ~(1<<5);
            break;
        case 5:
            DDRC  |= (1<<2);
            PORTC &= ~(1<<2);
            break;
        case 6:
            DDRC  |= (1<<3);
            PORTC &= ~(1<<3);
            break;
        case 7:
            DDRC  |= (1<<4);
            PORTC &= ~(1<<4);
            break;
        case 8:
            DDRC  |= (1<<5);
            PORTC &= ~(1<<5);
            break;
        case 9:
            DDRC  |= (1<<6);
            PORTC &= ~(1<<6);
            break;
        case 10:
            DDRC  |= (1<<7);
            PORTC &= ~(1<<7);
            break;
        case 11:
            DDRF  |= (1<<0);
            PORTF &= ~(1<<0);
            break;
        case 12:
            DDRF  |= (1<<1);
            PORTF &= ~(1<<1);
            break;
        case 13:
            DDRF  |= (1<<2);
            PORTF &= ~(1<<2);
            break;
        case 14:
            DDRF  |= (1<<3);
            PORTF &= ~(1<<3);
            break;
        case 15:
            DDRF  |= (1<<4);
            PORTF &= ~(1<<4);
            break;
        case 16:
            DDRF  |= (1<<5);
            PORTF &= ~(1<<5);
            break;
        case 17:
            DDRF  |= (1<<6);
            PORTF &= ~(1<<6);
            break;
        case 18:
            DDRF  |= (1<<7);
            PORTF &= ~(1<<7);
            break;
    }
}
