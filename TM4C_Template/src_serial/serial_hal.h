/*
 * serial_hal.h
 *
 *  Created on: Jan 4, 2019
 *      Author: alex.tran
 */

#ifndef SRC_SERIAL_SERIAL_HAL_H_
#define SRC_SERIAL_SERIAL_HAL_H_

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

#define SERIAL_RX_BUFFER_SIZE 128
#define SERIAL_TX_BUFFER_SIZE 1024

extern volatile uint8_t serial_rx_buffer[];
extern volatile uint32_t serial_rx_head;
extern volatile uint32_t serial_rx_tail;

extern volatile uint8_t serial_tx_buffer[];
extern volatile uint32_t serial_tx_head;
extern volatile uint32_t serial_tx_tail;

typedef struct {
    bool enable;
    uint32_t baud;
    uint8_t length;
    uint8_t parity;
    uint8_t stop;
} SERIAL_CONFIG_INFO;

void serial_hal_init(uint32_t sysClock);

#ifdef UART_INT_EN
void serial_transmit(const uint8_t *uiBuffer, uint32_t ui32Count);
#else
void serial_receive(void);
void serial_transmit(void);
#endif

#endif /* SRC_SERIAL_SERIAL_HAL_H_ */
