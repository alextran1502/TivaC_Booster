/*
 * all_tests.c
 *
 *  Created on: Sep 3, 2019
 *      Author: Alex
 */


#include "test/unity/unity_fixture.h"

static void RunAllTests(void)
{
  RUN_TEST_GROUP(EEPROM);
}


int main_test(int argc, const char * argv[])
{
  return UnityMain(argc, argv, RunAllTests);
}
