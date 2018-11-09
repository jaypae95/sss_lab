/* ----------------------------------------------------------------------------------------------------
 *  파일: login.c
 *  기능	: 희원가입, 로그인
 *  개발자: 201520934 배재훈 
 *  날짜	: 1차 개발 : 2018년 4월 20일
 *----------------------------------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <ncurses.h>
#include <syslog.h>

void sig_handler(int); //SIGALRM
int select_menu(); //select menu
void sign_in(); //SIGUSR1
void sign_up(); //SIGUSR2

pid_t ppid; //parent pid
FILE *fp; //file pointer
int suc[2]; //pipe
char *root = "root"; //root id / password
#define KEY_CR_ 0x0d
#define KEY_BACKSPACE_ 0x7f

#define BUFLEN_MAX 255

#define TRY_MAX 3

#define INIT_X (0)
#define INIT_Y (0)

#define ID_X (INIT_X + 10)
#define ID_Y (INIT_Y + 3)

#define PASSWORD_X (ID_X)
#define PASSWORD_Y (ID_Y + 1)

#define RESULT_X (0)
#define RESULT_Y (PASSWORD_Y + 2)

#define EXPIRE_TIME 30
#define MODE_PASSWORD 1
#define MODE_ID 2

int main() {

		pid_t pid;
		char *succ = (char*)malloc(sizeof(char)*30); //success pipe

		signal(SIGUSR1, sign_up); //signal for sign_up
		signal(SIGUSR2, sign_in); //signal for sign_in

		fp = fopen("./info.txt", "a+"); //open info.txt, if not exist, create and open
		ppid = getpid(); //for kill function
		if(pipe(suc)) { //open pipe
				perror("pipe error\n");
				return 0;
		}

		while(1) {
				if((pid = fork()) < 0) {
						printf("fokr failed.\n");
						return 0;
				}
				else if (pid == 0) {
						select_menu(); //select menu fuction
						read(suc[0], succ, 18); //read success message from parent by pipe
						printf("%s\n", succ); 
						exit(0);
				}
				else {
						wait(0);
				}
		}
}

void sig_handler(int signum) { //time expired..SIGALRM handler
		endwin(); //close previous ncurses
		initscr(); //initiallize
		clear(); 
		move(INIT_Y,INIT_X); //from 0, 0
		printw("Timer expired.. (%d seconds)", EXPIRE_TIME);
		getch();
		refresh();
		endwin(); //close
		write(suc[1], " ", 1); //child is waiting for pipe
		exit(0);
}

int select_menu(parent) {

		int menu;
		printf("Press [1] to Sign UP and [2] to Sign IN : ");
		fflush(stdout); //flush stdout
		scanf("%d", &menu);
		getchar();
		if(menu == 1) { //sign up
				kill(ppid, SIGUSR1); //send signal to parent
		}
		else if(menu == 2) {//sign in
				kill(ppid, SIGUSR2); //send signal to parent
		}
		else {
				printf("Wrong Input....\n");
				exit(0);
		}
		

}

void sign_up(int signum) {
		char *new_id = (char*)malloc(sizeof(char)*20); //id
		char *new_pwd = (char*)malloc(sizeof(char)*20); //password
		pid_t pid;
		int status;
		int i; //count
		char* infile = (char*)malloc(sizeof(char)*100); //string in file
		bool exist; //exist or not in file
		
		initscr(); //initiallize
		while(1) {
			clear();
			move(INIT_Y, INIT_X); //form (0,0);
			printw(  "#############################################");
			printw("\n#####              Sign UP              #####");
			printw("\n#############################################");
			printw("\nUser ID  : ");
			printw("\nPassword : ");
			refresh();
			if(get_string(MODE_ID, new_id) <= 0 ) continue; //get id
			else {
					if(get_string(MODE_PASSWORD, new_pwd) <= 0) continue; //get password
					else {
							if(!strcmp(new_id, root)) { //if id is "root"
									clear();
									move(0,0);
									printw("Cannot create a root account!\n\n"); //cannot create
									getch();
									refresh();
									continue; //go to top of the while loop
							}
							fseek(fp,0, SEEK_SET); //set offset to the beginning
							i = 0;
							while(fgets(infile, 100, fp) != NULL) { //get string in file by each line
											if(i%3 == 0 ) { //id part											
													infile[strlen(infile)-1] = '\0'; //change '\n' to null
													if(!strcmp(new_id, infile)) { //already exist in file
														clear();
														move(0, 0);
														//cannot create
														printw("already exist. can't create account.\n");
														getch();
														refresh();
														exist = TRUE; //exist
														break;
													}
													else exist = FALSE; //not exist
											}
											memset(infile, 0, strlen(infile)); //initiallize
											i++;
							}
							if(exist == FALSE) { //not exist untill the end >> successed
								endwin();
								break;
							}
							else continue; //repeat
					}

			}
		}
		//sign up successed
		fprintf(fp, "%s\n", new_id); //id to file
		fprintf(fp, "%s\n\n", new_pwd); //password to file
		fflush(fp);
		write(suc[1], "Sign UP Successed!", 18); //send success message to child
		return;
}

void sign_in(int signum) {

		char *user_id = (char*)malloc(sizeof(char)*20); //id
		char *user_pwd = (char*)malloc(sizeof(char)*20); //password
		int i; //count
		char* infile = (char*)malloc(sizeof(char)*100); //id in file
		char* infile_pwd = (char*)malloc(sizeof(char)*100); //password in file
		bool exist; //exist or not

		signal(SIGALRM, sig_handler); //signal for alarm
		alarm(EXPIRE_TIME); //alarm (30 seconds in this code)
		initscr(); //initiallize
		int nTry = 0; 
		while(nTry < 3) { //if tried 3 times, break
			clear();
			move(INIT_Y, INIT_X); //from (0, 0);
			printw(  "#############################################");
			printw("\n#####              Sign IN              #####");
			printw("\n#############################################");
			printw("\nUser ID  : ");
			printw("\nPassword : ");
			refresh();
			if(get_string(MODE_ID, user_id) <= 0 ) nTry++; //get id
			else {
					if(get_string(MODE_PASSWORD, user_pwd) <= 0) nTry++; //get password
					else {
							fseek(fp,0, SEEK_SET); //set offset to the beginning
							i = 0;
							if(!strcmp(user_id, root)) { //if id is root
									if(!strcmp(user_pwd, root)) { //if password is root
											clear();
											move(0, 0);
											printw("Sign IN sucessed(root) !\n"); //successed
											getch();
											refresh();
											exist = TRUE; //think as it exsit
									}
									else { //if password is not root
											clear();
											move(0, 0);
											printw("incorrect password (root) !\n"); //failed
											getch();
											refresh();
											exist = FALSE; //think as it does not exist
									}
							}
							else { //if not root
									while(fgets(infile, 100, fp) != NULL) {
											if(i%3 == 0 ) {	//id part
													infile[strlen(infile)-1] = '\0'; //change '\n' to null
													if(!strcmp(user_id, infile)) { //if id is in file
															memset(infile_pwd, 0, strlen(infile_pwd));
															fgets(infile_pwd, 100, fp); //get the id's password
															infile_pwd[strlen(infile_pwd)-1] = '\0'; //change '\n' to null		
															if(!strcmp(user_pwd, infile_pwd)) { //if id and password matches
																	clear(); 
																	move(0,0);
																	printw("Sign IN sucessed !\n"); //successed
																	getch();
																	refresh();
																	exist = TRUE; //exist
																	break;
															}
															else { //id and password does not match
																	clear();
																	move(0,0);
																	printw("Incorrect Password !\n"); //failed
																	getch();
																	refresh();
																	exist = FALSE; //not exist
																	break;
															}							
													}
											}
											memset(infile, 0, strlen(infile));
											i++;
											exist = FALSE; //not exist
									}
							}
							if(exist == FALSE) { //not exist untill the end
									if(!strcmp(user_id, infile) || !strcmp(user_id, root)) { //if the id was there or id was root but failed
											nTry++; //password fail >> try agian, try count +1
									}
									else { //if the id was not there
											clear();
											move(0, 0);
											printw("Invalid ID !\n"); //invalid id
											getch();	
											refresh();
											nTry++; //try again, try count +1
									}
							}
							else { //if successed
									clear();
									move(0, 0);
									printw("Good luck on your mid-term exam~!\n"); //print lucky message for mid-term
									getch();
									refresh();
									endwin(); //close
									write(suc[1], " ", 1); //child is waiting for pipe
									exit(0); //end program.
									break;
							}		
					}
			}
		}
		if(nTry>=TRY_MAX) { //if tried 3times
				clear();
				move(0, 0);	
				printw("Fail to Sign IN !! (you tried %d times)\n", nTry); //failed
				getch();
				refresh();
				endwin(); //close
				write(suc[1], " ", 1); //child is waiting for pipe
				exit(0); //end program.
		}
}

int get_string(int mode, char *buf) {
		
		int n, res;
		char ch;
		if((mode != MODE_PASSWORD) && (mode != MODE_ID)) //if mode is not id or password
				return -1; //return error
		memset(buf, 0, strlen(buf));
		noecho();
		mode == MODE_PASSWORD ? move(PASSWORD_Y, PASSWORD_X) : move(ID_Y, ID_X);
		refresh();
		n = 0;
		while((res = read(0, &ch, 1))) { //read one character
				if(res<0) return -1;
				if(ch == KEY_CR_) break; //if enter, break
				if(ch == KEY_BACKSPACE_) { //if key is backspace
						if(n>0) {
								n--; //move to front
								mode == MODE_PASSWORD ? move(PASSWORD_Y, PASSWORD_X + n) : move(ID_Y, ID_X + n);

								printw(" "); //switch character to space,to be seems nothing there
								mode == MODE_PASSWORD ? move(PASSWORD_Y, PASSWORD_X + n) : move(ID_Y, ID_X + n);
								buf[n] = '\0';
								refresh();
						}
				}
				else {
						mode == MODE_PASSWORD ? printw("*") : printw("%c", ch); //if mode is password, mask to *
						refresh();

						buf[n++] = ch; //inset on buf one by one
						if(n>= BUFLEN_MAX) return -1;
				}
		}
		buf[n] = '\0';
		return n;
}
