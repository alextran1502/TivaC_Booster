/*
 * eeprom_comfig.h
 *
 *  Created on: Aug 30, 2019
 *      Author: Alex.tran
 */

#ifndef SRC_EEPROM_EEPROM_CONFIG_H_
#define SRC_EEPROM_EEPROM_CONFIG_H_


#define ENABLE_CUSTOM_CONFIG        0
#define OPERATING_MODE              1
#define DEVICE_ROLE                 2
#define ENABLE_CUSTOM_PINMAP        3

#define INPUT_FROM_MASTER_COUNT     4
#define INPUT_FROM_SLAVE_A_COUNT    5
#define INPUT_FROM_SLAVE_B_COUNT    6
#define INPUT_FROM_SLAVE_C_COUNT    7

#define MASTER_MAP_PIN_0            8
#define MASTER_MAP_PIN_1            9
#define MASTER_MAP_PIN_2            10
#define MASTER_MAP_PIN_3            11
#define MASTER_MAP_PIN_4            12
#define MASTER_MAP_PIN_5            13
#define MASTER_MAP_PIN_6            14
#define MASTER_MAP_PIN_7            15
#define MASTER_MAP_PIN_8            16
#define MASTER_MAP_PIN_9            17
#define MASTER_MAP_PIN_10           18
#define MASTER_MAP_PIN_11           19
#define MASTER_MAP_PIN_12           20
#define MASTER_MAP_PIN_13           21
#define MASTER_MAP_PIN_14           22
#define MASTER_MAP_PIN_15           23
#define MASTER_MAP_PIN_16           24

#define SLAVE_A_MAP_PIN_0           25
#define SLAVE_A_MAP_PIN_1           26
#define SLAVE_A_MAP_PIN_2           27
#define SLAVE_A_MAP_PIN_3           28
#define SLAVE_A_MAP_PIN_4           29
#define SLAVE_A_MAP_PIN_5           30
#define SLAVE_A_MAP_PIN_6           31
#define SLAVE_A_MAP_PIN_7           32
#define SLAVE_A_MAP_PIN_8           33
#define SLAVE_A_MAP_PIN_9           34
#define SLAVE_A_MAP_PIN_10          35
#define SLAVE_A_MAP_PIN_11          36
#define SLAVE_A_MAP_PIN_12          37
#define SLAVE_A_MAP_PIN_13          38
#define SLAVE_A_MAP_PIN_14          39
#define SLAVE_A_MAP_PIN_15          40
#define SLAVE_A_MAP_PIN_16          41

#define SLAVE_B_MAP_PIN_0           42
#define SLAVE_B_MAP_PIN_1           43
#define SLAVE_B_MAP_PIN_2           44
#define SLAVE_B_MAP_PIN_3           45
#define SLAVE_B_MAP_PIN_4           46
#define SLAVE_B_MAP_PIN_5           47
#define SLAVE_B_MAP_PIN_6           48
#define SLAVE_B_MAP_PIN_7           49
#define SLAVE_B_MAP_PIN_8           50
#define SLAVE_B_MAP_PIN_9           51
#define SLAVE_B_MAP_PIN_10          52
#define SLAVE_B_MAP_PIN_11          53
#define SLAVE_B_MAP_PIN_12          54
#define SLAVE_B_MAP_PIN_13          55
#define SLAVE_B_MAP_PIN_14          56
#define SLAVE_B_MAP_PIN_15          57
#define SLAVE_B_MAP_PIN_16          58

#define SLAVE_C_MAP_PIN_0           59
#define SLAVE_C_MAP_PIN_1           60
#define SLAVE_C_MAP_PIN_2           61
#define SLAVE_C_MAP_PIN_3           62
#define SLAVE_C_MAP_PIN_4           63
#define SLAVE_C_MAP_PIN_5           64
#define SLAVE_C_MAP_PIN_6           65
#define SLAVE_C_MAP_PIN_7           66
#define SLAVE_C_MAP_PIN_8           67
#define SLAVE_C_MAP_PIN_9           68
#define SLAVE_C_MAP_PIN_10          69
#define SLAVE_C_MAP_PIN_11          70
#define SLAVE_C_MAP_PIN_12          71
#define SLAVE_C_MAP_PIN_13          72
#define SLAVE_C_MAP_PIN_14          73
#define SLAVE_C_MAP_PIN_15          74
#define SLAVE_C_MAP_PIN_16          75

char* eeprom_create_json(void);
void print_eeprom_json(void);
void eeprom_write_default(void);
#endif /* SRC_EEPROM_EEPROM_CONFIG_H_ */
