/* ----------------------------------------------------------------------------------------------------
*  ����: info.c
*  ���	: ����/���� ���� ���� ����
*  ������: 201520934 ������
*  ��¥	: 1�� ���� : 2018�� 6�� 8��
*----------------------------------------------------------------------------------------------------*/
#include "fake_apue.h"



int get_user_info(char *_id) {
		char *num = (char*)malloc(20);
		char *name = (char*)malloc(20);
		char *major = (char*)malloc(20);
		
		memset(num, 0, 20);
		memset(name, 0, 20);
		memset(major, 0, 20);
		char *message = "User Info. Requested\0"; 
		send(s_c_sock, message, 30, 0); //���� ���� ���� ����
		usleep(10);
		fscanf(fp,"%s %s %s\n", num, name, major); //�α����� �� �� ���� ������ ���̵� �н����带 �о� �� ����
												//�����¿��� ���� ������ �� �޾ƿ´�.
		fseek(fp, -(strlen(num)+strlen(name)+strlen(major)+3), SEEK_CUR); //�޾ƿ� ��ŭ ���� �������ν� �ٽ� ���� ����
																		// �Լ��� ȣ���ص� �״�� �о�� �� �ֵ��� �Ѵ�.

		send(s_c_sock, num, 20, 0); //�й�
		send(s_c_sock, name, 20, 0); //�̸�
		send(s_c_sock, major, 20, 0); //�а��� Ŭ���̾�Ʈ�� ����
		
		free(num);
		free(name);
		free(major);
		
		return 0;
}

int get_book_info_all() {
		char *book_info = (char*)malloc(256);
		
		fseek(fp2, 0, SEEK_SET); //�������� ó������ ����
		while(fgets(book_info, 256, fp2) >0){ //���� �� �о���鼭
				send(s_c_sock, book_info, 256, 0); //å ������ Ŭ���̾�Ʈ�� ����
				usleep(1000);
				memset(book_info, 0 , 256);
		}
		send(s_c_sock, "done\0", 256, 0); //done �޽����� ����
		
		return 0;
}

int get_book_info_select() {
		char *book_info = (char*)malloc(256);
		char *book_name = (char*)malloc(100);
		int exist =0;
		
		fseek(fp2, 0, SEEK_SET); //���� ��ġ�� ó������ ����
		recv(s_c_sock, book_name, 100, 0); //���� �̸��� �޾ƿ�
		while(fgets(book_info, 256, fp2) >0) { //�� �پ� �о���鼭
				book_info[strlen(book_info)-10] = '\0'; //, 0001, V\n ���� �Ǿտ� ,�ڸ��� null
				if(!strcmp(book_info, book_name)) { //���� �̸� ���ؼ� ��ġ�ϸ�
				exist = 1; //����
				send(s_c_sock, book_name, 100, 0); //���� �̸� ����
				send(s_c_sock, book_info+(strlen(book_info)+8), 10, 0); //���� �뿩 ���� ���� ���� ����
				break;
				}
		}
		if(exist == 0) { //�������� ������
				send(s_c_sock, "Not exist\0", 100, 0); //�������� �ʴ´ٴ� �޽��� ����
		}
		
		free(book_name);
		free(book_info);
		return 0;
}

