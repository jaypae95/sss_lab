/* ----------------------------------------------------------------------------------------------------
*  ����: hook.h
*  ���	: hook.c�� �������
*  ������: 201520934 ������, ������ ������
*  ��¥	: 1�� ���� : 2018�� 5�� 24��
*----------------------------------------------------------------------------------------------------*/
#ifndef _HOOK_H_
#define _HOOK_H_

#define GPF_DISABLE()   write_cr0(read_cr0() & (~0x10000)) //����ŷ
#define GPF_ENABLE()    write_cr0(read_cr0() | 0x10000) //����ŷ ����

int hook_save(void); //hook_save����
int hook_start(void); //hook_start����
int hook_stop(void); //hook_stop����

#endif /* _HOOK_H_ */
