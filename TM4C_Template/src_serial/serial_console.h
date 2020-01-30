/*
 * serial_console.h
 *
 *  Created on: Jan 6, 2019
 *      Author: alex.tran
 */

#ifndef SRC_SERIAL_SERIAL_CONSOLE_H_
#define SRC_SERIAL_SERIAL_CONSOLE_H_

#include <stdint.h>

void process_serial_input(void);
void parse_message(uint8_t *command);

#endif /* SRC_SERIAL_SERIAL_CONSOLE_H_ */
