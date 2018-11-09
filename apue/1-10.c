#include "apue.h"
#include <sys/wait.h>

static void sig_int(int);

int main() {
		char buf[MAXLINE];
		pid_t pid;
		int status;

		if(signal(SIGINT, sig_int) == SIG_ERR) {
				printf("signal error");
				return 0;
		}

		printf("%% ");
		while(fgets(buf, MAXLINE, stdin) != NULL) {
				if (buf[strlen(buf)-1] == '\n') {
						buf[strlen(buf) -1 ] = 0;
				}
				if((pid = fork())<0) {
						printf("fork error");
						return 0;
				}
				else if (pid == 0) {
						execlp(buf, buf, NULL);	
						printf("couldn't execute: %s", buf);
						exit(127);
				}

				if((pid = waitpid(pid, &status, 0)) < 0) {
						printf("error\n");
						return 0;
				}	
				printf("%% ");
		}

		exit(0);
}

void sig_int(int signo) {
		printf("interrupt\n%% ");
}
