/* ----------------------------------------------------------------------------------------------------
*  ����: sign.c
*  ���	: ������� �α���
*  ������: 201520934 ������
*  ��¥	: 1�� ���� : 2018�� 6�� 8��
*----------------------------------------------------------------------------------------------------*/
#include "fake_apue.h"

void sign_up() {
		char *new_id = (char*)malloc(sizeof(char)*20); //id
		char *new_pwd = (char*)malloc(sizeof(char)*20); //password
		char *new_num = (char*)malloc(sizeof(char)*20);
		char *new_name = (char*)malloc(sizeof(char)*20);
		char *new_major = (char*)malloc(sizeof(char)*20);
		char *exist = (char*)malloc(sizeof(char)*11);
		int status;
		int i; //count
		char* infile = (char*)malloc(sizeof(char)*100); //string in file
		initscr();
		setvbuf(stdout, 0, _IONBF, 0);
		setvbuf(stdin, 0, _IONBF, 0);
		while(1) {
			memset(new_id, 0, sizeof(char)*20); //�޸� �ʱ�ȭ
			memset(new_pwd, 0, sizeof(char)*20);
			memset(new_num, 0, sizeof(char)*20);
			memset(new_name, 0, sizeof(char)*20);
			memset(new_major, 0, sizeof(char)*20);

			clear();
			move(INIT_Y, INIT_X); //form (0,0);
			printw(  "#############################################"); //������� â�� ���
			printw("\n#####              Sign UP              #####");
			printw("\n#############################################");
			printw("\nUser ID  : "); //id
			printw("\nPassword : "); //�н�����
			printw("\nStudent# : "); //�й�
			printw("\nName     : "); //�̸�
			printw("\nMajor    : "); //�а�
			refresh();

			get_string_count = 0;
			get_string(MODE_ID, new_id); //id�Է�
			get_string(MODE_PASSWORD, new_pwd); //�н����� �Է�
			get_string(MODE_ID, new_num); //�й� �Է�
			get_string(MODE_ID, new_name); //�̸� �Է�
			get_string(MODE_ID, new_major); //�а� �Է�

			send(c_sock, new_id, strlen(new_id), 0); //������ id�� ����
			recv(c_sock, exist, sizeof(char)*11, 0); //id�� �����ϴ��� �����ʴ��� ������ ����
			if(!strcmp(exist, "exist")) { //�����Ѵٸ�
					clear();
					move(0, 0);
					printw("already exist. can't create account.\n"); //�̹� �����Ѵٴ� �޽����� ���
					getch();
					refresh();
			}
			else { //�������� �ʴ´ٸ�
					clear();
					move(0, 0);
					printw("SIGN UP SUCCESSED!\n"); //������Կ� �����ߴٴ� �޽����� ���
					getch();
					refresh();
					endwin();
					send(c_sock, new_pwd, sizeof(char)*20, 0); //id�� �������� �н�����
					send(c_sock, new_num, sizeof(char)*20, 0); //�й�
					send(c_sock, new_name, sizeof(char)*20, 0); //�̸�
					send(c_sock, new_major, sizeof(char)*20, 0); //�а��� ����
					break;
			}
		}

}

void sign_in() {

		char *user_id = (char*)malloc(sizeof(char)*20); //id
		char *user_pwd = (char*)malloc(sizeof(char)*20); //password
		char *exist = (char*)malloc(sizeof(char)*12);

		initscr(); //initiallize
		setvbuf(stdout, 0, _IONBF, 0); //���۸��� ������
		setvbuf(stdin, 0, _IONBF, 0); //���۸��� ������
		while(1) { //if tried 3 times, break
			memset(user_id, 0, sizeof(char)*20);
			memset(user_pwd, 0, sizeof(char)*20);

			get_string_count = 0;
			clear();
			move(INIT_Y, INIT_X); //from (0, 0);
			printw(  "#############################################"); //�α��� â�� ���
			printw("\n#####              Sign IN              #####");
			printw("\n#############################################");
			printw("\nUser ID  : "); //id
			printw("\nPassword : "); //�н�����
			refresh();

			get_string(MODE_ID, user_id); //get id
			get_string(MODE_PASSWORD, user_pwd); //get password
			send(c_sock, user_id, sizeof(char)*20, 0); //������ id������
			send(c_sock, user_pwd, sizeof(char)*20, 0); //������ �н����带 ����
			recv(c_sock, exist, sizeof(char)*12, 0); //id�� �����ϴ���, �����Ѵٸ� �н����尡
													// ��ġ�ϴ��������������� ����
			if(!strcmp(exist, "exist")) { //�����ϰ� �н����尡 ��ġ�Ѵٸ�
					clear(); 
					move(0,0);
					printw("Sign IN sucessed !\n"); //�α��� ����
					getch();
					refresh();
					endwin();
					break;
			}
			else{
					memset(user_id, 0, 20);
					memset(user_pwd, 0, 20);
					if(!strcmp(exist, "invalid pwd")) { //��й�ȣ�� Ʋ�� ��
							clear();
							move(0, 0);
							printw("Incorrect Password!\n"); //���� �޽��� ���
							getch();
							refresh();
					}
					else if(!strcmp(exist, "invalid id")) { //�������� �ʴ� ���̵� �� ��
							clear();
							move(0, 0);
							printw("Invalid ID!\n"); //���� �޽��� ���
							getch();
							refresh();
					}
			}

		}
}
