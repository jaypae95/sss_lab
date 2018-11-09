/* ----------------------------------------------------------------------------------------------------
*  파일: library_server.c
*  기능	: 로그인 후 도서관 기능을 하는 서버
*  개발자: 201520934 배재훈
*  날짜	: 1차 개발 : 2018년 6월 8일
*----------------------------------------------------------------------------------------------------*/
#include "fake_apue.h"

int library_server(char * _id) {
		char* lib_menu = (char*)malloc(10);
		char* list_menu = (char*)malloc(10);
		int fd;

		fp2 = fopen("./book_list.txt", "r+"); //파일오픈
		fp3 = fopen("./rent.txt", "a+"); //파일오픈
		while(1) {
				recv(s_c_sock, lib_menu, 10, 0); //클라이언트로부터 메뉴정보를 받음
				if(lib_menu[0] == '1') { //1일 경우
						get_user_info(_id); //유저 정보 함수 호출
						send(s_c_sock, " ", 1, 0); //1번 기능이 끝났다는 메시지 전송
				}
				else if(lib_menu[0] == '2') { //2일 경우
						char *message = "Book List Requested\0"; 
						send(s_c_sock, message, 30, 0);// 도서 정보 응답 전송
							
						recv(s_c_sock, list_menu, 10, 0); //클라이언트로 부터 도서 정보 메뉴선택을 받음
						if(list_menu[0] == '1') { //1일경우
								get_book_info_all(); //전체 도서 정보 함수 호출
						}
						else if(list_menu[0] == '2') { //2일 경우
								get_book_info_select(); //선택 도서 정보 함수 호출
						}
					
						send(s_c_sock, " ", 1, 0); //2번 기능이 끝났다는 메시지를 전송
				}
				else if(lib_menu[0] == '3') { //3일 경우
						char *message = "Rental Requested\0";
						char *book_name = (char *)malloc(100);

						send(s_c_sock, message, 30, 0); //도서 대여 응답 전송
						
						usleep(1);
						
						get_book_info_all(); //전체 도서 정보 함수 호출
						
						recv(s_c_sock, book_name, 100, 0); //도서 이름을 받음
						
						book_rental(book_name, _id); //선택 도서 정보 함수 호출

						send(s_c_sock, " ", 1, 0); //3번 기능이 끝났다는 메시지를 전송
				}
				else if(lib_menu[0] == '4') { //4일 경우
						char *message = "Return Requested\0";
						send(s_c_sock, message, 30, 0); //도서 반납 응답 전송
						
						usleep(1000);
						book_return(_id); //도서 반납 함수 호출
						send(s_c_sock, " ", 1, 0); //4번 기능이 끝났다는 메시지를 전송
				}
				else if(lib_menu[0] == '5') { //5일 경우
						char * message = "EXIT Requested\0";
						send(s_c_sock, message, 30, 0); //로그아웃(종료) 응답 전송
						
						close(s_c_sock); //소켓 닫음
						return 0;
				}
				else {
						char *message = "Wrong Input\0";
						send(s_c_sock, message, 30, 0);
						
				}
		}
}
