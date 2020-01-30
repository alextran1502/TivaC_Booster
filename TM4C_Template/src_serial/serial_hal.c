/*
 * serial_hal.c
 *
 *  Created on: Jan 4, 2019
 *      Author: alex.tran
 */
#include "serial_hal.h"
#include <benetton.h>
#include <src_util/uartstdio.h>
#include "serial.h"
#include "serial_console.h"
#include "src_mk_led/mk_led_control.h"

volatile uint8_t serial_rx_buffer[SERIAL_RX_BUFFER_SIZE];
volatile uint32_t serial_rx_head, serial_rx_tail;

volatile uint8_t serial_tx_buffer[SERIAL_TX_BUFFER_SIZE];
volatile uint32_t serial_tx_head, serial_tx_tail;

SERIAL_CONFIG_INFO serial_config_info;

void serial_hal_init(uint32_t sysClock) {
    serial_config_info.enable = true;
    serial_config_info.baud = BAUD_RATE;
    serial_config_info.length = UART_CONFIG_WLEN_8;
    serial_config_info.parity = UART_CONFIG_PAR_NONE;
    serial_config_info.stop = UART_CONFIG_STOP_ONE;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTDisable(UART0_BASE);
    UARTEnable(UART0_BASE);

    UARTConfigSetExpClk(UART0_BASE, sysClock, serial_config_info.baud,
                        (serial_config_info.length | serial_config_info.parity | serial_config_info.stop));

    serial_rx_head = 0;
    serial_rx_tail = 0;

#ifdef UART_INT_EN
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
#endif
}

#ifdef UART_INT_EN
void serial_transmit(const uint8_t *uiBuffer, uint32_t ui32Count) {
    while (ui32Count--) {
        UARTCharPutNonBlocking(UART0_BASE, *uiBuffer++);
    }
}
#endif

void serial_receive(void) {
    uint32_t new_char;

    if (UARTCharsAvail(UART0_BASE)) {
        new_char = UARTCharGetNonBlocking(UART0_BASE);

        // Check if the input is valid ascii
        if (new_char > 0xFF) {
            UARTRxErrorGet(UART0_BASE);
            UARTRxErrorClear(UART0_BASE);
        } else {
            // If user hit "enter" the transmit buffer will move cursor to a new line
            if (new_char == '\r') {
                serial_tx_buffer[serial_tx_head % SERIAL_TX_BUFFER_SIZE] = new_char;
                serial_tx_head++;
                new_char = '\n';
            }

            // if (new_char == )
            // Put input char into Receiving buffer and increase the index
            serial_rx_buffer[serial_rx_head % SERIAL_RX_BUFFER_SIZE] = new_char;
            serial_rx_head++;

            // Also put input char into Transmit buffer to echo back to the console
            serial_tx_buffer[serial_tx_head % SERIAL_TX_BUFFER_SIZE] = new_char;
            serial_tx_head++;

            if (serial_rx_buffer[(serial_rx_head - 1) % SERIAL_RX_BUFFER_SIZE] == '\n') {
                process_serial_input();
            }
        }
    }
}

void serial_transmit(void) {
    uint32_t index;

    for (index = serial_tx_tail; index < serial_tx_head; index++) {
        if (UARTSpaceAvail(UART0_BASE)) {
            UARTCharPutNonBlocking(UART0_BASE, serial_tx_buffer[index % SERIAL_TX_BUFFER_SIZE]);
            serial_tx_tail++;
        }
    }
}
