#include "fake_apue.h"

int _server() {
		char menu;
		char *_id = (char*)malloc(sizeof(char)*20);
		char *_pwd = (char*)malloc(sizeof(char)*20);
		char *pwd = (char*)malloc(sizeof(char)*20);
		char *id = (char*)malloc(sizeof(char)*20);
		char *num = (char*)malloc(sizeof(char)*20);
		char *name = (char*)malloc(sizeof(char)*20);
		char *major = (char*)malloc(sizeof(char)*20);
		char *_else = (char*)malloc(sizeof(char)*100);
		fp = fopen("./user_data.txt", "a+");
		
		int exist = 0, not_pwd=0;
		while(1) {
				exist = 0;
				s_readfd = open(FIFO2, O_RDONLY, 0);
				read(s_readfd, &menu, sizeof(char));
				close(s_readfd);
				if(menu == '1') {
						char *message = "Sign Up Requested\0";
						s_writefd = open(FIFO1, O_WRONLY, 0);
						write(s_writefd, message, strlen(message));
						close(s_writefd);
						while(1) {
								memset(id, 0, 20);
								s_readfd = open(FIFO2, O_RDONLY, 0);
								read(s_readfd, id, sizeof(char)*20);
								close(s_readfd);
								fseek(fp, 0, SEEK_SET);
								while(fscanf(fp, "%s", _id) > 0) {
										//_id[strlen(id-1] = '\0';
										if(!strcmp(id, _id)) {
												s_writefd = open(FIFO1, O_WRONLY, 0);
												write(s_writefd, "exist\0", sizeof(char)*10);
												close(s_writefd);
												exist = 1;
												break;
										}
										exist = 0; //not exist
										fgets(_else, 100, fp);
										memset(_id, 0, sizeof(char)*20);
								}
								if(exist == 0) { //not exist untill the end >> successed
										s_writefd = open(FIFO1, O_WRONLY, 0);
										write(s_writefd, "not exist\0", sizeof(char)*10);
										close(s_writefd);
										s_readfd = open(FIFO2, O_RDONLY, 0);
										read(s_readfd, pwd, sizeof(char)*20);
										close(s_readfd);
										s_readfd = open(FIFO2, O_RDONLY, 0);
										read(s_readfd, num, sizeof(char)*20);
										close(s_readfd);
										s_readfd = open(FIFO2, O_RDONLY, 0);
										read(s_readfd, name, sizeof(char)*20);
										close(s_readfd);
										s_readfd = open(FIFO2, O_RDONLY, 0);
										read(s_readfd, major, sizeof(char)*20);
										close(s_readfd);
										fseek(fp, 0, SEEK_END);
										fprintf(fp, "%s %s %s %s %s\n", id, pwd, num, name, major);
										fflush(fp);
										break;
								}
								else continue;
						}
				}
				else if(menu == '2') {
						memset(id, 0, 20);
						memset(pwd, 0, 20);
						exist = 0;
						char *message = "Sign In Requested\0";
						s_writefd = open(FIFO1, O_WRONLY, 0);
						write(s_writefd, message, strlen(message));
						close(s_writefd);
						while(1) {
								s_readfd = open(FIFO2, O_RDONLY, 0);
								read(s_readfd, _id, sizeof(char)*20);
								close(s_readfd);
								s_readfd = open(FIFO2, O_RDONLY, 0);
								read(s_readfd, _pwd, sizeof(char)*20);
								close(s_readfd);
								fseek(fp, 0, SEEK_SET);
								while(fscanf(fp, "%s %s ", id, pwd)>0) {
										if(!strcmp(id, _id)) {
												if(!strcmp(pwd, _pwd)) {
														s_writefd = open(FIFO1, O_WRONLY, 0);
														write(s_writefd, "exist\0", sizeof(char)*12);
														close(s_writefd);
														exist = 1;
														break;
												}
												else {
														exist = 1;
														not_pwd =1;
														s_writefd = open(FIFO1, O_WRONLY, 0);
														write(s_writefd, "invalid pwd\0", sizeof(char)*12);
														close(s_writefd);
														break;
												}
										}
										else { 
												exist = 0;
										}
										fgets(_else, 100, fp);
										memset(id, 0, 20);
										memset(pwd, 0, 20);
										
								}
								if(exist == 1) {
										if(not_pwd == 1) {
												not_pwd = 0;
										}
										else break;
								}
								else {
										s_writefd = open(FIFO1, O_WRONLY, 0);
										write(s_writefd, "invalid id\0", sizeof(char)*12);
										close(s_writefd);
								}
										
						}
						break;
				}
				else {
						char* message = "Wrong Input\0";
						s_writefd = open(FIFO1, O_WRONLY, 0);
						write(s_writefd, message, strlen(message));
						close(s_writefd);
				}
		}
		library_server(id);
}
