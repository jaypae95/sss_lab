#include "fake_apue.h"

int main() {
		pid_t pid;

		if((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST)) {
				printf("fifo error\n");
				return 0;
		}
		if((mkfifo(FIFO2, FILE_MODE)<0) && (errno != EEXIST)) {
				printf("fifo error\n");
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
