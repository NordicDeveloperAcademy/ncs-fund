/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <sys/printk.h>
/* STEP 3 - Include the header file of the UART driver in main.c */

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* STEP 9.1.1 - Define the size of the receive buffer */

/* STEP 9.2 - Define the receiving timeout period */

/* STEP 5.1 - Get C identifiers for the DeviceTree labels and properties' values related to LEDs */

static const struct device *leds;

/* STEP 8.1 - Define the transmission buffer, which is a buffer to hold the data to be sent over UART */


/* STEP 9.1.2 - Define the receive buffer */


/* STEP 6 - Define the callback function for UART */

int main(void)
{
	int ret;
	leds = device_get_binding(LED0);
	if (leds == NULL) {
		return 1 ;
	}

/* STEP 4 - Get the device struct of the UART hardware */

/* STEP 5.2 - Configure the LEDs */

/* STEP 7 - Register the UART callback function */

/* STEP 8.2 - Send the data over UART by calling uart_tx() */

/* STEP 9.3  - Start receiving by calling uart_rx_enable() and pass it the address of the receive  buffer */

	while (1) {
		k_msleep(SLEEP_TIME_MS);
	}
}
