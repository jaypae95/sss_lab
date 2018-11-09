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
				read(fd1[0], &menu, sizeof(char));
				if(menu == '1') {
						char *message = "Sign Up Requested\0";
						write(fd2[1], message, strlen(message));
						while(1) {
								memset(id, 0, 20);
								read(fd1[0], id, sizeof(char)*20);
								fseek(fp, 0, SEEK_SET);
								while(fscanf(fp, "%s", _id) > 0) {
										//_id[strlen(id-1] = '\0';
										if(!strcmp(id, _id)) {
												write(fd2[1], "exist\0", sizeof(char)*10);
												exist = 1;
												break;
										}
										exist = 0; //not exist
										fgets(_else, 100, fp);
										memset(_id, 0, sizeof(char)*20);
								}
								if(exist == 0) { //not exist untill the end >> successed
										write(fd2[1], "not exist\0", sizeof(char)*10);
										read(fd1[0], pwd, sizeof(char)*20);
										read(fd1[0], num, sizeof(char)*20);
										read(fd1[0], name, sizeof(char)*20);
										read(fd1[0], major, sizeof(char)*20);
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
						write(fd2[1], message, strlen(message));
						while(1) {
								read(fd1[0], _id, sizeof(char)*20);
								read(fd1[0], _pwd, sizeof(char)*20);
								fseek(fp, 0, SEEK_SET);
								while(fscanf(fp, "%s %s ", id, pwd)>0) {
										if(!strcmp(id, _id)) {
												if(!strcmp(pwd, _pwd)) {
														write(fd2[1], "exist\0", sizeof(char)*12);
														exist = 1;
														break;
												}
												else {
														exist = 1;
														not_pwd =1;
														write(fd2[1], "invalid pwd\0", sizeof(char)*12);
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
										write(fd2[1], "invalid id\0", sizeof(char)*12);
								}
										
						}
						break;
				}
				else {
						char* message = "Wrong Input\0";
						write(fd2[1], message, strlen(message));
				}
		}
		library_server(id);
}
