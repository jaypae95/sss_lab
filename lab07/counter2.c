/* ----------------------------------------------------------------------------------------------------
 *  파일: counter2.c
 *  기능	: 경쟁조건이 발생하지 않는 동기화 된 counting 프로그램
 *  개발자: 201520934 배재훈
 *  날짜	: 1차 개발 : 2018년 5월 4일 
 *----------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
void *counter(void *arg);
int cnt = 0;

pthread_mutex_t sync_mutex;

int main() {
		pthread_t tid[5]; //쓰레드 배열
		pthread_mutex_init(&sync_mutex, NULL);
		int i;
		for(i = 0; i<5; i++) {
				if(pthread_create(&tid[i], NULL, counter,  NULL) != 0) { //쓰레드 5개 생성
						printf("fail to create thread.\n");
						return 0;
						}
		}
		for(i = 0; i<5; i++) {
				if(pthread_join(tid[i], NULL) != 0) { //쓰레드 5개를 기다림
						printf("fail to join thread.\n");
						return 0;
				}
		}
		return 0;
}

void *counter(void *args) {

		int tmp, j;
		pthread_mutex_lock(&sync_mutex); //상호 배제 락을 걸어줌
		for(j=0; j<100; j++) { //각 쓰레드마가 100번씩 count (총 500번의 count)
				tmp = cnt; //cnt를 tmp에 저장 후
				usleep(1); //경쟁 조건이 일어날 수 있도록 슬립을 걸어줬음에도 불구하고 락 때문에 걸리지 않는다
				tmp++; //tmp값 증가
				cnt = tmp; //증가시킨 tmp 값을 cnt에 저장
				printf("%d\n", cnt);
		}
		pthread_mutex_unlock(&sync_mutex); //상호 배제 락을 풀어줌
		pthread_exit((void*)0); //쓰레드 종료
}				
