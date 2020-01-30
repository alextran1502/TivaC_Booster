/*
 * joystick.c
 *
 *  Created on: Jan 28, 2020
 *      Author: alex
 */


#include <stdint.h>
#include "src_util/uartstdio.h"
#include "joystick.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
/**
 * Pin Setting
 * VER (Y) J3.26 = TIVA J1.42 (A13 | PIN PD_2)
 * HOR (X) J1.2 = TIVA J3.66 (A17 | PIN PK_1)
 * SEL: J1.5 = TIVA J1.45  (PIN PD_5)
 */


void joystick_init(void) {
	UARTprintf("Init joystick\r\n");

	/* Enable Joystick X-Y */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0));

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_2);
	GPIOPinTypeADC(GPIO_PORTK_BASE, GPIO_PIN_1);

	ADCSequenceConfigure(ADC_BASE, 2, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC_BASE, 2, 0, ADC_CTL_CH13);	// Configure step 0 is for CH13
	ADCSequenceStepConfigure(ADC_BASE, 2, 1, ADC_CTL_CH17 | ADC_CTL_IE | ADC_CTL_END); // configure step 1 is for CH17
	ADCSequenceEnable(ADC_BASE, 2);
	ADCIntClear(ADC_BASE, 2);
	ADCHardwareOversampleConfigure(ADC_BASE, 64);

	/* Enable Joystick button */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_4);
	GPIODirModeSet(GPIO_PORTD_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}


JOYSTICK_STATUS joystick_get_value(joystick_data_t * joystick_data) {
	uint32_t buffer[2];
	int32_t button_state;
	ADCProcessorTrigger(ADC_BASE, 2);

	while(!ADCIntStatus(ADC_BASE, 2, false))
	{
		return JOYSTICK_ERROR;
	}

	ADCIntClear(ADC_BASE, 0);
	ADCSequenceDataGet(ADC_BASE, 2, &buffer[0]);

	button_state = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_4);
	joystick_data->x_axis = buffer[0];
	joystick_data->y_axis = buffer[1];
	joystick_data->button_state = button_state == 0 ? BTN_PRESS : BTN_RELEASE;
	return JOYSTICK_OK;
}
