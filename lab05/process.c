#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <time.h>
int num_child = 0; //number of child
int i = 1; //to print 5000*i process
int main() {
		pid_t pid;
		time_t tm;
		struct sysinfo sys; //to get system memory

		printf("Writing on \"log.txt\"......(My process ID : %d)\n", getpid());
		FILE *fp;
		if (creat("./log.txt", 0644) < 0 ) { //create file, if fail print error
				printf("fail to create \"log.txt\"\n");
				return 0;
		}
		close(fileno(fp)); //close

		if((fp = fopen("./log.txt", "w")) == NULL) { //open file, if fail print error
				printf("fail to open \"log.txt\"");
				return 0;
		}

		for( ; ; ) { //infinitely
				++num_child; //increase number of child

				if(num_child == (5000* i)) { //print(not to be bored waiting for out of resources)
						printf("%d Processes has been created! Still creatring..\n", 5000*i++);

				}

				if((pid = fork()) < 0 ) { //fork
						time(&tm); //get time
						printf("Time : %s\n",  ctime(&tm)); //print time
						fprintf(fp, "Time : %s\n", ctime(&tm));
						fclose(fp);
						perror("fork error"); //failed
						return 0;
				}
				else if (pid == 0) { //child
						sysinfo(&sys); //to get system memory
						//print to file
						fprintf(fp, "Child:%d PID:%d\nMemoryUsed:%.2f%% MemoryLeft:%.2f%%\n\n", num_child, getpid(), ((float)sys.totalram-(float)sys.freeram)/(float)sys.totalram*100,(float)sys.freeram/(float)sys.totalram*100);
						
						exit(0);
				}		
			
		}
				fclose(fp); //close
}
