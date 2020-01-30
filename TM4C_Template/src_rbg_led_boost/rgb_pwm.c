/*
 * rgb_pwm.c
 *
 *  Created on: Jan 30, 2020
 *      Author: alex
 */
#include <stdint.h>
#include <stdbool.h>

#include "driverlib/pwm.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

#include "src_util/helper_function.h"
#include "src_util/uartstdio.h"
#include "rgb_pwm.h"

uint32_t linear_transform(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);

void RGB_led_init(uint32_t sysClock) {

	/* PWM */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
	SysCtlDelay(10);

	GPIOPinConfigure(GPIO_PK4_M0PWM6);
	GPIOPinConfigure(GPIO_PK5_M0PWM7);

	GPIOPinTypePWM(GPIO_PORTK_BASE, GPIO_PIN_4);
	GPIOPinTypePWM(GPIO_PORTK_BASE, GPIO_PIN_5);

	PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_8);

	PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

	uint32_t freq = 1 / 250 * (sysClock / 8);
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, freq);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 1);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 1);

	PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true);
	PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);
	PWMGenEnable(PWM0_BASE, PWM_GEN_3);
}

uint32_t linear_transform(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void RGB_set_dutycycle(RGB_LED_COLOR color, uint32_t duty_cycle, bool dynamic) {
	if (color == RGB_RED_LED) {
		if (dynamic == true) {
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, linear_transform(duty_cycle, 100, 4025, 0, 1000));
		} else {
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, linear_transform(duty_cycle, 0, 100, 0, 1000));
		}

	} else if (color == RGB_GREEN_LED) {
		if (dynamic == true) {
			UARTprintf("duty: %d\n", duty_cycle);
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, linear_transform(duty_cycle, 100, 4025, 0, 1000));
		} else {
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, linear_transform(duty_cycle, 0, 100, 0, 1000));
		}
	}
}

