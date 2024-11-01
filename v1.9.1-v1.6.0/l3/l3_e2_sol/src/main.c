/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr.h>
#include <sys/printk.h>
//#include "myfunction.h"

void main(void)
{
	int a = 3, b = 4;
	while(1){
		if(!(IS_ENABLED(CONFIG_MYFUNCTION))){
			printk("MYFUNCTION not enabled\n");
			return;
		}
		printk("The sum of %d and %d is %d\n", a, b, sum(a,b));
		k_msleep(1000);
	}
}