/* ----------------------------------------------------------------------------------------------------
*  파일: hook.c
*  기능	: 후킹 모듈을 위한 프로그램
*  개발자: 201520934 배재훈, 현만석 조교님
*  날짜	: 1차 개발 : 2018년 5월 24일
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
asmlinkage long (*org_open)(char *buf, int flags, mode_t mode); //org_open함수 선언
asmlinkage long (*org_read)(unsigned int fd, char __user *buf, size_t count); //org_read함수 선언

#define IN_USER         0x01 //유저
#define IN_KERNEL       0x00 //커널
#define KEY_BACKSPACE   0x7f //백스페이스
/*
 * new system call function (fork, vfork, clone, execve, open)
 */
asmlinkage long new_open(char __user *filename, int flags, mode_t mode) //후킹 후의 open
{
	long ret;

	ret = (*org_open)(filename, flags, mode); //원래의 open함수 호출
	if (!strcmp(filename, "./target.txt")) { //파일이 target.txt일 경우
			ret = -1; //ret값 = -1
			printk(KERN_INFO "target.txt open\n"); //커널 메시지 출력
	}
	
	return ret;	//ret값 리턴(target.txt일 때 target.txt가 존재함에도 불구하고 -1을 리턴)
}

asmlinkage long new_read(unsigned int fd, char __user *buf, size_t count){ //후킹 후의 read
	long ret;
	ret = (*org_read)(fd, buf, count); //원래의 read함수 호출
	if(fd == 0){ //stdin인 결우
			if(*buf == KEY_BACKSPACE) //백 스페이스를 눌렀을 경우(원래 이상한 문구가 출력됨)
					printk(KERN_INFO "BACKSPACE\n"); //BACKSPACE문구를 커널에다 출력
			else printk(KERN_INFO "buf : %s\n", buf); //buv값을 커널에다 출력
	}
	return ret; //ret값 반환
}
int hook_save(void) //기존 함수 저장
{
	printk(KERN_INFO "%s : save start\n", __func__);

	org_open = org_syscall_table[__NR_open]; //기존 open시스템콜 저장
	org_read = org_syscall_table[__NR_read]; //기존 read시스템콜 저장


	return 0;
}

int hook_start(void)
{
	printk(KERN_INFO "%s : start start\n", __func__); 

	GPF_DISABLE(); //후킹을 시작 할 때 걸어줌(이 것을 하지 않으면 write에 의한 시스템 오류가 날 수 있음)

	org_syscall_table[__NR_open] = (void *)new_open; //new_open을 기존 open위치에 저장
	org_syscall_table[__NR_read] = (void *)new_read; //new_read를 기존 read위치에 저장
	
	GPF_ENABLE(); //걸어준 것을 풀어줌

	return 0;
}

int hook_stop(void)
{
	printk(KERN_INFO "%s : stop start\n", __func__);

	GPF_DISABLE();
	org_syscall_table[__NR_open] = (void *)org_open; //기존 open을 다시 테이블에 저장
	org_syscall_table[__NR_read] = (void *)org_read; //기존 read를 다시 테이블에 저장
	GPF_ENABLE();

	return 0;
}
