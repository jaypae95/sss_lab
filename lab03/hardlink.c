/*----------------------------------------------------------------------------------
 * 파일: hardlink.c
 * 기능: hard link(argv[1]과 argv[2]를 hard link해준다.)
 * 개발자: 201520934 배재훈
 * 날짜: 1차 개발 : 2018년 3월 23일
 ----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
		if(link(argv[1], argv[2]) == -1) { //link argv[1] to argv[2], if fail>> err
				printf("link failed");
				exit(1);

		}

		printf("move %s to %s\n", argv[1], argv[2]); //print
		exit(0);

}
