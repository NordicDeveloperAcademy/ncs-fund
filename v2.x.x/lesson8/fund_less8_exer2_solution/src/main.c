/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/random/rand32.h>
#include <string.h>

#define THREAD0_STACKSIZE       512
#define THREAD1_STACKSIZE       512

/* STEP 3 - Set the priority of the two threads to have equal priority*/
#define THREAD0_PRIORITY 4 
#define THREAD1_PRIORITY 4

/* STEP 5 - Define the two counters with a constant combined total */
#define COMBINED_TOTAL   40

int32_t increment_count = 0; 
int32_t decrement_count = COMBINED_TOTAL; 

/* STEP 11 - Define mutex to protect access to shared code section */
K_MUTEX_DEFINE(test_mutex);

// Shared code run by both threads
void shared_code_section(void)
{
	/* STEP 12.1 - Lock the mutex */
	k_mutex_lock(&test_mutex, K_FOREVER);

	/* STEP 6 - Increment count and decrement count changed */
	/* according to logic defined in exercise text */
	increment_count += 1;
	increment_count = increment_count % COMBINED_TOTAL; 

	decrement_count -= 1;
	if (decrement_count == 0) 
	{
		decrement_count = COMBINED_TOTAL;
	}

	/* STEP 12.2 - Unlock the mutex */
	k_mutex_unlock(&test_mutex);

	/* STEP 7 - Print counter values if they do not add up to COMBINED_TOTAL */
	if(increment_count + decrement_count != COMBINED_TOTAL )
	{
		printk("Race condition happend!\n");
		printk("Increment_count (%d) + Decrement_count (%d) = %d \n",
	                increment_count, decrement_count, (increment_count + decrement_count));
		k_msleep(400 + sys_rand32_get() % 10);
	}
}

/* STEP 4 - Functions for thread0 and thread1 with a shared code section */
void thread0(void)
{
	printk("Thread 0 started\n");
	while (1) {
		shared_code_section(); 
	}
}

void thread1(void)
{
	printk("Thread 1 started\n");
	while (1) {
		shared_code_section(); 
	}
}

// Define and initialize threads
K_THREAD_DEFINE(thread0_id, THREAD0_STACKSIZE, thread0, NULL, NULL, NULL,
		THREAD0_PRIORITY, 0, 5000);

K_THREAD_DEFINE(thread1_id, THREAD1_STACKSIZE, thread1, NULL, NULL, NULL,
		THREAD1_PRIORITY, 0, 5000);

