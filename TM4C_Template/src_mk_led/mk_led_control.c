/*
 * mk_led_control.c
 *
 *  Created on: Jan 3, 2019
 *      Author: alex.tran
 */

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

#include "mk_led_control.h"

led_struct led_1;
led_struct led_2;
led_struct led_3;
led_struct led_4;

void led_init(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

    led_1.gpio_base = GPIO_PORTN_BASE;
    led_1.gpio_pin = GPIO_PIN_1;
    led_1.pwm_time = 0;
    led_1.status = LED_OFF;

    led_2.gpio_base = GPIO_PORTN_BASE;
    led_2.gpio_pin = GPIO_PIN_0;
    led_2.pwm_time = 0;
    led_2.status = LED_OFF;

    led_3.gpio_base = GPIO_PORTF_BASE;
    led_3.gpio_pin = GPIO_PIN_4;
    led_3.pwm_time = 0;
    led_3.status = LED_OFF;

    led_4.gpio_base = GPIO_PORTF_BASE;
    led_4.gpio_pin = GPIO_PIN_0;
    led_4.pwm_time = 0;
    led_4.status = LED_OFF;

    GPIOPinTypeGPIOOutput(led_1.gpio_base, led_1.gpio_pin);
    GPIOPinTypeGPIOOutput(led_2.gpio_base, led_2.gpio_pin);
    GPIOPinTypeGPIOOutput(led_3.gpio_base, led_3.gpio_pin);
    GPIOPinTypeGPIOOutput(led_4.gpio_base, led_4.gpio_pin);

    set_board_led(BOARD_LED_1, LED_OFF);
    set_board_led(BOARD_LED_2, LED_OFF);
    set_board_led(BOARD_LED_3, LED_OFF);
    set_board_led(BOARD_LED_4, LED_OFF);
}

void set_board_led(BOARD_LED led, LED_STATUS status) {
    led_struct *selected_led;

    if (led == BOARD_LED_1) {
        selected_led = &led_1;
    } else if (led == BOARD_LED_2) {
        selected_led = &led_2;
    } else if (led == BOARD_LED_3) {
        selected_led = &led_3;
    } else {
        selected_led = &led_4;
    }

    if (status == LED_ON) {
        selected_led->status = LED_ON;
        GPIOPinWrite(selected_led->gpio_base, selected_led->gpio_pin, selected_led->gpio_pin);
    } else if (status == LED_OFF) {
        selected_led->status = LED_OFF;
        GPIOPinWrite(selected_led->gpio_base, selected_led->gpio_pin, 0);
    }
}

void toggle_board_led(BOARD_LED led) {
    led_struct *selected_led;

    if (led == BOARD_LED_1) {
        selected_led = &led_1;
    } else if (led == BOARD_LED_2) {
        selected_led = &led_2;
    } else if (led == BOARD_LED_3) {
        selected_led = &led_3;
    } else {
        selected_led = &led_4;
    }

    if (get_board_led_status(led) == LED_ON) {
        selected_led->status = LED_OFF;
        GPIOPinWrite(selected_led->gpio_base, selected_led->gpio_pin, 0);
    } else if (get_board_led_status(led) == LED_OFF) {
        selected_led->status = LED_ON;
        GPIOPinWrite(selected_led->gpio_base, selected_led->gpio_pin, selected_led->gpio_pin);
    }
}

LED_STATUS get_board_led_status(BOARD_LED led) {
    if (led == BOARD_LED_1) {
        return led_1.status;
    } else if (led == BOARD_LED_2) {
        return led_2.status;
    } else if (led == BOARD_LED_3) {
        return led_3.status;
    } else {
        return led_4.status;
    }
}
