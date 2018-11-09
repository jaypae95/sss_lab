/* ----------------------------------------------------------------------------------------------------
 *  파일: free.c
 *  기능	: 6가지 exec함수를 활용한 free 명령어 구현 
 *  개발자: 201520934 배재훈
 *  날짜	: 1차 개발 : 2018년 4월 6일 
 *----------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

		int j = 1;
		int i, k;
		char *option = (char *)malloc(sizeof(char)*30); //for option
		char *cmd = (char*)malloc(sizeof(char)*10); //for command
		strcpy(cmd,argv[0]+2);	//delete "./"
		char path[5][30] = {"/usr/bin/", "/usr/local/bin","/bin/", "/usr/sbin/", "/sbin/" }; //path for command
		if( argc>1 ) { //combine option together.
				option[0] = '-';
				for(i = 1; i < argc; i++) {
						while(argv[i][j] != '\0') {
							option[strlen(option)] = argv[i][j++];
							
						}
						j = 1;
				}
		} //combine complete!

		pid_t pid;

		/*execl*/
		if((pid = fork())<0) { //fork
				printf("fork failed.\n"); //fail
				return 0;
		}else if(pid == 0) { //child
				int pathcheck; //integer for loop
				printf("\n===============Execute with execl===============\n");
				for(pathcheck = 0; pathcheck<5; pathcheck++) { //to check where the command file is
						char tmp[50];
						strcpy(tmp, path[pathcheck]); //path>>tmp
						strcpy(tmp+(strlen(path[pathcheck])), cmd); //+command>>tmp
						if(argc >1) execl(tmp, cmd, option ,NULL); //execl
						else execl(tmp,cmd, NULL); //execl with no option

				}
				printf("execl error.\n"); //error
				exit(0);
		}else wait(0); //wait for child.
        
		printf("\n");
		/*execlp*/
		if((pid = fork())<0) { //fork
				printf("fork failed.\n"); //fail
				return 0;
		}else if(pid == 0) { //child
				printf("\n===============Execute with execlp===============\n");
				if(argc>1) execlp(cmd, cmd, option ,NULL); //execlp
				else execlp(cmd, cmd, NULL);//execlp with no option
				printf("execlp error.\n");//error
				exit(0);

		}else wait(0); //wait for child
		printf("\n");

		/*execle*/
		if((pid = fork())<0) { //fork
				printf("fork failed.\n"); //fail
				return 0;
		}else if(pid == 0) { //child
				int pathcheck; //integer for loop
				printf("\n===============Execute with execle===============\n");
				for(pathcheck = 0; pathcheck<5; pathcheck++) { //to check where the command file is
						char tmp[50]; 
						strcpy(tmp, path[pathcheck]); //path>>tmp
						strcpy(tmp+(strlen(path[pathcheck])), cmd); //+command>>tmp 
						if (argc>1) execle(tmp, cmd, option ,NULL, NULL); //execle
						else execle(tmp, cmd, NULL, NULL); //execle with no option
				}
				printf("execle error.\n"); //error
				exit(0);
		}else wait(0); //waith for child

		printf("\n");

		/*execv*/
		if((pid = fork())<0) { //fork
				printf("fork failed.\n"); //fail
				return 0;
		}else if(pid == 0) { //child
				int pathcheck; //integer for loop
				printf("\n===============Execute with execv===============\n");
				for(pathcheck = 0; pathcheck<5; pathcheck++) { //to check where the command file is
						char tmp[50];
						strcpy(tmp, path[pathcheck]); //path>>tmp
						strcpy(tmp+(strlen(path[pathcheck])), cmd);//+command>>tmp
						execv(tmp, argv); //execv
				
				}
				printf("execv error.\n"); //error
				exit(0);
		}else wait(0); //wait for child

		printf("\n");

		/*execvp*/
		if((pid = fork())<0) { //fork
				printf("fork failed.\n"); //fail
				return 0;
		}else if(pid == 0) { //child
				printf("\n===============Execute with execvp===============\n");
				execvp(cmd, argv); //execvp
				printf("execvp error.\n"); //error
				exit(0); 
		}else wait(0); //wait for child

		printf("\n");

		/*execve*/
		if((pid = fork())<0) { //fork
				printf("fork failed.\n"); //fail
				return 0;
		}else if(pid == 0) { //child
				int pathcheck; //integer for loop
				printf("\n===============Execute with execve===============\n");
				for(pathcheck = 0; pathcheck<5; pathcheck++) { //to check where the command file is
						char tmp[50];
						strcpy(tmp, path[pathcheck]); //path>>tmp
						strcpy(tmp+(strlen(path[pathcheck])), cmd); //+command>>tmp
						execve(tmp, argv, NULL);//execve
				}
				printf("execve error.\n"); //error
				exit(0);
		}else wait(0); //wait for child

		printf("\n");
}

