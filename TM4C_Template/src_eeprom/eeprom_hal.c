/*
 * eeprom_hal.c
 *
 *  Created on: Aug 30, 2019
 *      Author: Alex.tran
 */
#include "eeprom_hal.h"
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/eeprom.h"
#include "driverlib/sysctl.h"
#include "src_util/uartstdio.h"

uint32_t eeprom_write_buffer[200];
uint32_t eeprom_read_buffer[200];

uint8_t eeprom_init()
{
    uint32_t ui32EEPROMInit;
    uint32_t e2size, e2block;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0))
    {
    }
    ui32EEPROMInit = EEPROMInit();
    if (ui32EEPROMInit != EEPROM_INIT_OK)
    {
        while (1)
        {
            UARTprintf("EEPROM Init Failed!\n");
        }
    }

    e2size = EEPROMSizeGet(); // Get EEPROM Size
    UARTprintf("EEPROM Size %d bytes\n", e2size);

    e2block = EEPROMBlockCountGet(); // Get EEPROM Block Count
    UARTprintf("EEPROM Blok Count: %d\n", e2block);

    return 0;
}

void eeprom_write_and_read(void)
{

    EEPROMProgram(eeprom_write_buffer, EEPROMAddrFromBlock(0), sizeof(eeprom_write_buffer));
    EEPROMRead(eeprom_read_buffer, EEPROMAddrFromBlock(0), sizeof(eeprom_read_buffer));
    //    EEPROMProgram(&eeprom_write_buffer[50], EEPROMAddrFromBlock(0), 1);
    //    EEPROMRead(eeprom_read_buffer, EEPROMAddrFromBlock(0), sizeof(eeprom_read_buffer));

    //    for (i = 0; i < 200; i++)
    //    {
    //        UARTprintf("EEPROM[%d]: %d\n", i, eeprom_read_buffer[i]);
    //        Delay(5);
    //    }
}

uint32_t eeprom_mass_erase()
{
    uint32_t ret, i;
    ret = EEPROMMassErase();
    EEPROMRead(eeprom_read_buffer, EEPROMAddrFromBlock(0), sizeof(eeprom_read_buffer));
    return ret;
}
