/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <string.h>
// Define stack size used by each thread
#define THREAD0_STACKSIZE       512
#define THREAD1_STACKSIZE       512
#define WORQ_THREAD_STACK_SIZE  512

/* STEP 2 - Set the priorities of the threads */
#define THREAD0_PRIORITY 2 
#define THREAD1_PRIORITY 3
#define WORKQ_PRIORITY   4

// Define stack area used by workqueue thread
static K_THREAD_STACK_DEFINE(my_stack_area, WORQ_THREAD_STACK_SIZE);

// Define queue structure
static struct k_work_q offload_work_q = {0};


/* STEP 5 - Define function to emulate non-urgent work */
static inline void emulate_work()
{
	for(volatile int count_out = 0; count_out < 150000; count_out ++);
}

/* STEP 7 - Create work_info structure and offload function */
struct work_info {
    struct k_work work;
    char name[25];
} my_work;

void offload_function(struct k_work *work_tem)
{
	emulate_work();
}

void thread0(void)
{
    uint64_t time_stamp;
    int64_t delta_time;
	/* STEP 8 - Start the workqueue, */
	/* initialize the work item and connect it to its handler function */ 
	k_work_queue_start(&offload_work_q, my_stack_area,
					K_THREAD_STACK_SIZEOF(my_stack_area), WORKQ_PRIORITY,
					NULL);
	strcpy(my_work.name, "Thread0 emulate_work()");
	k_work_init(&my_work.work, offload_function);
    while (1) {
        time_stamp = k_uptime_get();
		/* STEP 9 - Submit the work item to the workqueue instead of calling emulate_work() directly */
		/* Remember to comment out emulate_work(); */
        k_work_submit_to_queue(&offload_work_q, &my_work.work);
        delta_time = k_uptime_delta(&time_stamp);
        printk("thread0 yielding this round in %lld ms\n", delta_time);
        k_msleep(20);
    }   
}

/* STEP 4 - Define entry function for thread1 */
void thread1(void)
{
    uint64_t time_stamp;
    int64_t delta_time;

    while (1) {
        time_stamp = k_uptime_get();
        emulate_work();
        delta_time = k_uptime_delta(&time_stamp);

        printk("thread1 yielding this round in %lld ms\n", delta_time);
        k_msleep(20);
    }   
}

K_THREAD_DEFINE(thread0_id, THREAD0_STACKSIZE, thread0, NULL, NULL, NULL,
		THREAD0_PRIORITY, 0, 0);
K_THREAD_DEFINE(thread1_id, THREAD1_STACKSIZE, thread1, NULL, NULL, NULL,
		THREAD1_PRIORITY, 0, 0);

