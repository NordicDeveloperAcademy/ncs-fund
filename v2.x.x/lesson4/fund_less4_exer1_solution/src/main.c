/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
/* STEP 6 - Include the header file of printk */
#include <zephyr/sys/printk.h>

/* STEP 8.1 - Define the macro MAX_NUMBER_FACT that represents the maximum number to calculate its factorial  */
#define MAX_NUMBER_FACT 10

#define SLEEP_TIME_MS   10*60*1000

#define SW0_NODE	DT_ALIAS(sw0)
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

/* STEP 8.2 - Replace the button callback function */
void button_pressed(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
  int i;
  int j;
  long int factorial;
  printk("Calculating the factorials of numbers from 1 to %d:\n\r",MAX_NUMBER_FACT);
  for (i=1;i<=MAX_NUMBER_FACT;i++){
	   factorial =1;
	    for (j=1;j<=i;j++){
			factorial = factorial*j;
		}
		printk("The factorial of %2d = %ld\n\r",i,factorial);
  }
  printk("_______________________________________________________\n\r");
  /*Important note! 
  Code in ISR runs at a high priority, therefore, it should be written with timing in mind.
  Too lengthy or too complex tasks should not be performed by an ISR, they should be deferred to a thread. 
  */
}

static struct gpio_callback button_cb_data;

void main(void)
{
	int ret;
	/* STEP 7 - Print a simple banner */
	printk("nRF Connect SDK Fundamentals - Lesson 4 - Exercise 1\n\r");

	/* Only checking one since led.port and button.port point to the same device, &gpio0 */
	if (!device_is_ready(led.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret < 0) {
		return;
	}

	ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);

	gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));	

	gpio_add_callback(button.port, &button_cb_data);	
	while (1) {
        k_msleep(SLEEP_TIME_MS); 
	}
}