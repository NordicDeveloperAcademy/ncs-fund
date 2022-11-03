#include <zephyr.h>
#include <sys/printk.h>


void main(void)
{
	while(1) {
		printk("Hello World!\n\r");
		k_msleep(1000);
	}
}