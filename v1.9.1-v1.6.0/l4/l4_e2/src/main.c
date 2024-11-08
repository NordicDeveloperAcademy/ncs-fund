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
/* STEP 4 - Include the header file of the logger module */


#define MAX_NUMBER_FACT 10
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

/* STEP 5 - Register your code with the logger */


/* STEP 7 - Replace the callback function button_pressed() */
void button_pressed(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
  int i;
  int j;
  long int factorial;
  printk("Calculating the factorials of numbers from 1 to %d:\n",MAX_NUMBER_FACT);
  for (i=1;i<=MAX_NUMBER_FACT;i++){
	   factorial =1;
	    for (j=1;j<=i;j++){
			factorial = factorial*j;
		}
		printk("The factorial of %2d = %ld\n",i,factorial);
  }
  printk("_______________________________________________________\n");
  /*Important note! 
  Code in ISR runs at a high priority, therefore, it should be written with timing in mind.
  Too lengthy or too complex tasks should not be performed by an ISR, they should be deferred to a thread. 
  */
}

static struct gpio_callback button_cb_data;

void main(void)
{
	const struct device *dev;
	int ret;
	/* STEP 6 - Write some logs */
	printk("nRF Connect SDK Fundamentals - Lesson 4 - Exercise 1\n");

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