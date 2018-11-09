#include "fake_apue.h"

int library_server(char * _id) {
		char* lib_menu = (char*)malloc(10);
		char* list_menu = (char*)malloc(10);
		int fd;

		fp2 = fopen("./book_list.txt", "r+");
		fp3 = fopen("./rent.txt", "a+");
		while(1) {
				read(fd1[0], lib_menu, 10);
				if(lib_menu[0] == '1') {
						get_user_info(_id);
						write(fd2[1], " ", 1);
				}
				else if(lib_menu[0] == '2') {
						char *message = "Book List Requested\0";
						write(fd2[1], message, 30);
						
						read(fd1[0], list_menu, 10);
						if(list_menu[0] == '1') {
								get_book_info_all();
						}
						else if(list_menu[0] == '2') {
								get_book_info_select();
						}
						printf("\n");
						write(fd2[1], " ", 1);
				}
				else if(lib_menu[0] == '3') {
						char *message = "Rental Requested\0";
						char *book_name = (char *)malloc(100);

						write(fd2[1], message, 30);
						usleep(1);
						
						get_book_info_all();
						
						read(fd1[0], book_name, 100);
						
						book_rental(book_name, _id);

						write(fd2[1], " ", 1);
				}
				else if(lib_menu[0] == '4') {
						char *message = "Return Requested\0";
						write(fd2[1], message, 30);
						usleep(1000);
						book_return(_id);
						write(fd2[1], " ", 1);
				}
				else if(lib_menu[0] == '5') {
						char * message = "EXIT Requested\0";
						write(fd2[1], message, 30);
						return 0;
				}
				else {
						char *message = "Wrong Input\0";
						write(fd2[1], message, 30);
				}
		}
}
