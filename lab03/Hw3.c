/*----------------------------------------------------------------------------------
 * 파일: Hw3.c
 * 기능: 파일을 create, open, close, write해주고 lseek로 오프셋 이동
 * 개발자: 201520934 배재훈
 * 날짜: 1차 개발 : 2018년 3월 23일
 ----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#define BUFF_SIZE 1024
int main() {
		char temp[BUFF_SIZE];
		int fd;
		int tmp_length; 
		int i;

		if((fd = creat("./exam.txt", 0644)) < 0) { //create, if fail>> err
				printf("fail to create(1) the file \"exam.txt\"\n");
				return 0;
		}

		if(close(fd) < 0) { //close, if fail>> err
				printf("fail to close(1) the file \"exam.txt\"\n");
				return 0;
		}
		
		if((fd = open("./exam.txt", O_RDWR))> 0) { //open, if success
				if (read(0, temp, BUFF_SIZE) <0) { //read from keyboard if fail>> err
						printf("fail to read(1) the file \"exam\"\n");
						return 0;
				}
				tmp_length = strlen(temp); // save the length of temp
				
				if(write(fd, temp, tmp_length) < 0) { //write, if fail>> err
						printf("fail to write(1) on file \"exam.txt\"\n");
						return 0;
				}

				if(close(fd)<0) { //close, if fail>> err
						printf("fail to close(2) the file \"exam.txt\"\n");
						return 0;
				}
		}
		else { //if open failed>>  err
 					printf("fail to open(1) the file \"exam.txt\"\n");
					return 0;
		}		

		if((fd = open("./exam.txt", O_RDWR))>0) { //if open successed
				for (i = 0; i < tmp_length-1; i+=2) { //0 to length-1(not to print the last "\n"), increased by 2 
						lseek(fd, i, SEEK_SET); // "i" is increased by 2 >> move by 2
						if(read(fd, temp, tmp_length)>0) { //read, if success 
							temp[tmp_length-i] = '\0'; //before temp[tmp_length-i] is the end of the string
							puts(temp); //print
						}
						else { //if read failed
								printf("fail to read(2) the file \"exam.txt\"\n");
								return 0;
						}

				}
				
		}
		else printf("fail to open(2) the file \"exam.txt\"\n"); //if open failed

		if(close(fd) < 0 ) { //close, if fail >> err
				printf("fail to close(3) the file \"exam.txt\"\n");
				return 0;
		}

		if((fd = open("./exam.txt", O_RDWR))>0) { //open, if successed
			for ( i=4; i<=tmp_length; i+=3) { //"i" is 4(to avoid printing \n and start from 3 word) to tmp_length,
												//increased by 3
					lseek(fd, -i, SEEK_END); // move backward by 3
					if(read(fd, temp, tmp_length)>0) { //read, if success
							temp[i] = '\0'; //before temp[i] is the end of the string
							puts(temp);//print
					}
					else { //if read failed
							printf("fail to read(3) the file \"exam.txt\"\n");
							return 0;
					}
			}
		}
		else {
				printf("fail to open(2) the file \"exam.txt\"\n");
				return 0;
		}

		if(close(fd) < 0) {
				printf("fail to close(4) the file \"exam.txt\"\n");
				return 0;
		}


		return 0;
}
