//*****************************************************************************
//
// Startup code for use with TI's Code Composer Studio.
//
// Copyright (c) 2011-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "src_util/uartstdio.h"
#include "inc/hw_types.h"
#include "inc/hw_nvic.h"
//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void startup(void);
void NmiSR(void);
void FaultISR(void);
void unimplemented_isr(void);
void fault_mpu(void);
void fault_bus(void);
void fault_usage(void);
//*****************************************************************************
//
// External declaration for the reset handler that is to be called when the
// processor is started
//
//*****************************************************************************
extern void _c_int00(void);
extern void SysTickHandler(void);
extern void lwIPEthernetIntHandler(void);
extern void UARTStdioIntHandler(void);

//*****************************************************************************
//
// Linker variable that marks the top of the stack.
//
//*****************************************************************************
extern uint32_t __STACK_TOP;

//*****************************************************************************
//
// External declarations for the interrupt handlers used by the application.
//
//*****************************************************************************
// To be added by user

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000 or at the start of
// the program if located at a start address other than 0.
//
//*****************************************************************************
#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
void (*const g_pfnVectors[])(void) =
    {
        (void (*)(void))((uint32_t)&__STACK_TOP),
        // The initial stack pointer
        startup,               // The reset handler
        NmiSR,                  // The NMI handler
        FaultISR,               // The hard fault handler
        fault_mpu,              // The MPU fault handler
        fault_bus,              // The bus fault handler
        fault_usage,            // The usage fault handler
        0,                      // Reserved
        0,                      // Reserved
        0,                      // Reserved
        0,                      // Reserved
        unimplemented_isr,      // SVCall handler
        unimplemented_isr,      // Debug monitor handler
        0,                      // Reserved
        unimplemented_isr,      // The PendSV handler
        SysTickHandler,         // The SysTick handler
        unimplemented_isr,      // GPIO Port A
        unimplemented_isr,      // GPIO Port B
        unimplemented_isr,      // GPIO Port C
        unimplemented_isr,      // GPIO Port D
        unimplemented_isr,      // GPIO Port E
        UARTStdioIntHandler,      // UART0 Rx and Tx
        unimplemented_isr,      // UART1 Rx and Tx
        unimplemented_isr,      // SSI0 Rx and Tx
        unimplemented_isr,      // I2C0 Master and Slave
        unimplemented_isr,      // PWM Fault
        unimplemented_isr,      // PWM Generator 0
        unimplemented_isr,      // PWM Generator 1
        unimplemented_isr,      // PWM Generator 2
        unimplemented_isr,      // Quadrature Encoder 0
        unimplemented_isr,      // ADC Sequence 0
        unimplemented_isr,      // ADC Sequence 1
        unimplemented_isr,      // ADC Sequence 2
        unimplemented_isr,      // ADC Sequence 3
        unimplemented_isr,      // Watchdog timer
        unimplemented_isr,      // Timer 0 subtimer A
        unimplemented_isr,      // Timer 0 subtimer B
        unimplemented_isr,      // Timer 1 subtimer A
        unimplemented_isr,      // Timer 1 subtimer B
        unimplemented_isr,      // Timer 2 subtimer A
        unimplemented_isr,      // Timer 2 subtimer B
        unimplemented_isr,      // Analog Comparator 0
        unimplemented_isr,      // Analog Comparator 1
        unimplemented_isr,      // Analog Comparator 2
        unimplemented_isr,      // System Control (PLL, OSC, BO)
        unimplemented_isr,      // FLASH Control
        unimplemented_isr,      // GPIO Port F
        unimplemented_isr,      // GPIO Port G
        unimplemented_isr,      // GPIO Port H
        unimplemented_isr,      // UART2 Rx and Tx
        unimplemented_isr,      // SSI1 Rx and Tx
        unimplemented_isr,      // Timer 3 subtimer A
        unimplemented_isr,      // Timer 3 subtimer B
        unimplemented_isr,      // I2C1 Master and Slave
        unimplemented_isr,      // CAN0
		unimplemented_isr,         // CAN1
        lwIPEthernetIntHandler, // Ethernet
        unimplemented_isr,      // Hibernate
        unimplemented_isr,      // USB0
        unimplemented_isr,      // PWM Generator 3
        unimplemented_isr,      // uDMA Software Transfer
        unimplemented_isr,      // uDMA Error
        unimplemented_isr,      // ADC1 Sequence 0
        unimplemented_isr,      // ADC1 Sequence 1
        unimplemented_isr,      // ADC1 Sequence 2
        unimplemented_isr,      // ADC1 Sequence 3
        unimplemented_isr,      // External Bus Interface 0
        unimplemented_isr,      // GPIO Port J
        unimplemented_isr,      // GPIO Port K
        unimplemented_isr,      // GPIO Port L
        unimplemented_isr,      // SSI2 Rx and Tx
        unimplemented_isr,      // SSI3 Rx and Tx
        unimplemented_isr,      // UART3 Rx and Tx
        unimplemented_isr,      // UART4 Rx and Tx
        unimplemented_isr,      // UART5 Rx and Tx
        unimplemented_isr,      // UART6 Rx and Tx
        unimplemented_isr,      // UART7 Rx and Tx
        unimplemented_isr,      // I2C2 Master and Slave
        unimplemented_isr,      // I2C3 Master and Slave
        unimplemented_isr,      // Timer 4 subtimer A
        unimplemented_isr,      // Timer 4 subtimer B
        unimplemented_isr,      // Timer 5 subtimer A
        unimplemented_isr,      // Timer 5 subtimer B
        unimplemented_isr,      // FPU
        0,                      // Reserved
        0,                      // Reserved
        unimplemented_isr,      // I2C4 Master and Slave
        unimplemented_isr,      // I2C5 Master and Slave
        unimplemented_isr,      // GPIO Port M
        unimplemented_isr,      // GPIO Port N
        0,                      // Reserved
        unimplemented_isr,      // Tamper
        unimplemented_isr,      // GPIO Port P (Summary or P0)
        unimplemented_isr,      // GPIO Port P1
        unimplemented_isr,      // GPIO Port P2
        unimplemented_isr,      // GPIO Port P3
        unimplemented_isr,      // GPIO Port P4
        unimplemented_isr,      // GPIO Port P5
        unimplemented_isr,      // GPIO Port P6
        unimplemented_isr,      // GPIO Port P7
        unimplemented_isr,      // GPIO Port Q (Summary or Q0)
        unimplemented_isr,      // GPIO Port Q1
        unimplemented_isr,      // GPIO Port Q2
        unimplemented_isr,      // GPIO Port Q3
        unimplemented_isr,      // GPIO Port Q4
        unimplemented_isr,      // GPIO Port Q5
        unimplemented_isr,      // GPIO Port Q6
        unimplemented_isr,      // GPIO Port Q7
        unimplemented_isr,      // GPIO Port R
        unimplemented_isr,      // GPIO Port S
        unimplemented_isr,      // SHA/MD5 0
        unimplemented_isr,      // AES 0
        unimplemented_isr,      // DES3DES 0
        unimplemented_isr,      // LCD Controller 0
        unimplemented_isr,      // Timer 6 subtimer A
        unimplemented_isr,      // Timer 6 subtimer B
        unimplemented_isr,      // Timer 7 subtimer A
        unimplemented_isr,      // Timer 7 subtimer B
        unimplemented_isr,      // I2C6 Master and Slave
        unimplemented_isr,      // I2C7 Master and Slave
        unimplemented_isr,      // HIM Scan Matrix Keyboard 0
        unimplemented_isr,      // One Wire 0
        unimplemented_isr,      // HIM PS/2 0
        unimplemented_isr,      // HIM LED Sequencer 0
        unimplemented_isr,      // HIM Consumer IR 0
        unimplemented_isr,      // I2C8 Master and Slave
        unimplemented_isr,      // I2C9 Master and Slave
        unimplemented_isr,      // GPIO Port T
        unimplemented_isr,      // Fan 1
        0,                      // Reserved
};

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void startup(void)
{
    //
    // Jump to the CCS C initialization routine.  This will enable the
    // floating-point unit as well, so that does not need to be done here.
    //
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
void NmiSR(void)
{
    UARTprintf("ERROR: Fault NMISR\n");
    while (1);
}

void FaultISR(void)
{
    uint32_t bus_fault_addr, mm_fault_addr, hard_fault_status;
    // SysCtlReset();
    UARTprintf("ERROR: Fault ISR\n");
    // Reading bus fault address
    bus_fault_addr = HWREG(NVIC_FAULT_ADDR) & 0xFFFFFFFF;
    mm_fault_addr = HWREG(NVIC_MM_ADDR)  & 0xFFFFFFFF;
    hard_fault_status = HWREG(NVIC_HFAULT_STAT)  & 0xFFFFFFFF;

    UARTprintf("Bus Fault Address: %X\n", bus_fault_addr);
    UARTprintf("MM Fault Address: %X\n", mm_fault_addr);
    UARTprintf("Hard Fault Status: %X\n", hard_fault_status);
    while (1);
}

void unimplemented_isr(void) {
    UARTprintf("ERROR: Unimplemented ISR\n");
    while (1);
}

void fault_mpu(void) {
    UARTprintf("ERROR: Fault MPU\n");
    while (1);
}

void fault_bus(void) {
    UARTprintf("ERROR: FAULT BUS\n");
    while (1);
}

void fault_usage(void) {
    UARTprintf("ERROR: FAULT USAGE\n");
    while (1);
}
