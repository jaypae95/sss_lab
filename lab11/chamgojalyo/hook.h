/* ----------------------------------------------------------------------------------------------------
*  파일: hook.h
*  기능	: hook.c의 헤더파일
*  개발자: 201520934 배재훈, 현만석 조교님
*  날짜	: 1차 개발 : 2018년 5월 24일
*----------------------------------------------------------------------------------------------------*/
#ifndef _HOOK_H_
#define _HOOK_H_

#define GPF_DISABLE()   write_cr0(read_cr0() & (~0x10000)) //마스킹
#define GPF_ENABLE()    write_cr0(read_cr0() | 0x10000) //마스킹 해제

int hook_save(void); //hook_save선언
int hook_start(void); //hook_start선언
int hook_stop(void); //hook_stop선언

#endif /* _HOOK_H_ */
