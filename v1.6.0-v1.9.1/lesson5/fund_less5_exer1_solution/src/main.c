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
#include <drivers/uart.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* STEP 9.1.1 - Define the size of the receive buffer */
#define RECEIVE_BUFF_SIZE 10

/* STEP 9.2 - Define the receiving timeout period */
#define RECEIVE_TIMEOUT 100

/* STEP 5.1 - Get C identifiers for the DeviceTree labels and properties' values related to LEDs */
#define LED0_NODE 	DT_ALIAS(led0)
#define LED0		DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN0		DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAG0		DT_GPIO_FLAGS(LED0_NODE, gpios)

#define LED1_NODE 	DT_ALIAS(led1)
#define LED1		DT_GPIO_LABEL(LED1_NODE, gpios)
#define PIN1		DT_GPIO_PIN(LED1_NODE, gpios)
#define FLAG1		DT_GPIO_FLAGS(LED1_NODE, gpios)

#define LED2_NODE 	DT_ALIAS(led2)
#define LED2		DT_GPIO_LABEL(LED2_NODE, gpios)
#define PIN2		DT_GPIO_PIN(LED2_NODE, gpios)
#define FLAG2		DT_GPIO_FLAGS(LED2_NODE, gpios)

static const struct device *leds;

/* STEP 8.1 - Define the transmission buffer, which is a buffer to hold the data to be sent over UART */
static uint8_t tx_buf[] =   {"nRF Connect SDK Fundamentals Course\n"
                             "Press 1-3 on your keyboard to toggle LEDS 1-3 on your development kit\n"};

/* STEP 9.1.2 - Define the receive buffer */
static uint8_t rx_buf[RECEIVE_BUFF_SIZE] = {0};


/* STEP 6 - Define the callback function for UART */
static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
{
	switch (evt->type) {

	case UART_RX_RDY:
		if((evt->data.rx.len) == 1){

		if(evt->data.rx.buf[evt->data.rx.offset] == '1')
			gpio_pin_toggle(leds,PIN0);
		else if (evt->data.rx.buf[evt->data.rx.offset] == '2')
			gpio_pin_toggle(leds,PIN1);
		else if (evt->data.rx.buf[evt->data.rx.offset] == '3')
			gpio_pin_toggle(leds,PIN2);					
		break;
		}
	case UART_RX_DISABLED:
		uart_rx_enable(dev ,rx_buf,sizeof rx_buf,RECEIVE_TIMEOUT);
		break;
		
	default:
		break;
	}
}

int main(void)
{
	int ret;
	leds = device_get_binding(LED0);
	if (leds == NULL) {
		return 1 ;
	}

/* STEP 4 - Get the device struct of the UART hardware */
	const struct device *uart= device_get_binding(DT_LABEL(DT_NODELABEL(uart0)));
	if (uart== NULL) {
		printk("Could not find  %s!\n",DT_LABEL(DT_NODELABEL(uart0)));
		return 1 ;
	}
/* STEP 5.2 - Configure the LEDs */
	ret = gpio_pin_configure(leds, PIN0, GPIO_OUTPUT_ACTIVE | FLAG0);
	if (ret < 0) {
		return 1 ; 
	}
	ret = gpio_pin_configure(leds, PIN1, GPIO_OUTPUT_ACTIVE | FLAG1);
	if (ret < 0) {
		return 1 ;
	}
	ret = gpio_pin_configure(leds, PIN2, GPIO_OUTPUT_ACTIVE | FLAG2);
	if (ret < 0) {
		return 1 ;
	}
/* STEP 7 - Register the UART callback function */
	ret = uart_callback_set(uart, uart_cb, NULL);
		if (ret) {
			return 1;
		}
/* STEP 8.2 - Send the data over UART by calling uart_tx() */
	ret = uart_tx(uart, tx_buf, sizeof(tx_buf), SYS_FOREVER_MS);
	if (ret) {
		return 1;
	}
/* STEP 9.3  - Start receiving by calling uart_rx_enable() and pass it the address of the receive  buffer */
	ret = uart_rx_enable(uart ,rx_buf,sizeof rx_buf,RECEIVE_TIMEOUT);
	if (ret) {
		return 1;
	}
	while (1) {
		k_msleep(SLEEP_TIME_MS);
	}

}