/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
/* STEP 3 - Include the header file of the I2C API */

/* STEP 4.1 - Include the header file of printk() */

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* STEP 7 - Define the I2C slave device address and the addresses of relevant registers */


/* STEP 5 - Get the label of the I2C controller connected to your sensor */

void main(void)
{

	int ret;

/* STEP 6 - Get the binding of the I2C driver  */

/* STEP 8 - Setup the sensor by writing the value 0x8C to the Configuration register */


	while (1) {
/* STEP 9 - Read the temperature from the sensor */


/* STEP 10 - Convert the two bytes to a 12-bits */

		k_msleep(SLEEP_TIME_MS);
	}
}
