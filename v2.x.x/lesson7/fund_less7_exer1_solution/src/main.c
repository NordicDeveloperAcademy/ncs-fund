/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/* STEP 2 - Define stack size and scheduling priority used by each thread */
#define STACKSIZE 1024

#define THREAD0_PRIORITY 7
#define THREAD1_PRIORITY 7

void thread0(void)
{
	while (1) {
		  /* STEP 3 - Call printk() to display a simple string "Hello, I am thread0" */
		  printk("Hello, I am thread0\n");
		  /* STEP 6 - Make the thread yield */
          //k_yield();
		  /* STEP 10 - Put the thread to sleep */
		  k_msleep(5);
		  /* Remember to comment out the line from STEP 6 */
	}
}

void thread1(void)
{
	while (1) {
		  /* STEP 3 - Call printk() to display a simple string "Hello, I am thread1" */
          printk("Hello, I am thread1\n");		  
		  /* STEP 8 - Make the thread yield */
		  //k_yield();		  
		  /* STEP 10 - Put the thread to sleep */
		  k_msleep(5);
		  /* Remember to comment out the line from STEP 8 */
	}
}

/* STEP 4 - Define and initialize the two threads */
K_THREAD_DEFINE(thread0_id, STACKSIZE, thread0, NULL, NULL, NULL,
		THREAD0_PRIORITY, 0, 0);
K_THREAD_DEFINE(thread1_id, STACKSIZE, thread1, NULL, NULL, NULL,
		THREAD1_PRIORITY, 0, 0);