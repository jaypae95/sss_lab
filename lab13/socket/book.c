#include "fake_apue.h"

int book_rental(char *book_name, char* id) {


		char *book_info = (char *)malloc(256);
		int exist = 0;

		fseek(fp2, 0, SEEK_SET);
		memset(book_info, 0, 256);
		while(fgets(book_info, 256, fp2) > 0) {
				book_info[strlen(book_info)-10] = '\0';
				if(!strcmp(book_info, book_name)) {
						exist =1;
						break;
				}
		}
		if(exist == 0) {
				send(s_c_sock, "not exist\0", 30, 0);
		}
		else {
				char valid = '\0';
				fseek(fp2, -2, SEEK_CUR);
				fscanf(fp2, "%c ", &valid);
				if(valid == 'I') {
						send(s_c_sock, "cannot rent\0", 30, 0);
				}
				else if(valid == 'V') {
						fseek(fp2, -2, SEEK_CUR);
						fprintf(fp2, "I");
						fflush(fp2);
						fprintf(fp3, "%s,%s\n", book_name, id);
						fflush(fp3);
						send(s_c_sock, "success!\0", 30, 0);
				}
		}
		
		free(book_info);
		return 0;

}

int book_return(char *id) {
		char rent_info[100] = {0, };
		char to_return[100] = {0, };
		char * token = NULL;
		char **buf = (char**)malloc(sizeof(char*)*2);
		int exist = 0;
		char temp_info[100];
		FILE *temp = fopen("./temp.txt", "w+");
		fseek(fp3, 0, SEEK_SET);
		send(s_c_sock, "===============List===============\0", 128, 0);
		while(fgets(rent_info, 100, fp3) > 0) {
				rent_info[strlen(rent_info)-1] = '\0';
				memset(temp_info, 0, 100);

				strcpy(temp_info, rent_info);

				token = strtok(temp_info, ",");
				int i=0;
				while(token != NULL) {
						buf[i] = (char*)malloc(30);
						memset(buf[i], 0, 30);
						buf[i] = token;
						buf[i][strlen(buf[i])] = '\0';
						i++;
						token=strtok(NULL, ",");
				}
				if(!strcmp(buf[1], id)) {		
						exist = 1;
						send(s_c_sock, buf[0], 128, 0);
						fseek(fp2, 0, SEEK_SET);
						while(fgets(to_return, 100, fp2) >0) {
								token = strtok(to_return, ",");
								if(!strcmp(token, buf[0])) {
										fseek(fp2, -2, SEEK_CUR);
										fprintf(fp2, "V\n");
										fflush(fp2);
								}
								memset(to_return, 0, 100);
						}
				}
				else {
						fprintf(temp, "%s\n", rent_info);
				}
		}
		if(exist == 0) {
				send(s_c_sock, "You have not rent any book\0", 128, 0);
		}
		else {
				send(s_c_sock, "\n\nComplete Returning\0", 128, 0);
		}
		send(s_c_sock, "done\0", 128, 0);
		system("rm -f ./rent.txt");
		rename("./temp.txt", "./rent.txt");
		
		fclose(fp3);
		fp3 = fopen("./rent.txt", "a+");

		return 0;
}

