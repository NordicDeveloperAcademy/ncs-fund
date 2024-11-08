/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
/* STEP 3 - Include the header file of the I2C API */

/* STEP 4.1 - Include the header file of printk() */

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

/* STEP 8 - Define the the addresses of relevant sensor registers and settings */

/* STEP 6 - Get the node identifier of the sensor */

int main(void)
{

	int ret;

	/* STEP 7 - Retrieve the API-specific device structure and make sure that the device is
	 * ready to use  */

	/* STEP 9 - Setup the sensor by writing the value 0x2A to the MODE_CONTROL1 register
	0x2A Means : IR Gain: 1x, RGB Gain: 1x, Measurement mode: 120ms mode
	*/

	/* STEP 10 - Enable measurement by writing 1 to bit 4 of the MODE_CONTROL2 register */

	while (1) {
		/* STEP 11 - Read the RGB values from the sensor */

		k_msleep(SLEEP_TIME_MS);
	}
}
