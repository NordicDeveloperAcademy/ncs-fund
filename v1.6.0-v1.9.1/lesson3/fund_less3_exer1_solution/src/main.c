/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr.h>
#include <sys/printk.h>


void main(void)
{
	while(1) {
		printk("Hello World!\n");
		k_msleep(1000);
	}
}