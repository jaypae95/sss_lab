#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
		if (argc != 1) {
				printf("Usage : ./pwd [no option!]");
				return 0;
		}

		pid_t pid;
		/*-------------EXECL-------------*/
		if((pid = fork())<0) { //fork
				printf("fork failed.."); //failed
				return 0;
		}else if (pid == 0) { //child
				printf("Execute with \"execl\"\n");
				execl("/bin/pwd", "pwd", NULL); //pwd wirh exel
		}else wait(); //parent wait
		printf("\n");
		/*-------------EXECLP-------------*/
		if((pid = fork())<0) { //fork
				printf("fork failed.."); //failed
				return 0;
		}else if (pid == 0 ) { //child
				printf("Execute with \"execlp\"\n");
				execlp("pwd", "pwd", NULL); //pwd with execlp
		}else wait(); //parent wait
		printf("\n");
		/*-------------EXECLE------------*/
		if((pid = fork())<0) { //fork
				printf("fork failed.."); //failed
				return 0;
		}else if (pid == 0) { //child
				printf("Execute with \"execle\"\n"); 
				execle("/bin/pwd", "pwd", NULL, NULL); //pwd with execle
		}else wait(); //parent wait
		printf("\n");
		/*-------------EXECV-------------*/
		if ((pid = fork())<0) { //fork
				printf("fork failed.."); //failed
				return 0;
		}else if (pid == 0) { //child
				char *cmd[] = {"pwd", NULL}; // pwd into string array
				printf("Execute with \"execv\"\n");
				execv("/bin/pwd", cmd); //pwd with execv
		}else wait(); //parent wait
		printf("\n");
		/*-------------EXECVP-------------*/
		if ((pid = fork())<0) { //fork
				printf("fork failed.."); //failed
				return 0;
		}else if (pid == 0) { //child
				char *cmd[] = {"pwd", NULL}; //pwd into string array
				printf("Execute with \"execvp\"\n");
				execvp("/bin/pwd", cmd); //pwd with execvp
		}else wait(); //parent wait
		printf("\n");
		/*-------------EXECVE-------------*/
		if ((pid = fork())<0) { //fork
				printf("fork failed.."); //failed
				return 0;
		}else if (pid == 0) { //child
				char *cmd[] = {"pwd", NULL}; //pwd into string array
				printf("Execute with \"execve\"\n");
				execve("/bin/pwd", cmd, NULL); //pwd with execve
		}else wait(); //parent wait

		
}
