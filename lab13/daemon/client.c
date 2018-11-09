/* ----------------------------------------------------------------------------------------------------
*  파일: _start_server.c
*  기능	: 클라이언트(모든 메뉴선택과 출력을 해줌)
*  개발자: 201520934 배재훈
*  날짜	: 1차 개발 : 2018년 6월 8일
*----------------------------------------------------------------------------------------------------*/
#include "fake_apue.h"

int _client() {
		char menu = '\0';
		char *lib_menu = (char*)malloc(10);
		char *list_menu = (char*)malloc(10);
		char *message = (char*)malloc(sizeof(char)*30);
		char *lib_message = (char*)malloc(sizeof(char)*30);
		
		char *num = (char*)malloc(20);
		char *name = (char*)malloc(20);
		char *major = (char*)malloc(20); 
		char *book_info = (char*)malloc(256);

		char suc ; '\0';
		while(1) {
				printf("===============Select Menu===============\n"); //메뉴 선택 창
				printf("1.Sign Up\n"); //희원 가입
				printf("2.Sign In\n"); //로그인

				scanf("%c", &menu); //1번 혹은 2번을 받음
				getchar();
				memset(message, 0, 30);
				send(c_sock, &menu, sizeof(char), 0); //메뉴 선택정보를 서버에 보냄
				recv(c_sock, message, sizeof(char)*30, 0); //서버에서 응답을 받음
				if(!strcmp(message, "Sign Up Requested")) { //희원가입
						printf("%s\n", message); 
						sign_up(); //희원가입 함수 호출
				}
				else if(!strcmp(message, "Sign In Requested")) { //로그인
						printf("%s\n", message);
						sign_in(); //로그인 함수 호출
						printf("================Sign In Successed!===============\n"); //함수에서 빠져나왔다는 뜻은 로그인 성공
						while(1) {
								printf("===================Select Menu===================\n"); //로그인 이후의 메뉴 출력
								printf("1. Get User Information\n"); //유저 정보 받기
								printf("2. Get Book List\n"); //도서 정보 받기
								printf("3. Book Rental\n"); //도서 대여
								printf("4. Return Book\n"); //도서 반납
								printf("5. Sign Out\n"); // 로그아웃(프로그램 종료)
								fgets(lib_menu, 10, stdin); //메뉴입력
								memset(lib_menu+1, 0, 9);
								send(c_sock, lib_menu, 10, 0); //메뉴입력정보를 서버에 보냄
								recv(c_sock, lib_message, sizeof(char)*30, 0); //서버로 부터 응답을 받음
								memset(lib_menu, 0, 10);
								if(!strcmp(lib_message, "User Info. Requested")) { //유저 정보 받기
										printf("%s\n", lib_message);
										usleep(1000);
										memset(num, 0, 20); //메모리 초기화
										memset(name, 0, 20);
										memset(major, 0, 20);

										recv(c_sock, num, 20, 0); //서버로부터 학번
										recv(c_sock, name, 20, 0); //이름
										recv(c_sock, major, 20, 0); //학과정보를 받아옴

										printf("Student # : %s\n", num); //받아온 정보를 출력
										printf("Name      : %s\n", name);
										printf("Major     : %s\n\n", major);

										recv(c_sock, &suc, 1, 0); //서버가 1번 기능을 끝냈다는 메시지를 받음
								}	
								else if(!strcmp(lib_message, "Book List Requested")) { //도서 정보
										printf("%s\n", lib_message);
										while(1) {
											printf("==========Select Menu==========\n"); //도서 정보 메뉴
											printf("1. List All Books\n"); //모든 도서 정보
											printf("2. Search Books\n"); //선택 도서 정보
											fgets(list_menu, 10, stdin); //메뉴를 입력받음
											memset(list_menu+1, 0, 9);
											if(!strcmp(list_menu, "1")) { //모든 도서 정보
													send(c_sock, list_menu, 1, 0); //서버에게 요청을 함
													while(1) {
															memset(book_info, 0, 256);
															recv(c_sock, book_info, 256, 0); //서버로 부터 정보를 
															if(!strcmp(book_info, "done")) { //done메시지가 올 때 까지 반복해서 받아옴
																	break;
															}
															printf("%s", book_info); //받아온 도서 정보 출력
													}
													printf("\n");
													usleep(1000);
													break;
											}
											else if(!strcmp(list_menu, "2")) { //선택 도서
													char *book = (char*)malloc(100);
													char *book_info = (char*)malloc(100);
													memset(book, 0, 100);
													memset(book_info, 0, 100);
													send(c_sock, list_menu, 10, 0); //서버에게 메뉴 요청
													printf("Book Name : ");
													fgets(book, 100, stdin); //책 이름을 입력
													book[strlen(book)-1] = '\0';
													send(c_sock, book, 100, 0); //서버에게 책이름 전송
													recv(c_sock, book_info, 100, 0); //서버에게 책 정보를 받음
													printf("%s", book_info); //책 정보 출력
													if(strcmp(book_info, "Not exist")) { //만약 존재 한다면
															memset(book_info, 0, 100);
															recv(c_sock, book_info, 10, 0); //대여 여부 정보를 받아옴
															printf(", %s", book_info); //대여 여버 정보 출력
													}
													printf("\n"); 
													usleep(1000);
													break;
											}
											else {
													printf("Wrong Input\n");
											}
											memset(list_menu, 0, 10);
										}
										recv(c_sock, &suc, 1, 0); //서버가 2번 기능을 끝냈다는 메시지를 받음
								}
								else if(!strcmp(lib_message, "Rental Requested")) { //도서 대여
										char *book = (char*)malloc(100);
										char *book_suc = (char*)malloc(30);

										printf("%s\n", lib_message);
										while(1) {
												memset(book_info, 0, 256);
												recv(c_sock, book_info, 256, 0); //책 정보들을
												if(!strcmp(book_info, "done")) { //done메시지를 받기 전까지 받아옴
														break;
												}
												printf("%s", book_info); //책 정보 출력
										}
										printf("\nBook Name : ");
										fgets(book, 100, stdin); //대여할 책 이름을 받아옴
										book[strlen(book)-1] = '\0'; 
										send(c_sock, book, 100, 0); //책 이름을 서버에 전송
										recv(c_sock, book_suc, 30, 0); //성공 여부를 받아옴
										printf("%s\n", book_suc); //성공 여부 출력
										free(book);
										free(book_suc);
										recv(c_sock, &suc, 1, 0);  //서버가 3번 기능을 끝냈다는 메시지를 받음
								}
								else if(!strcmp(lib_message, "Return Requested")) { //도서 반납
										char * return_message = (char*)malloc(128);
										printf("%s\n", lib_message);
										recv(c_sock, return_message, 128, 0); //==========list==========
										printf("%s\n", return_message);
										while(1) {
												memset(return_message, 0, 128);
												recv(c_sock, return_message, 128, 0); //대여 한 책 정보를
												if(!strcmp(return_message, "done")) { //done메시지를 받기 전 까지
														break;
												}
												printf("%s\n", return_message, 128, 0);
										}
										printf("\n");
										recv(c_sock, &suc, 1, 0);  //서버가 4번 기능을 끝냈다는 메시지를 받음
								}
								else if(!strcmp(lib_message, "EXIT Requested")) { //로그아웃(종료)
										printf("%s\n", lib_message); 
										close(c_sock);//소켓 종료
										return 0;
								}
								else{
										printf("%s\n", lib_message);
								}
						}
						lib_menu='\0';

				}
				else {
						printf("%s\n", message);
						menu = '\0';
				}
		}

		return 0;
}
