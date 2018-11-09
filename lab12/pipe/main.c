#include "fake_apue.h"

int main() {
		pid_t pid;

		if(pipe(fd1) <0 || pipe(fd2)<0) {
				printf("pipe error\n");
				return 0;
		}

		if((pid = fork()) < 0) {
				printf("fork error\n");
				return 0;
		}

		else if(pid == 0) {
				_client();
		}
		else {
				_server();
				wait(0);
		}

		return 0;
}
