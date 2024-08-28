/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/* STEP 2 - Define stack size and scheduling priority used by each thread */

void thread0(void)
{
	while (1) {
		/* STEP 3 - Call printk() to display a simple string "Hello, I am thread0" */
		/* STEP 6 - Make the thread yield */
		/* STEP 10 - Put the thread to sleep */
		/* Remember to comment out the line from STEP 6 */
	}
}

void thread1(void)
{
	while (1) {
		/* STEP 3 - Call printk() to display a simple string "Hello, I am thread1" */
		/* STEP 8 - Make the thread yield */
		/* STEP 10 - Put the thread to sleep */
		/* Remember to comment out the line from STEP 8 */
	}
}

/* STEP 4 - Define and initialize the two threads */