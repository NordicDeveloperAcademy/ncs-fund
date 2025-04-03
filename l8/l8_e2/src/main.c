/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "ncs_version.h"
#if NCS_VERSION_NUMBER < 0x20600
#include <zephyr/random/rand32.h>
#else 
#include <zephyr/random/random.h>
#endif
#include <string.h>

#define THREAD0_STACKSIZE 1024
#define THREAD1_STACKSIZE 1024

/* STEP 3 - Set the priority of the two threads to have equal priority*/

/* STEP 5 - Define the two counters with a constant combined total */

/* STEP 11 - Define mutex to protect access to shared code section */

// Shared code run by both threads
void shared_code_section(void)
{
	/* STEP 12.1 - Lock the mutex */

	/* STEP 6 - Increment count and decrement count changed */
	/* according to logic defined in exercise text */

	/* STEP 12.2 - Unlock the mutex */

	/* STEP 7 - Print counter values if they do not add up to COMBINED_TOTAL */
}

/* STEP 4 - Functions for thread0 and thread1 with a shared code section */

// Define and initialize threads
K_THREAD_DEFINE(thread0_id, THREAD0_STACKSIZE, thread0, NULL, NULL, NULL, THREAD0_PRIORITY, 0,
		5000);

K_THREAD_DEFINE(thread1_id, THREAD1_STACKSIZE, thread1, NULL, NULL, NULL, THREAD1_PRIORITY, 0,
		5000);
