/*
 * explore_all.h
 *
 *  Created on: Jan 4, 2019
 *      Author: alex.tran
 */

#ifndef BENETTON_H_
#define BENETTON_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>
#include <src_util/uartstdio.h>
#include <stdio.h>
#include <string.h>

#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/i2c.h"
#include "driverlib/adc.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/timer.h"
#include "driverlib/fpu.h"
#include "driverlib/emac.h"
#include "driverlib/flash.h"

#include "src_mk_led/mk_led_control.h"
#include "src_serial/serial.h"

#define SYSTICKHZ 100
#define SYSTICKMS (1000 / SYSTICKHZ)


uint32_t ui32SysClock;

void Delay(uint32_t delay_tick);
void can_irq(void);

#endif /* BENETTON_H_ */
