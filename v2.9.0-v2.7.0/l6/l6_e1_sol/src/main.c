/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
/* STEP 3 - Include the header file of the I2C API */
#include <zephyr/drivers/i2c.h>
/* STEP 4.1 - Include the header file of printk() */
#include <zephyr/sys/printk.h>
/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

/* STEP 8 - Define the addresses of relevant registers */
#define CTRLMEAS 0xF4
#define CALIB00	 0x88
#define ID	 0xD0
#define TEMPMSB	 0xFA

#define CHIP_ID  0x60
#define SENSOR_CONFIG_VALUE 0x93

/* STEP 6 - Get the node identifier of the sensor */
#define I2C_NODE DT_NODELABEL(mysensor)

/* Data structure to store BME280 data */
struct bme280_data {
	/* Compensation parameters */
	uint16_t dig_t1;
	int16_t dig_t2;
	int16_t dig_t3;
} bmedata;

/* Read sensor calibration data and stores these into sensor data */
void bme_calibrationdata(const struct i2c_dt_spec *spec, struct bme280_data *sensor_data_ptr)
{
	
	/* Step 10 - Put calibration function code */
	uint8_t values[6];

	int ret = i2c_burst_read_dt(spec, CALIB00, values, 6);

	if (ret != 0) {
		printk("Failed to read register %x \n", CALIB00);
		return;
	}

	sensor_data_ptr->dig_t1 = ((uint16_t)values[1]) << 8 | values[0];
	sensor_data_ptr->dig_t2 = ((uint16_t)values[3]) << 8 | values[2];
	sensor_data_ptr->dig_t3 = ((uint16_t)values[5]) << 8 | values[4];
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
	static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C_NODE);

	if (!device_is_ready(dev_i2c.bus)) {
		printk("I2C bus %s is not ready!\n", dev_i2c.bus->name);
		return -1;
	}

	/* STEP 9 - Verify it is proper device by reading device id  */
	uint8_t id = 0;
	uint8_t regs[] = {ID};

	int ret = i2c_write_read_dt(&dev_i2c, regs, 1, &id, 1);

	if (ret != 0) {
		printk("Failed to read register %x \n", regs[0]);
		return -1;
	}

	if (id != CHIP_ID) {
		printk("Invalid chip id! %x \n", id);
		return -1;
	}

	bme_calibrationdata(&dev_i2c, &bmedata);

	/* STEP 11 - Setup the sensor by writing the value 0x93 to the Configuration register */
	uint8_t sensor_config[] = {CTRLMEAS, SENSOR_CONFIG_VALUE};

	ret = i2c_write_dt(&dev_i2c, sensor_config, 2);

	if (ret != 0) {
		printk("Failed to write register %x \n", sensor_config[0]);
		return -1;
	}

	while (1) {

		/* STEP 12 - Read the temperature from the sensor */
		uint8_t temp_val[3] = {0};

		int ret = i2c_burst_read_dt(&dev_i2c, TEMPMSB, temp_val, 3);

		if (ret != 0) {
			printk("Failed to read register %x \n", TEMPMSB);
			k_msleep(SLEEP_TIME_MS);
			continue;
		}

		/* STEP 12.1 - Put the data read from registers into actual order (see datasheet) */
		int32_t adc_temp =
			(temp_val[0] << 12) | (temp_val[1] << 4) | ((temp_val[2] >> 4) & 0x0F);

		/* STEP 12.2 - Compensate temperature */
		int32_t comp_temp = bme280_compensate_temp(&bmedata, adc_temp);

		/* STEP 12.3 - Convert temperature */
		float temperature = (float)comp_temp / 100.0f;
		double fTemp = (double)temperature * 1.8 + 32;

		// Print reading to console
		printk("Temperature in Celsius : %8.2f C\n", (double)temperature);
		printk("Temperature in Fahrenheit : %.2f F\n", fTemp);

		k_msleep(SLEEP_TIME_MS);
	}
}
