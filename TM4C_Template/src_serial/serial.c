/*
 * serial.c
 *
 *  Created on: Jan 4, 2019
 *      Author: alex.tran
 */
#include <main.h>
#include "serial.h"
#include "serial_hal.h"
#include "src_mk_led/mk_led_control.h"

void serial_init(uint32_t sysClock) {
    //    serial_hal_init(sysClock);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTStdioConfig(0, BAUD_RATE, 16000000);
    UARTFlushTx(false);
}

void serial_idle(void) {
    serial_receive();
    serial_transmit();
}

void serial_print(const char* buffer) {
    int i = 0;

    while (buffer[i] != '\0') {
        serial_tx_buffer[serial_tx_head % SERIAL_TX_BUFFER_SIZE] = buffer[i];
        serial_tx_head++;
        i++;
    }
}

#ifdef UART_INT_EN
void UARTIntHandler() {
    uint32_t ui32Status;

    ui32Status = UARTIntStatus(UART0_BASE, true);

    UARTIntClear(UART0_BASE, ui32Status);

    if (UARTCharsAvail(UART0_BASE)) {
        UARTCharPutNonBlocking(UART0_BASE, UARTCharGetNonBlocking(UART0_BASE));

        set_mk_led(RED_LED, LED_ON);

        SysCtlDelay(ui32SysClock / (1000 * 3));

        set_mk_led(RED_LED, LED_OFF);
    }
}
#endif
