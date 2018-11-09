#include "fake_apue.h"

int library_server(char * _id) {
		char* lib_menu = (char*)malloc(10);
		char* list_menu = (char*)malloc(10);
		int fd;

		fp2 = fopen("./book_list.txt", "r+");
		fp3 = fopen("./rent.txt", "a+");
		while(1) {
				s_readfd = open(FIFO2, O_RDONLY, 0);
				read(s_readfd, lib_menu, 10);
				close(s_readfd);
				if(lib_menu[0] == '1') {
						get_user_info(_id);
						s_writefd = open(FIFO1, O_WRONLY, 0);
						write(s_writefd, " ", 1);
						close(s_writefd);
				}
				else if(lib_menu[0] == '2') {
						char *message = "Book List Requested\0";
						s_writefd = open(FIFO1, O_WRONLY, 0);
						write(s_writefd, message, 30);
						close(s_writefd);
						s_readfd = open(FIFO2, O_RDONLY, 0);
						read(s_readfd, list_menu, 10);
						close(s_readfd);
						if(list_menu[0] == '1') {
								get_book_info_all();
						}
						else if(list_menu[0] == '2') {
								get_book_info_select();
						}
						printf("\n");
						s_writefd = open(FIFO1, O_WRONLY, 0);
						write(s_writefd, " ", 1);
						close(s_writefd);
				}
				else if(lib_menu[0] == '3') {
						char *message = "Rental Requested\0";
						char *book_name = (char *)malloc(100);
						s_writefd = open(FIFO1, O_WRONLY, 0);
						write(s_writefd, message, 30);
						close(s_writefd);
						usleep(1);
						
						get_book_info_all();
						s_readfd = open(FIFO2, O_RDONLY, 0);
						read(s_readfd, book_name, 100);
						close(s_readfd);
						
						book_rental(book_name, _id);
						
						s_writefd = open(FIFO1, O_WRONLY, 0);
						write(s_writefd, " ", 1);
						close(s_writefd);
				}
				else if(lib_menu[0] == '4') {
						char *message = "Return Requested\0";
						s_writefd = open(FIFO1, O_WRONLY, 0);
						write(s_writefd, message, 30);
						close(s_writefd);
						usleep(1000);
						book_return(_id);
						s_writefd = open(FIFO1, O_WRONLY, 0);
						write(s_writefd, " ", 1);
						close(s_writefd);
				}
				else if(lib_menu[0] == '5') {
						char * message = "EXIT Requested\0";
						s_writefd = open(FIFO1, O_WRONLY, 0);
						write(s_writefd, message, 30);
						close(s_writefd);
						return 0;
				}
				else {
						char *message = "Wrong Input\0";
						s_writefd = open(FIFO1, O_WRONLY, 0);
						write(s_writefd, message, 30);
						close(s_writefd);
				}
		}
}
