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
				printf("===============Select Menu===============\n");
				printf("1.Sign Up\n");
				printf("2.Sign In\n");

				scanf("%c", &menu);
				getchar();
				memset(message, 0, 30);
				send(c_sock, &menu, sizeof(char), 0);
				recv(c_sock, message, sizeof(char)*30, 0);
				if(!strcmp(message, "Sign Up Requested")) {
						printf("%s\n", message);
						sign_up();
				}
				else if(!strcmp(message, "Sign In Requested")) {
						printf("%s\n", message);
						sign_in();
						printf("================Sign In Successed!===============\n");
						while(1) {
								printf("===================Select Menu===================\n");
								printf("1. Get User Information\n");
								printf("2. Get Book List\n");
								printf("3. Book Rental\n");
								printf("4. Return Book\n");
								printf("5. Sign Out\n");
								fgets(lib_menu, 10, stdin);
								memset(lib_menu+1, 0, 9);
								send(c_sock, lib_menu, 10, 0);
								recv(c_sock, lib_message, sizeof(char)*30, 0);
								memset(lib_menu, 0, 10);
								if(!strcmp(lib_message, "User Info. Requested")) {
										printf("%s\n", lib_message);
										usleep(1000);
										memset(num, 0, 20);
										memset(name, 0, 20);
										memset(major, 0, 20);

										recv(c_sock, num, 20, 0);
										recv(c_sock, name, 20, 0);
										recv(c_sock, major, 20, 0);

										printf("Student # : %s\n", num);
										printf("Name      : %s\n", name);
										printf("Major     : %s\n\n", major);

										recv(c_sock, &suc, 1, 0);
								}	
								else if(!strcmp(lib_message, "Book List Requested")) {
										printf("%s\n", lib_message);
										while(1) {
											printf("==========Select Menu==========\n");
											printf("1. List All Books\n");
											printf("2. Search Books\n");
											fgets(list_menu, 10, stdin);
											memset(list_menu+1, 0, 9);
											if(!strcmp(list_menu, "1")) {
													send(c_sock, list_menu, 1, 0);
													while(1) {
															memset(book_info, 0, 256);
															recv(c_sock, book_info, 256, 0);
															if(!strcmp(book_info, "done")) {
																	break;
															}
															printf("%s", book_info);
													}
													printf("\n");
													usleep(1000);
													break;
											}
											else if(!strcmp(list_menu, "2")) {
													char *book = (char*)malloc(100);
													char *book_info = (char*)malloc(100);
													memset(book, 0, 100);
													memset(book_info, 0, 100);
													send(c_sock, list_menu, 10, 0);
													printf("Book Name : ");
													fgets(book, 100, stdin);
													book[strlen(book)-1] = '\0';
													send(c_sock, book, 100, 0);
													recv(c_sock, book_info, 100, 0);
													printf("%s", book_info);
													if(strcmp(book_info, "Not exist")) {
															memset(book_info, 0, 100);
															recv(c_sock, book_info, 10, 0);
															printf(", %s", book_info);
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
										recv(c_sock, &suc, 1, 0);
								}
								else if(!strcmp(lib_message, "Rental Requested")) {
										char *book = (char*)malloc(100);
										char *book_suc = (char*)malloc(30);

										printf("%s\n", lib_message);
										while(1) {
												memset(book_info, 0, 256);
												recv(c_sock, book_info, 256, 0);
												if(!strcmp(book_info, "done")) {
														break;
												}
												printf("%s", book_info);
										}
										printf("\nBook Name : ");
										fgets(book, 100, stdin);
										book[strlen(book)-1] = '\0'; 
										send(c_sock, book, 100, 0);
										recv(c_sock, book_suc, 30, 0);
										printf("%s\n", book_suc);
										free(book);
										free(book_suc);
										recv(c_sock, &suc, 1, 0);
								}
								else if(!strcmp(lib_message, "Return Requested")) {
										char * return_message = (char*)malloc(128);
										printf("%s\n", lib_message);
										recv(c_sock, return_message, 128, 0);
										printf("%s\n", return_message);
										while(1) {
												memset(return_message, 0, 128);
												recv(c_sock, return_message, 128, 0);
												if(!strcmp(return_message, "done")) {
														break;
												}
												printf("%s\n", return_message, 128, 0);
										}
										printf("\n");
										recv(c_sock, &suc, 1, 0);
								}
								else if(!strcmp(lib_message, "EXIT Requested")) {
										printf("%s\n", lib_message);
										close(c_sock);
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
