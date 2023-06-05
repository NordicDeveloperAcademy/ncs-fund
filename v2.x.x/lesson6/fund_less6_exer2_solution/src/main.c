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

/* STEP 8 - Define the the addresses of relevant sensor registers and settings */
#define BH1749_SYSTEM_CONTROL                           0x40
#define BH1749_MODE_CONTROL1                            0x41
#define BH1749_MODE_CONTROL2                            0x42
#define BH1749_RED_DATA_LSB                             0x50
#define BH1749_MODE_CONTROL2_RGB_EN_ENABLE              BIT(4)
/* IR Gain: 1x, RGB Gain: 1x, Measurement mode: 120ms mode */
#define BH1749_MODE_CONTROL1_DEFAULTS                   0x2A

/* STEP 6 - Get the node identifier of the sensor */
#define I2C_NODE DT_NODELABEL(bh1749)

void main(void)
{

	int ret;

/* STEP 7 - Retrieve the API-specific device structure and make sure that the device is ready to use  */
	static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C_NODE);
	if (!device_is_ready(dev_i2c.bus)) {
		printk("I2C bus %s is not ready!\n\r",dev_i2c.bus->name);
		return;
	}

/* STEP 9 - Setup the sensor by writing the value 0x2A to the MODE_CONTROL1 register 
0x2A Means : IR Gain: 1x, RGB Gain: 1x, Measurement mode: 120ms mode
*/
	char buff1[] = {BH1749_MODE_CONTROL1,BH1749_MODE_CONTROL1_DEFAULTS};
	ret = i2c_write_dt(&dev_i2c,buff1,sizeof(buff1));
	if(ret != 0){
			printk("Failed to write to I2C device address 0x%c at Reg. 0x%c\n",dev_i2c.addr,BH1749_MODE_CONTROL1);
		}
/* STEP 10 - Enable measurement by writing 1 to bit 4 of the MODE_CONTROL2 register */
	char buff2[] = {BH1749_MODE_CONTROL2,BH1749_MODE_CONTROL2_RGB_EN_ENABLE};
	ret = i2c_write_dt(&dev_i2c,buff2,sizeof(buff2));
	if(ret != 0){
		printk("Failed to write to I2C device address 0x%c at Reg. 0x%c\n",dev_i2c.addr,BH1749_MODE_CONTROL2);
	}

	while (1) {
/* STEP 11 - Read the RGB values from the sensor */
		uint8_t rgb_value[6]= {0};//3 colour channels x 2 = 6
		//Do a burst read of 6 bytes as each color channel is 2 bytes. 
		ret = i2c_burst_read_dt(&dev_i2c, BH1749_RED_DATA_LSB,rgb_value,sizeof(rgb_value));
		if(ret != 0){
			printk("Failed to read to I2C device address 0x%c at Reg. 0x%c\n",dev_i2c.addr,BH1749_RED_DATA_LSB);
		}
		//Print reading to console  
		printk("_______________________________\n");
		printk("Red Value:\t %d\n", (rgb_value[0] | rgb_value[1] << 8));
		printk("Green Value:\t %d\n", (rgb_value[2] | rgb_value[3] << 8));
		printk("Blue Value:\t %d\n", (rgb_value[4] | rgb_value[5] << 8));

		k_msleep(SLEEP_TIME_MS);
	}
}
