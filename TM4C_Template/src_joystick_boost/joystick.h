/*
 * joystick.h
 *
 *  Created on: Jan 28, 2020
 *      Author: alex
 */

#ifndef SRC_JOYSTICK_BOOST_JOYSTICK_H_
#define SRC_JOYSTICK_BOOST_JOYSTICK_H_
#include <stdint.h>

#define ADC_BASE ADC0_BASE

typedef enum {
    JOYSTICK_OK,
    JOYSTICK_ERROR
} JOYSTICK_STATUS;

typedef enum {
    BTN_RELEASE = 0,
    BTN_PRESS
} JOYSTICK_BUTTON_STATE;

typedef struct {
    uint32_t x_axis;
    uint32_t y_axis;
    JOYSTICK_BUTTON_STATE button_state;
} joystick_data_t;




void joystick_init(void);
JOYSTICK_STATUS joystick_get_value(joystick_data_t * joystick_data);

#endif /* SRC_JOYSTICK_BOOST_JOYSTICK_H_ */
