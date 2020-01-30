
/*
 * benetton.c
 *
 *  Created on: Jan 5, 2019
 *      Author: alex.tran
 */
#include "benetton.h"
#include "inc/tm4c1294ncpdt.h"
#include "settings.h"

#include "src_ethernet/src_ethernet.h"
#include "src_eeprom/eeprom_hal.h"
#include "src_eeprom/eeprom_config.h"
#include "src_joystick_boost/joystick.h"
#include "test/unity/unity_fixture.h"
#include "test/unity/unity.h"

#include "driverlib/pwm.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#define TICK_PER_SECOND_US 1000000 // Micro-second Timer
#define TICK_PER_SECOND_MS 1000    // Mili-second Timer

extern int main_test(void);

/* Global Variables */
volatile uint8_t ip_ready;
volatile uint32_t tick = 0;
volatile bool is_ready_to_send = false;
struct ethernet_settings_t ethernet_settings;

uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);

void runTest(UnityTestFunction test)
{
    if (TEST_PROTECT())
    {
        test();
    }
}

void SysTickHandler(void)
{
    tick++;
    lwIPTimer(10); // lwIP Timer Trigger [1 : 100ms] - [10 : 10ms] - [100 : 1ms]
}

void setup_systick_timer(uint32_t SysClock)
{
    SysTickPeriodSet(SysClock / TICK_PER_SECOND_MS - 1);
    SysTickEnable();
    SysTickIntEnable();
}

void Delay(uint32_t delay_tick)
{
    uint32_t current_tick;
    current_tick = tick;
    while ((tick - current_tick) < (delay_tick - 1))
    {
    }
}

int main(int argc, const char *argv[])
{
    /* turn on main oscilator for Ethernet PHY */
    SysCtlMOSCConfigSet(SYSCTL_MOSC_HIGHFREQ);

    /* Set system clock to 120MHz - Run directly from crystal */
    ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);
    setup_systick_timer(ui32SysClock);

    /* Initialization peripheral */
    serial_init(ui32SysClock);
    UARTprintf("\033[2J\033[H");
    UARTprintf("<<<<<<<<<<< Initializing hardware...\n");

    led_init();
    joystick_init();

    JOYSTICK_STATUS joystick_status;
    joystick_data_t joystick_data;

    /* PWM */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    SysCtlDelay(10);

    GPIOPinConfigure(GPIO_PK4_M0PWM6);
    GPIOPinConfigure(GPIO_PK5_M0PWM7);

    GPIOPinTypePWM(GPIO_PORTK_BASE, GPIO_PIN_4);
    GPIOPinTypePWM(GPIO_PORTK_BASE, GPIO_PIN_5);

    PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_8);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    uint32_t freq = 1 / 250 * (ui32SysClock / 8);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, freq);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 0);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 0);

    PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true);
    PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_3);
    while (1)
    {
        joystick_status = joystick_get_value(&joystick_data);

        // UARTprintf("X: %d - Y: %d - BTN: %d\n", joystick_data.x_axis, joystick_data.y_axis, joystick_data.button_state);
        if (joystick_status == JOYSTICK_ERROR)
        {
            UARTprintf("Joystick error \n");
        }

        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, map(joystick_data.x_axis, 100, 4025, 0, 1000));
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, map(joystick_data.y_axis, 100, 4025, 0, 1000));

        Delay(2);
    }
}

uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}