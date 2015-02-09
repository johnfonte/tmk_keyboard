#include <avr/io.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include "pjrc.h"
#include "usb.h"
#include "print.h"
#include "sendchar.h"
#include "rn42.h"
#include "rn42_task.h"
#include "serial.h"
#include "keyboard.h"
#include "keycode.h"
#include "action.h"
#include "action_util.h"
#include "wait.h"
#include "suart.h"
#include "suspend.h"

static int8_t sendchar_func(uint8_t c)
{
    xmit(c);        // SUART
    sendchar(c);    // PJRC
    return 0;
}

static void SetupHardware(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    clock_prescale_set(clock_div_1);

    usb_init();

    print_set_sendchar(sendchar_func);

    // SUART PD3:output, PD2:input
    DDRD |= (1<<3);
    PORTD |= (1<<3);
    DDRD &= ~(1<<2);
    PORTD |= (1<<2);
}

int main(void)  __attribute__ ((weak));
int main(void)
{
    SetupHardware();
    sei();

    /* wait for USB startup to get ready for debug output */
    uint8_t timeout = 255;  // timeout when USB is not available(Bluetooth)
    while (timeout-- && !usb_configured()) {
        wait_ms(4);
#if defined(INTERRUPT_CONTROL_ENDPOINT)
        ;
#endif
    }
    print("\nUSB init\n");

    rn42_init();
    rn42_task_init();
    print("RN-42 init\n");

    /* init modules */
    keyboard_init();

    if (!rn42_rts()) {
        host_set_driver(&rn42_driver);
    } else {
        host_set_driver(pjrc_driver());
    }

#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif

    print("Keyboard start\n");
    while (1) {
        while (rn42_rts() && // RN42 is off
                suspend) {
            print("[s]");
            matrix_power_down();
            suspend_power_down();
            suspend_power_down();
            suspend_power_down();
            suspend_power_down();
            suspend_power_down();
            suspend_power_down();
            suspend_power_down();
            if (remote_wakeup && suspend_wakeup_condition()) {
                    usb_remote_wakeup();
            }
        }

        keyboard_task();

#if !defined(INTERRUPT_CONTROL_ENDPOINT)
        USB_USBTask();
#endif

        rn42_task();
    }
}
