#include "fake_apue.h"



int get_user_info(char *_id) {
		char *num = (char*)malloc(20);
		char *name = (char*)malloc(20);
		char *major = (char*)malloc(20);
		
		memset(num, 0, 20);
		memset(name, 0, 20);
		memset(major, 0, 20);
		char *message = "User Info. Requested\0";
		s_writefd = open(FIFO1, O_WRONLY, 0);
		write(s_writefd, message, 30);
		close(s_writefd);
		usleep(10);
		fscanf(fp,"%s %s %s\n", num, name, major);
		fseek(fp, -(strlen(num)+strlen(name)+strlen(major)+3), SEEK_CUR);
		printf("Student Number : %s\n", num);
		printf("Student Name   : %s\n", name);
		printf("Major          : %s\n\n", major);
		
		free(num);
		free(name);
		free(major);
		
		return 0;
}

int get_book_info_all() {
		char *book_info = (char*)malloc(256);
		
		fseek(fp2, 0, SEEK_SET);
		while(fgets(book_info, 256, fp2) >0){
				printf("%s", book_info);
				memset(book_info, 0 , 256);
		}
		
		return 0;
}

int get_book_info_select() {
		char *book_info = (char*)malloc(256);
		char *book_name = (char*)malloc(100);
		int exist =0;
		
		fseek(fp2, 0, SEEK_SET);
		s_readfd = open(FIFO2, O_RDONLY, 0);
		read(s_readfd, book_name, 100);
		close(s_readfd);
		while(fgets(book_info, 256, fp2) >0) {
				book_info[strlen(book_info)-10] = '\0';
				if(!strcmp(book_info, book_name)) {
				exist = 1;
				printf("%s, %s", book_name, book_info+(strlen(book_info)+8));
				break;
				}
		}
		if(exist == 0) {
				printf("Not exist\n");
		}
		
		free(book_name);
		free(book_info);
		return 0;
}

