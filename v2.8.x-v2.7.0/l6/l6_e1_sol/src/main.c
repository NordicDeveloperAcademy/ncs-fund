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
#define DELAY_PARAM		50

#define BME_280_CHIP_ID		  0xD0

#define CTRLHUM 		0xF2
#define CTRLMEAS		0xF4
#define CALIB00			0x88
#define CALIB26			0xE1
#define ID				0xD0
#define PRESSMSB		0xF7
#define PRESSLSB		0xF8
#define PRESSXLSB		0xF9
#define TEMPMSB			0xFA
#define TEMPLSB			0xFB
#define TEMPXLSB		0xFC
#define HUMMSB			0xFD
#define HUMLSB			0xFE
#define DUMMY			0xFF

/* STEP 6 - Get the node identifier of the sensor */
#define I2C_NODE DT_NODELABEL(mysensor)


/* Data structure to store BME280 data */
struct bme280_data {
	/* Compensation parameters */
	uint16_t dig_t1;
	int16_t dig_t2;
	int16_t dig_t3;

	/* Compensated values */
	int32_t comp_temp;

	/* Carryover between temperature and pressure/humidity compensation */
	int32_t t_fine;

	uint8_t chip_id;
} bmedata;


void bme_calibrationdata(const struct i2c_dt_spec *spec)
{
	uint8_t values[3];
	uint8_t regaddr;

	regaddr = CALIB00;
	i2c_write_read_dt(spec,&regaddr, 1,values, 2);
	bmedata.dig_t1 = ((uint16_t)values[1])<<8 | values[0];
	k_msleep(DELAY_PARAM);

	regaddr += 2;
	i2c_write_read_dt(spec,&regaddr, 1,values, 2);
	bmedata.dig_t2 = ((uint16_t)values[1])<<8 | values[1];
	k_msleep(DELAY_PARAM);
	
	regaddr += 2;
	i2c_write_read_dt(spec,&regaddr, 1,values, 2);
	bmedata.dig_t3 = ((uint16_t)values[1])<<8 | values[1];
	k_msleep(DELAY_PARAM);

}
static int32_t bme280_compensate_temp(struct bme280_data *data, int32_t adc_temp)
{
	int32_t var1, var2;

	var1 = (((adc_temp >> 3) - ((int32_t)data->dig_t1 << 1)) *
		((int32_t)data->dig_t2)) >> 11;
	var2 = (((((adc_temp >> 4) - ((int32_t)data->dig_t1)) *
		  ((adc_temp >> 4) - ((int32_t)data->dig_t1))) >> 12) *
		((int32_t)data->dig_t3)) >> 14;

	data->t_fine = var1 + var2;
	return (data->t_fine * 5 + 128) >> 8;
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


	bme_calibrationdata(&dev_i2c);

	uint8_t id = 0;
	uint8_t regs[]= {BME_280_CHIP_ID};

	i2c_write_read_dt(&dev_i2c, regs,1,&id, 1);

	if( id != 0x60 )
	{
		printk("Invalid chip id %x \n", id);
	}

	regs[0] = CTRLHUM;

	uint8_t  reg_write[] ={CTRLHUM,0x04};
	i2c_write_dt(&dev_i2c,reg_write,2);

	reg_write[0] = CTRLMEAS;
	reg_write[1] = 0x93;

	i2c_write_dt(&dev_i2c,reg_write,2);

	while (1) {

		uint8_t temp_val[3]={0};

		i2c_burst_read_dt(&dev_i2c, TEMPMSB, temp_val, 3);

		int32_t adc_temp = (temp_val[0] << 12) | (temp_val[1] << 1) | ((temp_val[2] >> 4) & 0x0F);

		int32_t comp_temp = bme280_compensate_temp(&bmedata, adc_temp);
		float temperature = (float)comp_temp/100.0f;

		printk("Temperature: %8.2f C \n",(double)temperature);
		k_msleep(SLEEP_TIME_MS);
	}
}
