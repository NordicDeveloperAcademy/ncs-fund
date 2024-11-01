/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
/* STEP 3 - Include the header file of the I2C API */
#include <drivers/i2c.h>
/* STEP 4.1 - Include the header file of printk() */
#include <sys/printk.h>
/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* STEP 7 - Define the I2C slave device address and the addresses of relevant registers */
#define STTS751_TEMP_HIGH_REG            0x00
#define STTS751_TEMP_LOW_REG             0x02
#define STTS751_CONFIG_REG               0x03
#define STTS751_I2C_ADDRESS              0x4A

/* STEP 5 - Get the label of the I2C controller connected to your sensor */
/* The devicetree node identifier for the "i2c0" */
#define I2C0_NODE DT_NODELABEL(i2c0)
#if DT_NODE_HAS_STATUS(I2C0_NODE, okay)
#define I2C0	DT_LABEL(I2C0_NODE)
#else
/* A build error here means your board does not have I2C enabled. */
#error "i2c0 devicetree node is disabled"
#define I2C0	""
#endif
void main(void)
{

	int ret;

/* STEP 6 - Get the binding of the I2C driver  */
	const struct device *dev_i2c = device_get_binding(I2C0);
	if (dev_i2c == NULL) {
		printk("Could not find  %s!\n",I2C0);
		return;
	}
/* STEP 8 - Setup the sensor by writing the value 0x8C to the Configuration register */
	uint8_t config[2] = {STTS751_CONFIG_REG,0x8C};
	ret = i2c_write(dev_i2c, config, sizeof(config), STTS751_I2C_ADDRESS);
	if(ret != 0){
		printk("Failed to write to I2C device address %x at Reg. %x \n", STTS751_I2C_ADDRESS,config[0]);
	}

	while (1) {
/* STEP 9 - Read the temperature from the sensor */
		uint8_t temp_reading[2]= {0};
		uint8_t sensor_regs[2] ={STTS751_TEMP_LOW_REG,STTS751_TEMP_HIGH_REG};
		ret = i2c_write_read(dev_i2c,STTS751_I2C_ADDRESS,&sensor_regs[0],1,&temp_reading[0],1);
		if(ret != 0){
			printk("Failed to write/read I2C device address %x at Reg. %x \n", STTS751_I2C_ADDRESS,sensor_regs[0]);
		}
		ret = i2c_write_read(dev_i2c,STTS751_I2C_ADDRESS,&sensor_regs[1],1,&temp_reading[1],1);
		if(ret != 0){
			printk("Failed to write/read I2C device address %x at Reg. %x \n", STTS751_I2C_ADDRESS,sensor_regs[1]);
		}

/* STEP 10 - Convert the two bytes to a 12-bits */
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
