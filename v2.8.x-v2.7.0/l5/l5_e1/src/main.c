/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Controlling LEDs through UART. Press 1-3 on your keyboard to toggle LEDS 1-3 on your development
 * kit */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
/* STEP 3 - Include the header file of the UART driver in main.c */

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

/* STEP 10.1.1 - Define the size of the receive buffer */

/* STEP 10.2 - Define the receiving timeout period */

/* STEP 5.1 - Get the device pointers of the LEDs through gpio_dt_spec */

/* STEP 4.1 - Get the device pointer of the UART hardware */

/* STEP 9.1 - Define the transmission buffer, which is a buffer to hold the data to be sent over
 * UART */

/* STEP 10.1.2 - Define the receive buffer */

/* STEP 7 - Define the callback function for UART */

int main(void)
{
	int ret;

	/* STEP 4.2 - Verify that the UART device is ready */

	/* STEP 5.2 - Verify that the LED devices are ready */

	/* STEP 6 - Configure the GPIOs of the LEDs */

	/* STEP 8 - Register the UART callback function */

	/* STEP 9.2 - Send the data over UART by calling uart_tx() */

	/* STEP 10.3  - Start receiving by calling uart_rx_enable() and pass it the address of the
	 * receive  buffer */

	while (1) {
		k_msleep(SLEEP_TIME_MS);
	}
}