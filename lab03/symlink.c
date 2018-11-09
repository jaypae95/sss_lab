/*----------------------------------------------------------------------------------
 * 파일: symlink.c
 * 기능: symbolic link(argv[1]과 argv[2]를 symbolic link해준다.)
 * 개발자: 201520934 배재훈
 * 날짜: 1차 개발 : 2018년 3월 23일
 ----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
		if(symlink(argv[1], argv[2]) == -1) { //link(symbolic) argv[1] to argv[2]
				printf("symlink failed");
				exit(1);
		}
		printf("link %s to %s\n", argv[1], argv[2]);//print
		exit(0);

}
