/* ----------------------------------------------------------------------------------------------------
*  ����: server.c
*  ���	: ������ �������/�α��� ����
*  ������: 201520934 ������
*  ��¥	: 1�� ���� : 2018�� 6�� 8��
*----------------------------------------------------------------------------------------------------*/
#include "fake_apue.h"

int _server() {
		char menu;
		char *_id = (char*)malloc(sizeof(char)*20);
		char *_pwd = (char*)malloc(sizeof(char)*20);
		char *pwd = (char*)malloc(sizeof(char)*20);
		char *id = (char*)malloc(sizeof(char)*20);
		char *num = (char*)malloc(sizeof(char)*20);
		char *name = (char*)malloc(sizeof(char)*20);
		char *major = (char*)malloc(sizeof(char)*20);
		char *_else = (char*)malloc(sizeof(char)*100);
		fp = fopen("./user_data.txt", "a+"); //���� ����
		int exist = 0, not_pwd=0;
		while(1) {
				exist = 0;
				recv(s_c_sock, &menu, sizeof(char), 0);  //Ŭ���̾�Ʈ�� ���� �޴� ������ ����
				if(menu == '1') { //1�� ���
						char *message = "Sign Up Requested\0";
						send(s_c_sock, message, strlen(message), 0); //��� ���� ���� ����
						
						while(1) {
								memset(id, 0, 20);
								recv(s_c_sock, id, sizeof(char)*20, 0); //Ŭ���̾�Ʈ���� ���̵� ����
								fseek(fp, 0, SEEK_SET); //������ �������� ó������ ����
								while(fscanf(fp, "%s", _id) > 0) { //������ �� ó�� ���ڸ� ����
										//_id[strlen(id-1] = '\0';
										if(!strcmp(id, _id)) { //id�� ���ؼ� ��ġ�ϸ�
												send(s_c_sock, "exist\0", sizeof(char)*10, 0);
												exist = 1; //����
												break;
										}
										exist = 0; //not exist
										fgets(_else, 100, fp); //������ ���� �о� ����(���� ���� ù��° ���ڸ� �о�� �� �ֵ���)
										memset(_id, 0, sizeof(char)*20);
								}
								if(exist == 0) { //not exist untill the end >> successed
										send(s_c_sock, "not exist\0", sizeof(char)*10, 0); //�������� �ʴ´ٴ� �޽����� ����
										recv(s_c_sock, pwd, sizeof(char)*20, 0); //��й�ȣ
										recv(s_c_sock, num, sizeof(char)*20, 0); //�й�
										recv(s_c_sock, name, sizeof(char)*20, 0); //�̸�
										recv(s_c_sock, major, sizeof(char)*20, 0); //�а��� Ŭ���̾�Ʈ�� ���� ����
										fseek(fp, 0, SEEK_END);
										fprintf(fp, "%s %s %s %s %s\n", id, pwd, num, name, major); //�������� ���Ͽ� ���
										fflush(fp);
										break;
								}
								else continue;
						}
				}
				else if(menu == '2') { //2�� ���
						memset(id, 0, 20);
						memset(pwd, 0, 20);
						exist = 0;
						char *message = "Sign In Requested\0";
						send(s_c_sock, message, strlen(message), 0); //�α��� ���� �޽��� ����
						
						while(1) {
								recv(s_c_sock, _id, sizeof(char)*20, 0); //Ŭ���̾�Ʈ�κ��� ���̵��
								recv(s_c_sock, _pwd, sizeof(char)*20, 0); //��й�ȣ�� ����
								fseek(fp, 0, SEEK_SET); //������ �������� ó������ �̵�
								while(fscanf(fp, "%s %s ", id, pwd)>0) { //���Ͽ��� id�� pwd�� �޾ƿ�
										if(!strcmp(id, _id)) {//id�� �� ��  ��ġ�ϸ�
												if(!strcmp(pwd, _pwd)) { //�н����带 ���� ��ġ�ϸ�
														send(s_c_sock, "exist\0", sizeof(char)*12, 0); //�����Ѵٴ� �޽��� ����
														exist = 1; //����
														break;
												}
												else { //�н����尡 ��ġ���� ������
														exist = 1; //����� ������
														not_pwd =1; //�н������ ��ġ x
														send(s_c_sock, "invalid pwd\0", sizeof(char)*12, 0); //�н����� ���� �޽��� ����
														break;
												}
										}
										else { //���̵� ��ġ����������
												exist = 0; //���� x
										}
										fgets(_else, 100, fp); //������ ������ �޾ƿ�(���̵�� �н����常 �е���)
										memset(id, 0, 20);
										memset(pwd, 0, 20);
										
								}
								if(exist == 1) { //�����Ѵٸ�
										if(not_pwd == 1) { //�н����尡 ��ġ���� �ʴ´ٸ�
												not_pwd = 0; //pwd�� 0���� �ʱ�ȭ
										}
										else break; //�н����尡 ��ġ�ϸ� ���Ϲ� ����
								}
								else { //�������� �ʴ´ٸ�
										send(s_c_sock, "invalid id\0", sizeof(char)*12, 0); //�������� �ʴ� id�޽��� ����
								}
										
						}
						break;
				}
				else {
						char* message = "Wrong Input\0";
						send(s_c_sock, message, strlen(message), 0);
				}
		}
		library_server(id);
}
