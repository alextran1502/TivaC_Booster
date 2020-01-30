/*
 * grb_pwm.h
 *
 *  Created on: Jan 30, 2020
 *      Author: alex
 */

#ifndef SRC_RBG_LED_BOOST_RGB_PWM_H_
#define SRC_RBG_LED_BOOST_RGB_PWM_H_

typedef enum {
	RGB_GREEN_LED,
	RGB_RED_LED
} RGB_LED_COLOR;

void RGB_led_init(uint32_t sysClock);
void RGB_set_dutycycle(RGB_LED_COLOR color, uint32_t duty_cycle, bool dynamic);

#endif /* SRC_RBG_LED_BOOST_RGB_PWM_H_ */
