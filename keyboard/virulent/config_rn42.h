/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H


/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0074
#define DEVICE_VER      0x0001
#define MANUFACTURER    t.m.k.
#define PRODUCT         Virulent
#define DESCRIPTION     t.m.k. keyboard firmware for Virulent


/* matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 19

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if need no debouncing */
#define DEBOUNCE    7

/* Set LED brightness 0-255.
 * This have no effect if sleep LED is enabled. */
#define LED_BRIGHTNESS  250

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* power control of key switch board */
#define HHKB_POWER_SAVING

/*
 * Hardware Serial(UART)
 *     Baud rate are calculated with round off(+0.5).
 */
#ifdef __AVR_AT90USB1286__
    #define SERIAL_UART_BAUD        115200
    #define SERIAL_UART_DATA        UDR1
    #define SERIAL_UART_UBRR        ((F_CPU/(16.0*SERIAL_UART_BAUD)-1+0.5))
    #define SERIAL_UART_RXD_VECT    USART1_RX_vect
    #define SERIAL_UART_TXD_READY   (UCSR1A&(1<<UDRE1))
    #define SERIAL_UART_INIT()      do { \
        cli(); \
        UBRR1L = (uint8_t) SERIAL_UART_UBRR;       /* baud rate */ \
        UBRR1H = ((uint16_t)SERIAL_UART_UBRR>>8);  /* baud rate */ \
        UCSR1A = (1<<U2X1); \
        UCSR1B |= (1<<RXCIE1) | (1<<RXEN1); /* RX interrupt, RX: enable */ \
        UCSR1B |= (0<<TXCIE1) | (1<<TXEN1); /* TX interrupt, TX: enable */ \
        UCSR1C |= (0<<UCSZ11) | (0<<UCSZ10);  /* parity: none(00), even(01), odd(11) */ \
        DDRE |= (1<<5); PORTE &= ~(1<<5);   /* RTS for flow control by firmware */ \
        sei(); \
    } while(0)
    #define SERIAL_UART_RTS_LO()    do { PORTE &= ~(1<<5); } while (0)
    #define SERIAL_UART_RTS_HI()    do { PORTE |=  (1<<5); } while (0)
#else
    #error "USART configuration is needed."
#endif


/* for debug */
#define SUART_OUT_PORT  PORTD
#define SUART_OUT_BIT   3
#define SUART_IN_PIN    PIND
#define SUART_IN_BIT    2


/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */
/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
