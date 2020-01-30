/*
 * mk_led_control.h
 *
 *  Created on: Jan 3, 2019
 *      Author: altra
 */

#ifndef SRC_MK_LED_MK_LED_CONTROL_H_
#define SRC_MK_LED_MK_LED_CONTROL_H_

typedef enum {
    LED_ON,
    LED_OFF,
    LED_PWM
} LED_STATUS;

typedef enum {
    BLUE_LED,
    GREEN_LED,
    RED_LED,
    BOARD_LED_1,
    BOARD_LED_2,
    BOARD_LED_3,
    BOARD_LED_4,
} BOARD_LED;

typedef struct {
    uint32_t gpio_base;
    uint32_t gpio_pin;
    uint32_t pwm_time;
    LED_STATUS status;
} led_struct;

void led_init(void);
void set_board_led(BOARD_LED led, LED_STATUS status);
void toggle_board_led(BOARD_LED led);
LED_STATUS get_board_led_status(BOARD_LED led);

#endif /* SRC_MK_LED_MK_LED_CONTROL_H_ */
