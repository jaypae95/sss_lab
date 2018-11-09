/* ----------------------------------------------------------------------------------------------------
*  ����: library_server.c
*  ���	: �α��� �� ������ ����� �ϴ� ����
*  ������: 201520934 ������
*  ��¥	: 1�� ���� : 2018�� 6�� 8��
*----------------------------------------------------------------------------------------------------*/
#include "fake_apue.h"

int library_server(char * _id) {
		char* lib_menu = (char*)malloc(10);
		char* list_menu = (char*)malloc(10);
		int fd;

		fp2 = fopen("./book_list.txt", "r+"); //���Ͽ���
		fp3 = fopen("./rent.txt", "a+"); //���Ͽ���
		while(1) {
				recv(s_c_sock, lib_menu, 10, 0); //Ŭ���̾�Ʈ�κ��� �޴������� ����
				if(lib_menu[0] == '1') { //1�� ���
						get_user_info(_id); //���� ���� �Լ� ȣ��
						send(s_c_sock, " ", 1, 0); //1�� ����� �����ٴ� �޽��� ����
				}
				else if(lib_menu[0] == '2') { //2�� ���
						char *message = "Book List Requested\0"; 
						send(s_c_sock, message, 30, 0);// ���� ���� ���� ����
							
						recv(s_c_sock, list_menu, 10, 0); //Ŭ���̾�Ʈ�� ���� ���� ���� �޴������� ����
						if(list_menu[0] == '1') { //1�ϰ��
								get_book_info_all(); //��ü ���� ���� �Լ� ȣ��
						}
						else if(list_menu[0] == '2') { //2�� ���
								get_book_info_select(); //���� ���� ���� �Լ� ȣ��
						}
					
						send(s_c_sock, " ", 1, 0); //2�� ����� �����ٴ� �޽����� ����
				}
				else if(lib_menu[0] == '3') { //3�� ���
						char *message = "Rental Requested\0";
						char *book_name = (char *)malloc(100);

						send(s_c_sock, message, 30, 0); //���� �뿩 ���� ����
						
						usleep(1);
						
						get_book_info_all(); //��ü ���� ���� �Լ� ȣ��
						
						recv(s_c_sock, book_name, 100, 0); //���� �̸��� ����
						
						book_rental(book_name, _id); //���� ���� ���� �Լ� ȣ��

						send(s_c_sock, " ", 1, 0); //3�� ����� �����ٴ� �޽����� ����
				}
				else if(lib_menu[0] == '4') { //4�� ���
						char *message = "Return Requested\0";
						send(s_c_sock, message, 30, 0); //���� �ݳ� ���� ����
						
						usleep(1000);
						book_return(_id); //���� �ݳ� �Լ� ȣ��
						send(s_c_sock, " ", 1, 0); //4�� ����� �����ٴ� �޽����� ����
				}
				else if(lib_menu[0] == '5') { //5�� ���
						char * message = "EXIT Requested\0";
						send(s_c_sock, message, 30, 0); //�α׾ƿ�(����) ���� ����
						
						close(s_c_sock); //���� ����
						return 0;
				}
				else {
						char *message = "Wrong Input\0";
						send(s_c_sock, message, 30, 0);
						
				}
		}
}
