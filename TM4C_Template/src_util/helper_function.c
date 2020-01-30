/*
 * helper_function.c
 *
 *  Created on: Jan 30, 2020
 *      Author: alex
 */


#include "helper_function.h"

int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
