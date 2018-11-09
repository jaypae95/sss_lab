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


int init_module(void) //모듈 설치 할 때 호출하는 함수
{
	printk(KERN_INFO "Demo Hook Module loaded...\n");

	hook_save();
	hook_start();

	return 0;
}

void cleanup_module(void) //모듈 삭제 할 때 호출하는 함수
{	
	printk(KERN_INFO "Demo Hook Module unloaded...\n");
	hook_stop();

	return;
}
