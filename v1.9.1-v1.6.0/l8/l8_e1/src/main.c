/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <sys/printk.h>
#include <sys/__assert.h>
#include <kernel.h>
#include <kernel_structs.h>
#include <string.h>
#include <random/rand32.h>

#define PRODUCER_STACKSIZE       512
#define CONSUMER_STACKSIZE       512

/* STEP 2 - Set the priority of the producer and consumper thread */

/* STEP 9 - Define semaphore to monitor instances of available resource */

/* STEP 3 - Initialize the available instances of this resource */

// Function for getting access of resource
void get_access(void)
{
	/* STEP 10.1 - Get semaphore before access to the resource */

	/* STEP 6.1 - Decrement available resource */

}

// Function for releasing access of resource
void release_access(void)
{
	/* STEP 6.2 - Increment available resource */

	/* STEP 10.2 - Give semaphore after finishing access to resource */

}

/* STEP 4 - Producer thread relinquishing access to instance */
void producer(void)
{

}

/* STEP 5 - Consumer thread obtaining access to instance */
void consumer(void)
{

}

// Define and initialize threads
K_THREAD_DEFINE(producer_id, PRODUCER_STACKSIZE, producer, NULL, NULL, NULL,
		PRODUCER_PRIORITY, 0, 0);

K_THREAD_DEFINE(consumer_id, CONSUMER_STACKSIZE, consumer, NULL, NULL, NULL,
		CONSUMER_PRIORITY, 0, 0);