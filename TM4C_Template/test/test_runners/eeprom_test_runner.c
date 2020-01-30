/*
 * eeprom_test_runner.c
 *
 *  Created on: Sep 3, 2019
 *      Author: Alex
 */

#include "test/unity/unity.h"
#include "test/unity/unity_fixture.h"

TEST_GROUP_RUNNER(EEPROM)
{
    RUN_TEST_CASE(EEPROM, SimpleTestCase);
}
