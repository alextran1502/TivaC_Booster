/*
 * serial_console.c
 *
 *  Created on: Jan 6, 2019
 *      Author: alex.tran
 */
#include <src_util/uartstdio.h>
#include "serial_console.h"
#include "serial.h"
#include "serial_hal.h"

void process_serial_input(void) {
    uint8_t tail_index;
    uint8_t process_buffer[SERIAL_RX_BUFFER_SIZE] = {0};

    // Read data that just came into circular buffer
    for (tail_index = serial_rx_tail; tail_index < serial_rx_head; tail_index++) {
        process_buffer[tail_index - serial_rx_tail] = serial_rx_buffer[tail_index % SERIAL_RX_BUFFER_SIZE];
    }

    parse_message(process_buffer);
    serial_rx_tail = serial_rx_head;
}

void parse_message(uint8_t *command) {
//    if (!strncmp(command, "help", 4)) {
//        UARTprintf("\n=== Use The Console Commands Below To Navigate Through the Application ===");
//    }
}
