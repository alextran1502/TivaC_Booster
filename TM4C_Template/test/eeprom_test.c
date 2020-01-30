/*
 * eeprom_test.c
 *
 *  Created on: Sep 3, 2019
 *      Author: Alex
 */
#include "src_eeprom/eeprom_hal.h"
#include "unity/unity.h"
#include "unity/unity_fixture.h"


TEST_GROUP(EEPROM);

TEST_SETUP(EEPROM)
{
}

TEST_TEAR_DOWN(EEPROM)
{
}

TEST(EEPROM, SimpleTestCase)
{
//  TEST_ASSERT_EQUAL(0, eeprom_init());
  TEST_FAIL_MESSAGE("Start here");
}
