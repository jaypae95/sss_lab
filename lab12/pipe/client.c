#include "fake_apue.h"

int _client() {
		char menu = '\0';
		char *lib_menu = (char*)malloc(10);
		char *list_menu = (char*)malloc(10);
		char *message = (char*)malloc(sizeof(char)*30);
		char *lib_message = (char*)malloc(sizeof(char)*30);
		char suc ; '\0';
		while(1) {
				printf("===============Select Menu===============\n");
				printf("1.Sign Up\n");
				printf("2.Sign In\n");

				scanf("%c", &menu);
				getchar();
				memset(message, 0, 30);
				write(fd1[1], &menu, sizeof(char));
				read(fd2[0], message, sizeof(char)*30);
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
								write(fd1[1], lib_menu, 10);
								read(fd2[0], lib_message, sizeof(char)*30);
								memset(lib_menu, 0, 10);
								if(!strcmp(lib_message, "User Info. Requested")) {
										printf("%s\n", lib_message);
										usleep(1000);
										read(fd2[0], &suc, 1);
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
													write(fd1[1], list_menu, 1);
													usleep(1000);
													break;
											}
											else if(!strcmp(list_menu, "2")) {
													char *book = (char*)malloc(100);
													memset(book, 0, 100);
													write(fd1[1], list_menu, 10);
													printf("Book Name : ");
													fgets(book, 100, stdin);
													book[strlen(book)-1] = '\0';
													write(fd1[1], book, 100);
													usleep(1000);
													break;
											}
											else {
													printf("Wrong Input\n");
											}
											memset(list_menu, 0, 10);
										}
										read(fd2[0], &suc, 1);
								}
								else if(!strcmp(lib_message, "Rental Requested")) {
										char*book = (char*)malloc(100);
										printf("%s\n", lib_message);
										usleep(1000);
										printf("Book Name : ");
										fgets(book, 100, stdin);
										book[strlen(book)-1] = '\0';
										write(fd1[1], book, 100);
										usleep(1000);
										free(book);
										read(fd2[0], &suc, 1);
								}
								else if(!strcmp(lib_message, "Return Requested")) {
										printf("%s\n", lib_message);
										usleep(1000);
										read(fd2[0], &suc, 1);
								}
								else if(!strcmp(lib_message, "EXIT Requested")) {
										printf("%s\n", lib_message);
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
