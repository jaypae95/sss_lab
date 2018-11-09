#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/syscalls.h>
#include <asm/unistd.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "hook.h"

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,31)
MODULE_LICENSE("GPL");
#endif


int init_module(void) //��� ��ġ �� �� ȣ���ϴ� �Լ�
{
	printk(KERN_INFO "Demo Hook Module loaded...\n");

	hook_save();
	hook_start();

	return 0;
}

void cleanup_module(void) //��� ���� �� �� ȣ���ϴ� �Լ�
{	
	printk(KERN_INFO "Demo Hook Module unloaded...\n");
	hook_stop();

	return;
}
