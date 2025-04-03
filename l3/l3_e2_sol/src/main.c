/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/* STEP 4 - Include the header file for the custom function */
// include "myfunction.h"

/* STEP 9.1 - Check CONFIG_MYFUNCTION before including the header file */
#ifdef CONFIG_MYFUNCTION
#include "myfunction.h"
#endif

/* STEP 9.2 - Check CONFIG_MYFUNCTION before calling sum() */
int main(void)
{
	while (1) {
#ifdef CONFIG_MYFUNCTION
		int a = 3, b = 4;
		printk("The sum of %d and %d is %d\n", a, b, sum(a, b));
#else
		printk("MYFUNCTION not enabled\n");
		return 0;
#endif
		k_msleep(1000);
	}
	return 0;
}

/* STEP 5 - Change main() to run the custom function */
/*int main(void)
{
	int a = 3, b = 4;
	while(1){
		printk("The sum of %d and %d is %d\n", a, b, sum(a,b));
		k_msleep(1000);
	}
}*/