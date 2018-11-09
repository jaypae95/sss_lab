/* ----------------------------------------------------------------------------------------------------
*  파일: sign.c
*  기능	: 희원가입 로그인
*  개발자: 201520934 배재훈
*  날짜	: 1차 개발 : 2018년 6월 8일
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
			memset(new_id, 0, sizeof(char)*20); //메모리 초기화
			memset(new_pwd, 0, sizeof(char)*20);
			memset(new_num, 0, sizeof(char)*20);
			memset(new_name, 0, sizeof(char)*20);
			memset(new_major, 0, sizeof(char)*20);

			clear();
			move(INIT_Y, INIT_X); //form (0,0);
			printw(  "#############################################"); //희원가입 창을 띄움
			printw("\n#####              Sign UP              #####");
			printw("\n#############################################");
			printw("\nUser ID  : "); //id
			printw("\nPassword : "); //패스워드
			printw("\nStudent# : "); //학번
			printw("\nName     : "); //이름
			printw("\nMajor    : "); //학과
			refresh();

			get_string_count = 0;
			get_string(MODE_ID, new_id); //id입력
			get_string(MODE_PASSWORD, new_pwd); //패스워드 입력
			get_string(MODE_ID, new_num); //학번 입력
			get_string(MODE_ID, new_name); //이름 입력
			get_string(MODE_ID, new_major); //학과 입력

			send(c_sock, new_id, strlen(new_id), 0); //서버에 id를 보냄
			recv(c_sock, exist, sizeof(char)*11, 0); //id가 존재하는지 하지않는지 정보를 받음
			if(!strcmp(exist, "exist")) { //존재한다면
					clear();
					move(0, 0);
					printw("already exist. can't create account.\n"); //이미 존재한다는 메시지를 출력
					getch();
					refresh();
			}
			else { //존재하지 않는다면
					clear();
					move(0, 0);
					printw("SIGN UP SUCCESSED!\n"); //희원가입에 성공했다는 메시지를 출력
					getch();
					refresh();
					endwin();
					send(c_sock, new_pwd, sizeof(char)*20, 0); //id를 보냈으니 패스워드
					send(c_sock, new_num, sizeof(char)*20, 0); //학번
					send(c_sock, new_name, sizeof(char)*20, 0); //이름
					send(c_sock, new_major, sizeof(char)*20, 0); //학과를 보냄
					break;
			}
		}

}

void sign_in() {

		char *user_id = (char*)malloc(sizeof(char)*20); //id
		char *user_pwd = (char*)malloc(sizeof(char)*20); //password
		char *exist = (char*)malloc(sizeof(char)*12);

		initscr(); //initiallize
		setvbuf(stdout, 0, _IONBF, 0); //버퍼링을 삭제함
		setvbuf(stdin, 0, _IONBF, 0); //버퍼링을 삭제함
		while(1) { //if tried 3 times, break
			memset(user_id, 0, sizeof(char)*20);
			memset(user_pwd, 0, sizeof(char)*20);

			get_string_count = 0;
			clear();
			move(INIT_Y, INIT_X); //from (0, 0);
			printw(  "#############################################"); //로그인 창을 띄움
			printw("\n#####              Sign IN              #####");
			printw("\n#############################################");
			printw("\nUser ID  : "); //id
			printw("\nPassword : "); //패스워드
			refresh();

			get_string(MODE_ID, user_id); //get id
			get_string(MODE_PASSWORD, user_pwd); //get password
			send(c_sock, user_id, sizeof(char)*20, 0); //서버에 id를보냄
			send(c_sock, user_pwd, sizeof(char)*20, 0); //서버에 패스워드를 보냄
			recv(c_sock, exist, sizeof(char)*12, 0); //id가 존재하는지, 존재한다면 패스워드가
													// 일치하는지에대한정보를 받음
			if(!strcmp(exist, "exist")) { //존재하고 패스워드가 일치한다면
					clear(); 
					move(0,0);
					printw("Sign IN sucessed !\n"); //로그인 성공
					getch();
					refresh();
					endwin();
					break;
			}
			else{
					memset(user_id, 0, 20);
					memset(user_pwd, 0, 20);
					if(!strcmp(exist, "invalid pwd")) { //비밀번호가 틀릴 시
							clear();
							move(0, 0);
							printw("Incorrect Password!\n"); //오류 메시지 출력
							getch();
							refresh();
					}
					else if(!strcmp(exist, "invalid id")) { //존재하지 않는 아이디 일 때
							clear();
							move(0, 0);
							printw("Invalid ID!\n"); //오류 메시지 출력
							getch();
							refresh();
					}
			}

		}
}
