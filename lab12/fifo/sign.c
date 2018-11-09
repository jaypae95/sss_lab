#include "fake_apue.h"

void sign_up() {
		char *new_id = (char*)malloc(sizeof(char)*20); //id
		char *new_pwd = (char*)malloc(sizeof(char)*20); //password
		char *new_num = (char*)malloc(sizeof(char)*20);
		char *new_name = (char*)malloc(sizeof(char)*20);
		char *new_major = (char*)malloc(sizeof(char)*20);
		char *exist = (char*)malloc(sizeof(char)*12);
		int status;
		int i; //count
		char* infile = (char*)malloc(sizeof(char)*100); //string in file
		initscr();
		setvbuf(stdout, 0, _IONBF, 0);
		setvbuf(stdin, 0, _IONBF, 0);
		while(1) {
			memset(new_id, 0, sizeof(char)*20);
			memset(new_pwd, 0, sizeof(char)*20);
			memset(new_num, 0, sizeof(char)*20);
			memset(new_name, 0, sizeof(char)*20);
			memset(new_major, 0, sizeof(char)*20);

			clear();
			move(INIT_Y, INIT_X); //form (0,0);
			printw(  "#############################################");
			printw("\n#####              Sign UP              #####");
			printw("\n#############################################");
			printw("\nUser ID  : ");
			printw("\nPassword : ");
			printw("\nStudent# : ");
			printw("\nName     : ");
			printw("\nMajor    : ");
			refresh();

			get_string_count = 0;
			get_string(MODE_ID, new_id);
			get_string(MODE_PASSWORD, new_pwd);
			get_string(MODE_ID, new_num);
			get_string(MODE_ID, new_name);
			get_string(MODE_ID, new_major);
			
			c_writefd = open(FIFO2, O_WRONLY, 0);
			write(c_writefd, new_id, strlen(new_id));
			close(c_writefd);
			c_readfd = open(FIFO1, O_RDONLY, 0);
			read(c_readfd, exist, sizeof(char)*12);
			close(c_readfd);
			if(!strcmp(exist, "exist")) {
					clear();
					move(0, 0);
					printw("already exist. can't create account.\n");
					getch();
					refresh();
			}
			else {
					clear();
					move(0, 0);
					printw("SIGN UP SUCCESSED!\n");
					getch();
					refresh();
					endwin();
					c_writefd = open(FIFO2, O_WRONLY, 0);
					write(c_writefd, new_pwd, sizeof(char)*20);
					close(c_writefd);
					c_writefd = open(FIFO2, O_WRONLY, 0);
					write(c_writefd, new_num, sizeof(char)*20);
					close(c_writefd);
					c_writefd = open(FIFO2, O_WRONLY, 0);
					write(c_writefd, new_name, sizeof(char)*20);
					close(c_writefd);
					c_writefd = open(FIFO2, O_WRONLY, 0);
					write(c_writefd, new_major, sizeof(char)*20);
					close(c_writefd);
					break;
			}
		}

}

void sign_in() {

		char *user_id = (char*)malloc(sizeof(char)*20); //id
		char *user_pwd = (char*)malloc(sizeof(char)*20); //password
		char *exist = (char*)malloc(sizeof(char)*12);

		initscr(); //initiallize
		setvbuf(stdout, 0, _IONBF, 0);
		setvbuf(stdin, 0, _IONBF, 0);
		while(1) { //if tried 3 times, break
			memset(user_id, 0, sizeof(char)*20);
			memset(user_pwd, 0, sizeof(char)*20);

			get_string_count = 0;
			clear();
			move(INIT_Y, INIT_X); //from (0, 0);
			printw(  "#############################################");
			printw("\n#####              Sign IN              #####");
			printw("\n#############################################");
			printw("\nUser ID  : ");
			printw("\nPassword : ");
			refresh();

			get_string(MODE_ID, user_id); //get id
			get_string(MODE_PASSWORD, user_pwd); //get password
			c_writefd = open(FIFO2, O_WRONLY, 0);
			write(c_writefd, user_id, sizeof(char)*20);
			close(c_writefd);
			c_writefd = open(FIFO2, O_WRONLY, 0);
			write(c_writefd, user_pwd, sizeof(char)*20);
			close(c_writefd);
			c_readfd = open(FIFO1, O_RDONLY, 0);
			read(c_readfd, exist, sizeof(char)*12);
			close(c_readfd);

			if(!strcmp(exist, "exist")) {
					clear(); 
					move(0,0);
					printw("Sign IN sucessed !\n"); //successed
					getch();
					refresh();
					endwin();
					break;
			}
			else{
					memset(user_id, 0, 20);
					memset(user_pwd, 0, 20);
					if(!strcmp(exist, "invalid pwd")) {
							clear();
							move(0, 0);
							printw("Incorrect Password!\n");
							getch();
							refresh();
					}
					else if(!strcmp(exist, "invalid id")) {
							clear();
							move(0, 0);
							printw("Invalid ID!\n");
							getch();
							refresh();
					}
			}

		}
}
