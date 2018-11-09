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
				recv(s_c_sock, &menu, sizeof(char), 0);
				if(menu == '1') {
						char *message = "Sign Up Requested\0";
						send(s_c_sock, message, strlen(message), 0);
						printf("%s\n", message);
						while(1) {
								memset(id, 0, 20);
								recv(s_c_sock, id, sizeof(char)*20, 0);
								fseek(fp, 0, SEEK_SET);
								while(fscanf(fp, "%s", _id) > 0) {
										//_id[strlen(id-1] = '\0';
										if(!strcmp(id, _id)) {
												send(s_c_sock, "exist\0", sizeof(char)*10, 0);
												exist = 1;
												break;
										}
										exist = 0; //not exist
										fgets(_else, 100, fp);
										memset(_id, 0, sizeof(char)*20);
								}
								if(exist == 0) { //not exist untill the end >> successed
										send(s_c_sock, "not exist\0", sizeof(char)*10, 0);
										recv(s_c_sock, pwd, sizeof(char)*20, 0);
										recv(s_c_sock, num, sizeof(char)*20, 0);
										recv(s_c_sock, name, sizeof(char)*20, 0);
										recv(s_c_sock, major, sizeof(char)*20, 0);
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
						send(s_c_sock, message, strlen(message), 0);
						printf("%s\n", message);
						while(1) {
								recv(s_c_sock, _id, sizeof(char)*20, 0);
								recv(s_c_sock, _pwd, sizeof(char)*20, 0);
								fseek(fp, 0, SEEK_SET);
								while(fscanf(fp, "%s %s ", id, pwd)>0) {
										if(!strcmp(id, _id)) {
												if(!strcmp(pwd, _pwd)) {
														send(s_c_sock, "exist\0", sizeof(char)*12, 0);
														exist = 1;
														break;
												}
												else {
														exist = 1;
														not_pwd =1;
														send(s_c_sock, "invalid pwd\0", sizeof(char)*12, 0);
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
										send(s_c_sock, "invalid id\0", sizeof(char)*12, 0);
								}
										
						}
						break;
				}
				else {
						char* message = "Wrong Input\0";
						send(s_c_sock, message, strlen(message), 0);
				}
		}
		library_server(id);
}
