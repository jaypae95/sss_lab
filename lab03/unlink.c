/*----------------------------------------------------------------------------------
 * 파일: unlink.c
 * 기능: unlink(argv[1]를 unlink해준다.
 * 개발자: 201520934 배재훈
 * 날짜: 1차 개발 : 2018년 3월 23일
 ----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
		if(unlink(argv[1]) == -1) { //unlink argv[1], if fail >> err
				printf("unlink failed");
				//unlink(argv[2]); // i don't think we need this
				exit(1);
		}

		printf("move %s to %s\n", argv[1], argv[2]); //print
		exit(0);
}
