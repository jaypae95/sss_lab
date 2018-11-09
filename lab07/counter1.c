/* ----------------------------------------------------------------------------------------------------
 *  파일: counter1.c
 *  기능	: 경쟁조건이 발생하는 counting 프로그램
 *  개발자: 201520934 배재훈
 *  날짜	: 1차 개발 : 2018년 5월 4일 
 *----------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
void *counter(void *arg);
int cnt = 0; //전역변수

int main() {
		pthread_t tid[5]; //쓰레드 배열
		int i;
		for(i=0; i<5; i++) {
				if(pthread_create(&tid[i], NULL, counter,  NULL) != 0) {//쓰레드 5개 생성
 						printf("fail to create thread.\n");
						return 0;
				}
		}
		for(i=0; i<5; i++) {
				if(pthread_join(tid[i], NULL) != 0 ) { //쓰레드 5개를 기다림
						printf("fail to join thread/\n");
						return 0;
				}
		}
		return 0;
}

void *counter(void *args) {
		int tmp, j;
		for(j=0; j<100; j++) { //각 쓰레드마가 100번씩 count (총 500번의 count)
				tmp = cnt; //cnt를 tmp에 저장 후
				usleep(1); //경쟁 조건이 일어나도록 시간을 아주 살짝 멈춤
				tmp++; //tmp값 증가
				cnt = tmp; //증가시킨 tmp 값을 cnt에 저장				
				printf("%d\n", cnt); 		
		}
		pthread_exit((void*)0); //쓰레드 종료
}				
