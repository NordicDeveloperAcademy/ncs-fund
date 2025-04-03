/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
/* STEP 6 - Include the header file of printk */

/* STEP 8.1 - Define the macro MAX_NUMBER_FACT that represents the maximum number to calculate its factorial  */

#define SLEEP_TIME_MS   10*60*1000

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
/* STEP 8.2 - Replace the button callback function */
void button_pressed(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
	gpio_pin_toggle(dev,PIN);
}

static struct gpio_callback button_cb_data;

void main(void)
{
	const struct device *dev;
	int ret;
	/* STEP 7 - Print a simple banner */

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

    ret = gpio_pin_interrupt_configure(dev,
                       SW0_GPIO_PIN,
                       GPIO_INT_EDGE_TO_ACTIVE | GPIO_INT_DEBOUNCE);	

	gpio_init_callback(&button_cb_data, button_pressed, BIT(SW0_GPIO_PIN));	

	gpio_add_callback(dev, &button_cb_data);	
	while (1) {
        k_msleep(SLEEP_TIME_MS); 
	}
}