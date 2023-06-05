/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#ifdef CONFIG_MYFUNCTION
#include "myfunction.h"
#endif

void main(void)
{
	
	while(1){
		#ifdef CONFIG_MYFUNCTION
		int a = 3, b = 4;
			printk("The sum of %d and %d is %d\n\r", a, b, sum(a,b));
		#else
			printk("MYFUNCTION not enabled\r\n");
			return;
		#endif
		k_msleep(1000);
	}
}