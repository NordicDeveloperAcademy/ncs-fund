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

/* STEP 8 - Define the I2C slave device address and the addresses of relevant registers */

#define CHIP_ID  0x60
#define SENSOR_CONFIG_VALUE 0x93

/* STEP 6 - Get the node identifier of the sensor */

/* Data structure to store BME280 data */
struct bme280_data {
	/* Compensation parameters */
	uint16_t dig_t1;
	int16_t dig_t2;
	int16_t dig_t3;
} bmedata;


void bme_calibrationdata(const struct i2c_dt_spec *spec, struct bme280_data *sensor_data_ptr)
{
	/* Step 10 - Put calibration function code */
}

/* Compensate current temperature using previously stored sensor calibration data */
static int32_t bme280_compensate_temp(struct bme280_data *data, int32_t adc_temp)
{
	int32_t var1, var2;

	var1 = (((adc_temp >> 3) - ((int32_t)data->dig_t1 << 1)) * ((int32_t)data->dig_t2)) >> 11;

	var2 = (((((adc_temp >> 4) - ((int32_t)data->dig_t1)) *
		  ((adc_temp >> 4) - ((int32_t)data->dig_t1))) >>
		 12) *
		((int32_t)data->dig_t3)) >>
	       14;

	return ((var1 + var2) * 5 + 128) >> 8;
}

int main(void)
{

	/* STEP 7 - Retrieve the API-specific device structure and make sure that the device is
	 * ready to use  */

	/* STEP 9 - Verify it is proper device by reading device id  */
	
	bme_calibrationdata(&dev_i2c, &bmedata);

	/* STEP 11 - Setup the sensor by writing the value 0x93 to the Configuration register */

	while (1) {

		/* STEP 12 - Read the temperature from the sensor */

		/* STEP 12.1 - Put the data read from registers into actual order (see datasheet) */

		/* STEP 12.2 - Compensate temperature */

		/* STEP 12.3 - Convert temperature */

		k_msleep(SLEEP_TIME_MS);
	}
}
