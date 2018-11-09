/* ----------------------------------------------------------------------------------------------------
*  파일: server.c
*  기능	: 도서관 희원가입/로그인 서버
*  개발자: 201520934 배재훈
*  날짜	: 1차 개발 : 2018년 6월 8일
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
		fp = fopen("./user_data.txt", "a+"); //파일 오픈
		int exist = 0, not_pwd=0;
		while(1) {
				exist = 0;
				recv(s_c_sock, &menu, sizeof(char), 0);  //클라이언트로 부터 메뉴 정보를 받음
				if(menu == '1') { //1일 경우
						char *message = "Sign Up Requested\0";
						send(s_c_sock, message, strlen(message), 0); //희원 가입 응답 전송
						
						while(1) {
								memset(id, 0, 20);
								recv(s_c_sock, id, sizeof(char)*20, 0); //클라이언트에게 아이디를 받음
								fseek(fp, 0, SEEK_SET); //파일의 오프셋을 처음으로 설정
								while(fscanf(fp, "%s", _id) > 0) { //파일의 맨 처음 인자를 읽음
										//_id[strlen(id-1] = '\0';
										if(!strcmp(id, _id)) { //id를 비교해서 일치하면
												send(s_c_sock, "exist\0", sizeof(char)*10, 0);
												exist = 1; //존재
												break;
										}
										exist = 0; //not exist
										fgets(_else, 100, fp); //나머지 줄을 읽어 들임(다음 줄의 첫번째 인자를 읽어올 수 있도록)
										memset(_id, 0, sizeof(char)*20);
								}
								if(exist == 0) { //not exist untill the end >> successed
										send(s_c_sock, "not exist\0", sizeof(char)*10, 0); //존재하지 않는다는 메시지를 전송
										recv(s_c_sock, pwd, sizeof(char)*20, 0); //비밀번호
										recv(s_c_sock, num, sizeof(char)*20, 0); //학번
										recv(s_c_sock, name, sizeof(char)*20, 0); //이름
										recv(s_c_sock, major, sizeof(char)*20, 0); //학과를 클라이언트로 부터 받음
										fseek(fp, 0, SEEK_END);
										fprintf(fp, "%s %s %s %s %s\n", id, pwd, num, name, major); //정보들을 파일에 출력
										fflush(fp);
										break;
								}
								else continue;
						}
				}
				else if(menu == '2') { //2일 경우
						memset(id, 0, 20);
						memset(pwd, 0, 20);
						exist = 0;
						char *message = "Sign In Requested\0";
						send(s_c_sock, message, strlen(message), 0); //로그인 응답 메시지 전송
						
						while(1) {
								recv(s_c_sock, _id, sizeof(char)*20, 0); //클라이언트로부터 아이디와
								recv(s_c_sock, _pwd, sizeof(char)*20, 0); //비밀번호를 받음
								fseek(fp, 0, SEEK_SET); //파일의 오프셋을 처음으로 이동
								while(fscanf(fp, "%s %s ", id, pwd)>0) { //파일에서 id와 pwd를 받아옴
										if(!strcmp(id, _id)) {//id를 비교 후  일치하면
												if(!strcmp(pwd, _pwd)) { //패스워드를 비교후 일치하면
														send(s_c_sock, "exist\0", sizeof(char)*12, 0); //존재한다는 메시지 전송
														exist = 1; //존재
														break;
												}
												else { //패스워드가 일치하지 않으면
														exist = 1; //존재는 하지만
														not_pwd =1; //패스워드는 일치 x
														send(s_c_sock, "invalid pwd\0", sizeof(char)*12, 0); //패스워드 오류 메시지 전송
														break;
												}
										}
										else { //아이디가 일치하지않으면
												exist = 0; //존재 x
										}
										fgets(_else, 100, fp); //나머지 정보를 받아옴(아이디와 패스워드만 읽도록)
										memset(id, 0, 20);
										memset(pwd, 0, 20);
										
								}
								if(exist == 1) { //존재한다면
										if(not_pwd == 1) { //패스워드가 일치하지 않는다면
												not_pwd = 0; //pwd를 0으로 초기화
										}
										else break; //패스워드가 일치하면 와일문 종료
								}
								else { //존재하지 않는다면
										send(s_c_sock, "invalid id\0", sizeof(char)*12, 0); //존재하지 않는 id메시지 전송
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
