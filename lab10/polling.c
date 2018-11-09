#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <sys/time.h>
#include <fcntl.h>
#include <string.h>

//int pipefd[2]; //pipe
int main(int argc, char *argv[]) {

		if (argc != 2) {
				printf("Usage : ./polling [word]\n");
				return 0;
		}
		int i,j, index = 0, linecount=0, sum = 0;
		int line_per_file;
		struct pollfd fds[5];
		int fd[5];
		FILE *fp;
		int ret, res;
		char *buf = (char*)malloc(sizeof(char)*512);
		char *word = (char*)malloc(sizeof(char)*20);
		char alph;
		int obj[5]={ 0, };
		memset(fds, 0, sizeof(fds));
		memset(buf, 0, sizeof(buf));

		i=0;
		while(argv[1][i] != '\0') {
				if(isupper((int)argv[1][i])) {
						argv[1][i]+=32;
				}
				i++;
		}
		system("mkdir ./workspace");

		if((fp = fopen("./long.txt", "r")) < 0 ) {
				printf("open error\n");
				return 0;
		}
		while(fgets(buf, 512, fp) != 0) {
				linecount++;
		}
		line_per_file = linecount / 5;
		fseek(fp, 0, SEEK_SET);
		if((fd[0] = open("./workspace/example1.txt", O_RDWR | O_CREAT | O_TRUNC, 0644))<0) {
				printf("open error\n");
				return 0;
		}
		if((fd[1] = open("./workspace/example2.txt", O_RDWR | O_CREAT | O_TRUNC, 0644))<0) {
				printf("open error\n");
				return 0;
		}
		if((fd[2] = open("./workspace/example3.txt", O_RDWR | O_CREAT | O_TRUNC, 0644))<0) {
				printf("open error\n");
				return 0;
		}
		if((fd[3] = open("./workspace/example4.txt", O_RDWR | O_CREAT | O_TRUNC, 0644))<0) {
				printf("open error\n");
				return 0;
		}
		if((fd[4] = open("./workspace/example5.txt", O_RDWR | O_CREAT | O_TRUNC, 0644))<0) {
				printf("open error\n");
				return 0;
		}

		for(i=0; i<5; i++) {
				if(i==4) line_per_file +=4;
				for(j=0;j<line_per_file; j++) {
						if(fgets(buf, 512, fp) == 0 ) break;
						buf[strlen(buf)-1] = '\0';
						write(fd[i], buf, strlen(buf));
						write(fd[i], "\n", 1);
				}
		}

		for(i=0; i<5; i++) {
				fds[i].fd = fd[i];
				fds[i].events = POLLIN;
				lseek(fds[i].fd, 0, SEEK_SET);
		}
		argv[1][strlen(argv[1])] = '\0';
		ret = poll(fds, 5, 5000);
		if(ret == -1) {
				printf("poll error\n");
		}
		else if(ret == 0) {
				printf("timeout occurerd\n");
		}
		else {
				for(i = 0; i<5; i++) {
						if(fds[i].revents & (POLLIN)) {
								while(1) {
										if((res = read(fds[i].fd, &alph, 1)) == 0) {
												break;
											}
										else if(res<0) {
												return 0;
										}
										else {
												if(alph == ' ' || alph == '\n') {
														word[strlen(word)] = '\0';
														if(!strcmp(word, argv[1])) {
																obj[i]++;
														}
														memset(word, 0, strlen(word));
														index = 0;
												}
												else if(isalpha((int)alph) || alph == '-' || alph == '\''){
														if(isupper((int)alph)) {
																alph +=32;
														}
												word[index++] = alph;
												}
										}
								}
						}
				}
		}

		for(i=0; i<5; i++) {
				printf("fd[%d] : %d\n", i, obj[i]);
				sum += obj[i];
		}
		printf("sum of the word \"%s\" : %d\n", argv[1], sum);

		if(sum == 0) {
				for(i=0; i<5; i++){
						write(fd[i], argv[1], strlen(argv[1]));
						write(fd[i], "\n", 1);
				} 
		}


		return 0;
}
