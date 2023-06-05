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
#define SLEEP_TIME_MS   1000

/* STEP 8 - Define the I2C slave device address and the addresses of relevant registers */
#define STTS751_TEMP_HIGH_REG            0x00
#define STTS751_TEMP_LOW_REG             0x02
#define STTS751_CONFIG_REG               0x03

/* STEP 6 - Get the node identifier of the sensor */
#define I2C_NODE DT_NODELABEL(mysensor)

void main(void)
{

	int ret;

/* STEP 7 - Retrieve the API-specific device structure and make sure that the device is ready to use  */
	static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C_NODE);
	if (!device_is_ready(dev_i2c.bus)) {
		printk("I2C bus %s is not ready!\n\r",dev_i2c.bus->name);
		return;
	}

/* STEP 9 - Setup the sensor by writing the value 0x8C to the Configuration register */
	uint8_t config[2] = {STTS751_CONFIG_REG,0x8C};
	ret = i2c_write_dt(&dev_i2c, config, sizeof(config));
	if(ret != 0){
		printk("Failed to write to I2C device address %x at Reg. %x \n", dev_i2c.addr,config[0]);
		return;
	}

	while (1) {
/* STEP 10 - Read the temperature from the sensor */
		uint8_t temp_reading[2]= {0};
		uint8_t sensor_regs[2] ={STTS751_TEMP_LOW_REG,STTS751_TEMP_HIGH_REG};
		ret = i2c_write_read_dt(&dev_i2c,&sensor_regs[0],1,&temp_reading[0],1);
		if(ret != 0){
			printk("Failed to write/read I2C device address %x at Reg. %x \r\n", dev_i2c.addr,sensor_regs[0]);
		}
		ret = i2c_write_read_dt(&dev_i2c,&sensor_regs[1],1,&temp_reading[1],1);
		if(ret != 0){
			printk("Failed to write/read I2C device address %x at Reg. %x \r\n", dev_i2c.addr,sensor_regs[1]);
		}

/* STEP 11 - Convert the two bytes to a 12-bits */
		int temp = ((int)temp_reading[1] * 256 + ((int)temp_reading[0] & 0xF0)) / 16;
		if(temp > 2047)
		{
			temp -= 4096;
		}

		// Convert to engineering units 
		double cTemp = temp * 0.0625;
		double fTemp = cTemp * 1.8 + 32;

		//Print reading to console  
		printk("Temperature in Celsius : %.2f C \n", cTemp);
		printk("Temperature in Fahrenheit : %.2f F \n", fTemp);
		k_msleep(SLEEP_TIME_MS);
	}
}
