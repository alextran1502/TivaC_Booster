/*
 * serial.h
 *
 *  Created on: Jan 4, 2019
 *      Author: alex.tran
 */

#ifndef SRC_SERIAL_SERIAL_H_
#define SRC_SERIAL_SERIAL_H_

#include <src_util/uartstdio.h>
#include <stdbool.h>
#include <stdint.h>

#define BAUD_RATE 115200

void serial_init(uint32_t sysClock);
void serial_get_data(int32_t incoming_data);
void serial_idle(void);
void serial_print(const char* buffer);

#endif /* SRC_SERIAL_SERIAL_H_ */
