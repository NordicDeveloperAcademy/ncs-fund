/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

/* STEP 9 - Increase the main thread sleep time from 100ms to 10 minutes  */
#define SLEEP_TIME_MS   100

#define SW0_NODE    DT_ALIAS(sw0)

#if DT_NODE_HAS_STATUS(SW0_NODE, okay)
#define SW0_GPIO_LABEL  DT_GPIO_LABEL(SW0_NODE, gpios)
#define SW0_GPIO_PIN    DT_GPIO_PIN(SW0_NODE, gpios)
#define SW0_GPIO_FLAGS  DT_GPIO_FLAGS(SW0_NODE, gpios)
#else
#error "Unsupported board: sw0 devicetree alias is not defined"
#define SW0_GPIO_LABEL  ""
#define SW0_GPIO_PIN    0
#define SW0_GPIO_FLAGS  0
#endif

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN	DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS	DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0	""
#define PIN	0
#define FLAGS	0
#endif
/* STEP 5 - Define the callback function */

/* STEP 3 - Define a variable of type static struct gpio_callback */

void main(void)
{
	const struct device *dev;
	int ret;

	dev = device_get_binding(LED0);
	if (dev == NULL) {
		return;
	}

	ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret < 0) {
		return;
	}
    ret = gpio_pin_configure(dev, SW0_GPIO_PIN, GPIO_INPUT | SW0_GPIO_FLAGS);
    if (ret < 0) {
        return;
    }
	/* STEP 4 - Configure the interrupt on the pin by calling the function gpio_pin_interrupt_configure()  */
	
	/* STEP 6 - Initialize the static struct gpio_callback variable   */
	
	/* STEP 7 - Add the callback function by calling gpio_add_callback()   */
	
	while (1) {
		/* STEP 8 - Remove the polling code */
        bool val; //A variable that stores the status of the button (pressed = 1 , unpressed = 0)
        val = gpio_pin_get(dev, SW0_GPIO_PIN); //Read the status of the button
        gpio_pin_set(dev, PIN, val); //Update the LED to the status of the button
        k_msleep(SLEEP_TIME_MS); // Put the CPU to sleep for 100ms so it does not consume power	
	}
}