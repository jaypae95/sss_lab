/* ----------------------------------------------------------------------------------------------------
*  파일: info.c
*  기능	: 유저/도서 정보 관리 서버
*  개발자: 201520934 배재훈
*  날짜	: 1차 개발 : 2018년 6월 8일
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
		send(s_c_sock, message, 30, 0); //유저 정보 응답 전송
		usleep(10);
		fscanf(fp,"%s %s %s\n", num, name, major); //로그인을 한 후 였기 때문에 아이디 패스워드를 읽어 온 후의
												//오프셋에서 인자 세개를 더 받아온다.
		fseek(fp, -(strlen(num)+strlen(name)+strlen(major)+3), SEEK_CUR); //받아온 만큼 돌려 놓음으로써 다시 유저 정보
																		// 함수를 호출해도 그대로 읽어올 수 있도록 한다.

		send(s_c_sock, num, 20, 0); //학번
		send(s_c_sock, name, 20, 0); //이름
		send(s_c_sock, major, 20, 0); //학과를 클라이언트로 전송
		
		free(num);
		free(name);
		free(major);
		
		return 0;
}

int get_book_info_all() {
		char *book_info = (char*)malloc(256);
		
		fseek(fp2, 0, SEEK_SET); //오프셋을 처음으로 설정
		while(fgets(book_info, 256, fp2) >0){ //한줄 씩 읽어오면서
				send(s_c_sock, book_info, 256, 0); //책 정보를 클라이언트로 전송
				usleep(1000);
				memset(book_info, 0 , 256);
		}
		send(s_c_sock, "done\0", 256, 0); //done 메시지를 전송
		
		return 0;
}

int get_book_info_select() {
		char *book_info = (char*)malloc(256);
		char *book_name = (char*)malloc(100);
		int exist =0;
		
		fseek(fp2, 0, SEEK_SET); //파일 위치를 처음으로 설정
		recv(s_c_sock, book_name, 100, 0); //도서 이름을 받아옴
		while(fgets(book_info, 256, fp2) >0) { //한 줄씩 읽어오면서
				book_info[strlen(book_info)-10] = '\0'; //, 0001, V\n 에서 맨앞에 ,자리에 null
				if(!strcmp(book_info, book_name)) { //도서 이름 비교해서 일치하면
				exist = 1; //존재
				send(s_c_sock, book_name, 100, 0); //도서 이름 전송
				send(s_c_sock, book_info+(strlen(book_info)+8), 10, 0); //도서 대여 가능 여부 정보 전송
				break;
				}
		}
		if(exist == 0) { //존재하지 않으면
				send(s_c_sock, "Not exist\0", 100, 0); //존재하지 않는다는 메시지 전송
		}
		
		free(book_name);
		free(book_info);
		return 0;
}

