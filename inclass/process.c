#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int num_of_child = 0;

int main() {
		pid_t pid;

		printf("My prodcess ID : %d\n", getpid());

		for( ; ; ) {
				++num_of_child;
				if((pid = fork()) < 0 ) {
						perror("fork error");
						exit(0);
				}
				else if (pid == 0) {
						printf("Child %d process PID(%d), PPID(%d)\n", num_of_child, getpid(), getppid());
						sleep(2);
						exit(0);
				}
			sleep(2);	
		}

}
