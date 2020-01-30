/*
 * eeprom_hal.h
 *
 *  Created on: Aug 30, 2019
 *      Author: Alex.tran
 */

#ifndef SRC_EEPROM_EEPROM_HAL_H_
#define SRC_EEPROM_EEPROM_HAL_H_
#include <stdint.h>

extern uint32_t eeprom_read_buffer[200];
extern uint32_t eeprom_write_buffer[200];

uint8_t eeprom_init();
void eeprom_write_and_read(void);
uint32_t eeprom_mass_erase(void); 
#endif /* SRC_EEPROM_EEPROM_HAL_H_ */
