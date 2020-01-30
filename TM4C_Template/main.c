
/*
 * benetton.c
 *
 *  Created on: Jan 5, 2019
 *      Author: alex.tran
 */
#include <main.h>
#include "inc/tm4c1294ncpdt.h"
#include "settings.h"

#include "src_ethernet/src_ethernet.h"
#include "src_eeprom/eeprom_hal.h"
#include "src_eeprom/eeprom_config.h"
#include "src_joystick_boost/joystick.h"
#include "src_rbg_led_boost/rgb_pwm.h"
#include "test/unity/unity_fixture.h"
#include "test/unity/unity.h"

#define TICK_PER_SECOND_US 1000000 // Micro-second Timer
#define TICK_PER_SECOND_MS 1000    // Mili-second Timer

extern int main_test(void);

/* Global Variables */
volatile uint8_t ip_ready;
volatile uint32_t tick = 0;
volatile bool is_ready_to_send = false;
struct ethernet_settings_t ethernet_settings;

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
    RGB_led_init(ui32SysClock);
    joystick_init();

    JOYSTICK_STATUS joystick_status;
    joystick_data_t joystick_data;



    while (1)
    {
        joystick_status = joystick_get_value(&joystick_data);
        UARTprintf("x: %d\ty:%d\tbtn:%d\n", joystick_data.x_axis, joystick_data.y_axis, joystick_data.button_state);
        if (joystick_status == JOYSTICK_ERROR)
        {
            UARTprintf("Joystick error \n");
        }

        RGB_set_dutycycle(RGB_RED_LED, 100, false);

        Delay(25);
    }
}


