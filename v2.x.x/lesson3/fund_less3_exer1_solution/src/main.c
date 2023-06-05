/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>


void main(void)
{
	while(1) {
		printk("Hello World!\n\r");
		k_msleep(1000);
	}
}