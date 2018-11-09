#include "fake_apue.h"

int library_server(char * _id) {
		char* lib_menu = (char*)malloc(10);
		char* list_menu = (char*)malloc(10);
		int fd;

		fp2 = fopen("./book_list.txt", "r+");
		fp3 = fopen("./rent.txt", "a+");
		while(1) {
				recv(s_c_sock, lib_menu, 10, 0);
				if(lib_menu[0] == '1') {
						get_user_info(_id);
						send(s_c_sock, " ", 1, 0);
				}
				else if(lib_menu[0] == '2') {
						char *message = "Book List Requested\0";
						send(s_c_sock, message, 30, 0);
						printf("%s\n", message);	
						recv(s_c_sock, list_menu, 10, 0);
						if(list_menu[0] == '1') {
								get_book_info_all();
						}
						else if(list_menu[0] == '2') {
								get_book_info_select();
						}
					
						send(s_c_sock, " ", 1, 0);
				}
				else if(lib_menu[0] == '3') {
						char *message = "Rental Requested\0";
						char *book_name = (char *)malloc(100);

						send(s_c_sock, message, 30, 0);
						printf("%s\n", message);
						usleep(1);
						
						get_book_info_all();
						
						recv(s_c_sock, book_name, 100, 0);
						
						book_rental(book_name, _id);

						send(s_c_sock, " ", 1, 0);
				}
				else if(lib_menu[0] == '4') {
						char *message = "Return Requested\0";
						send(s_c_sock, message, 30, 0);
						printf("%s\n", message);
						usleep(1000);
						book_return(_id);
						send(s_c_sock, " ", 1, 0);
				}
				else if(lib_menu[0] == '5') {
						char * message = "EXIT Requested\0";
						send(s_c_sock, message, 30, 0);
						printf("%s\n", message);
						close(s_c_sock);
						return 0;
				}
				else {
						char *message = "Wrong Input\0";
						send(s_c_sock, message, 30, 0);
						printf("%s\n", message);
				}
		}
}
