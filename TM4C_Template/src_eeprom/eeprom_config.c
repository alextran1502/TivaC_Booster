/*
 * eeprom_config.c
 *
 *  Created on: Aug 30, 2019
 *      Author: Alex.tran
 */

#include "eeprom_hal.h"
#include "eeprom_config.h"
#include "src_util/cJSON.h"
#include "src_util/uartstdio.h"

char* eeprom_create_json(void) {

    char *string = NULL;
    uint32_t result;

    cJSON *eeprom = cJSON_CreateObject();
    if (eeprom == NULL)
        goto end;

    // ENABLE_CUSTOM_CONFIG
    cJSON_AddBoolToObject(eeprom, "enable_custom_config", eeprom_read_buffer[ENABLE_CUSTOM_CONFIG]);

    // OPERATING_MODE
    result = eeprom_read_buffer[OPERATING_MODE];
    if (result == 1) {
        cJSON_AddStringToObject(eeprom, "operating_mode", "master_1_slave");
    } else if(result == 2) {
        cJSON_AddStringToObject(eeprom, "operating_mode", "master_2_slave");
    } else if(result == 3) {
        cJSON_AddStringToObject(eeprom, "operating_mode", "master_3_slave");
    } else {
        cJSON_AddStringToObject(eeprom, "operating_mode", "NaN");
    }

    // DEVICE ROLE
    result = eeprom_read_buffer[DEVICE_ROLE];
    if (result == 1) {
        cJSON_AddStringToObject(eeprom, "device_role", "master");
    } else if(result == 2) {
        cJSON_AddStringToObject(eeprom, "device_role", "slave_a");
    } else if(result == 3) {
        cJSON_AddStringToObject(eeprom, "device_role", "slave_b");
    } else if(result == 4) {
        cJSON_AddStringToObject(eeprom, "device_role", "slave_c");
    } else {
        cJSON_AddStringToObject(eeprom, "device_role", "NaN");
    }

    // ENABLE_CUSTOM_PINMAP
    cJSON_AddBoolToObject(eeprom, "enable_custom_pinmap", eeprom_read_buffer[ENABLE_CUSTOM_PINMAP]);

    // INPUT_FROM_MASTER_COUNT
    cJSON_AddNumberToObject(eeprom, "input_from_master_count", eeprom_read_buffer[INPUT_FROM_MASTER_COUNT]);

    // INPUT_FROM_SLAVE_A_COUNT
    cJSON_AddNumberToObject(eeprom, "input_from_slave_a_count", eeprom_read_buffer[INPUT_FROM_SLAVE_A_COUNT]);

    // INPUT_FROM_SLAVE_B_COUNT
    cJSON_AddNumberToObject(eeprom, "input_from_slave_b_count", eeprom_read_buffer[INPUT_FROM_SLAVE_B_COUNT]);

    // INPUT_FROM_SLAVE_C_COUNT
    cJSON_AddNumberToObject(eeprom, "input_from_slave_c_count", eeprom_read_buffer[INPUT_FROM_SLAVE_C_COUNT]);




    // Print out JSON
    string = cJSON_PrintUnformatted(eeprom);

    end:
    cJSON_Delete(eeprom);
    return string;
}


void eeprom_write_default(void) {
    eeprom_write_buffer[ENABLE_CUSTOM_CONFIG] = true;

    /** OPERATING_MODE
     * 1 : "master_1_slave"
     *      NOTE: DEVICE_ROLE will be ignored when the OPERATING_MODE is master_1_slave,
     *      dip switch will be used to determine role instead.
     * 2 : "master_2_slave"
     * 3 : "master_3_slave"
     */
    eeprom_write_buffer[OPERATING_MODE] = 1;

    /** DEVICE_ROLE
     * 1 : "master"
     * 2 : "slave_a"
     * 3 : "slave_b"
     * 4 : "slave_c"
     */
    eeprom_write_buffer[DEVICE_ROLE] = 1;

    /** ENABLE_CUSTOM_PINMAP
     * false -> use 1-to-1 input output mapping, meaning input 1 maps to output 1
     * true -> use custom output mapping in the subsequent table below
     */ 
    eeprom_write_buffer[ENABLE_CUSTOM_PINMAP] = false;

    /** INPUT_FROM_MASTER_COUNT
     * Number of input coming from Master device that will be used in the current device
     */ 
    eeprom_write_buffer[INPUT_FROM_MASTER_COUNT] = 8;

    /** INPUT_FROM_SLAVE_A_COUNT
     * Number of input coming from Slave A device that will be used in the current device
     */ 
    eeprom_write_buffer[INPUT_FROM_SLAVE_A_COUNT] = 8;

    /** INPUT_FROM_SLAVE_B_COUNT
     * Number of input coming from Slave B device that will be used in the current device
     */ 
    eeprom_write_buffer[INPUT_FROM_SLAVE_B_COUNT] = 8;

    /** INPUT_FROM_SLAVE_C_COUNT
     * Number of input coming from Slave C device that will be used in the current device
     */ 
    eeprom_write_buffer[INPUT_FROM_SLAVE_C_COUNT] = 4;

    eeprom_write_and_read();
}



void print_eeprom_json(void) {
    UARTprintf("%s\n", eeprom_create_json());
}
