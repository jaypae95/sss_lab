#include <time.h>
#include <signal.h>
#include <setjmp.h>
#include <ncurses.h>
#include <syslog.h>
#include <string.h>
#include <stdlib.h>

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

#define EXPIRE_TIME 5
#define BASIC_TIME 5

int g_remain;
int g_timer_param;

void sig_handler(int signum) {
		if(signum != SIGALRM) exit(0);

		if(g_timer_param == EXPIRE_TIME) {
				clear();
				move(INIT_Y, INIT_X);
				printw("Timer expired.. (%d seconds)", EXPIRE_TIME);
				refresh();
				getch();
				endwin();
				exit(0);
		}
		else if(g_timer_param == BASIC_TIME) {
				g_timer_param = EXPIRE_TIME;
				g_remain -= BASIC_TIME;
				alarm(g_remain);
		}

		else {
				clear();
				move(0,0);
				printw("illegal parameter...");
				refresh();
				getch();
				exit(0);
		}
}

void draw_interface() {
		clear();
		move(INIT_Y, INIT_X);
		printw(  "#############################################");
		printw("\n# (Chap 9.2) Login program using signal     #");
		printw("\n#############################################");
		printw("\nLogin ID : ");
		printw("\nPassword : ");
		refresh();
}

#define MODE_PASSWORD 1
#define MODE_ID 2

int get_string(int mode, char *buf) {
		int n, res;
		char ch;

		if((mode != MODE_PASSWORD) && (mode != MODE_ID)) 
				return -1;

		memset(buf, 0, BUFLEN_MAX);

		noecho();

		mode == MODE_PASSWORD ? move(PASSWORD_Y, PASSWORD_X) : move(ID_Y, ID_X);

		refresh();

		n = 0;
		while((res = read(0, &ch, 1))) {
				if(res<0) return -1;
				if(ch == KEY_CR_) break;

				if(g_remain < BASIC_TIME) {
						g_timer_param = EXPIRE_TIME;
						alarm(g_remain);
						g_remain = 0;
				}
				else {
						g_timer_param = BASIC_TIME;
						alarm(BASIC_TIME);
				}

				if(ch == KEY_BACKSPACE_) {
						if(n>0) {
								n--;
								mode == MODE_PASSWORD ? move(PASSWORD_Y, PASSWORD_X + n) : move(ID_Y, ID_X + n);

								printw(" ");
								mode == MODE_PASSWORD ? move(PASSWORD_Y, PASSWORD_X + n) : move(ID_Y, ID_X + n);
								refresh();
						}
				}
				else {
						mode == MODE_PASSWORD ? printw("*") : printw("%c", ch);
						refresh();

						buf[n++] = ch;
						if(n>= BUFLEN_MAX) return -1;
				}
		}
		buf[n] = '\0';

		return n;
}

int main(int argc, char *argv[]) {
		int nTry;
		char buf_login[BUFLEN_MAX], buf_password[BUFLEN_MAX];

		const char *user_login = "jaypae";
		const char *user_password = "1111";

		struct sigaction sa;

		pid_t pid;

		if(pid = fork() > 0) wait(0);
		initscr();

		memset(&sa, 0, sizeof(struct sigaction));
		sa.sa_handler = sig_handler;
		sigfillset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGALRM, &sa, NULL);

		g_remain = EXPIRE_TIME;
		g_timer_param = EXPIRE_TIME;
		alarm(0);
		alarm(EXPIRE_TIME);

		nTry = 0;
		while(nTry < TRY_MAX) {
				draw_interface();

				if(get_string(MODE_ID, buf_login) <= 0) nTry ++;
				else {
						if(get_string(MODE_PASSWORD,buf_password) <= 0) nTry ++;
						else {
								if(!strcmp(buf_login, user_login) && !strcmp(buf_password, user_password)) break;
								else nTry++;
						}
				}
		}
		clear();
		move(INIT_Y, INIT_X);

		nTry < TRY_MAX ? printw("Corrcet !!\n*ID= %s\n*Password= %s", buf_login, buf_password) : printw("Fail to login !! (you tried %d times)", nTry);
		refresh();
		getch();
		endwin();
		return 0;
}
