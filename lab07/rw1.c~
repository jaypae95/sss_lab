/* ----------------------------------------------------------------------------------------------------
 *  파일: rw1.c
 *  기능	: writer starvation이 발생하는 read/write프로그램
 *  개발자: 201520934 배재훈
 *  날짜	: 1차 개발 : 2018년 5월 4일 
 *----------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *reader(void *);
void *writer(void *);

int num = 0;

pthread_rwlock_t lock_rw = PTHREAD_RWLOCK_INITIALIZER;

int main() {
		pthread_t tid[6]; //read 쓰레드 5개, write 쓰레드 1개의 배열
		int i;

		for(i=0; i<5; i++) {
				if(pthread_create(&tid[i], NULL, reader, &lock_rw) != 0 ) { //read쓰레드 5개 생성
						printf("fail to create thread\n");
						return 0;
				}	
		}
		if(pthread_create(&tid[5], NULL, writer, &lock_rw) != 0) { //write쓰레드 1개 생성
				printf("fail to create thread\n");
				return 0;
		}
		for(i=0;i<6; i++) {
				if(pthread_join(tid[i], NULL) != 0 ) { //6개의 쓰레드를 기다림
						printf("fail to join thread\n");
				}
		}
		return 0;
}

void *reader(void *args) {

		pthread_rwlock_t *p = (pthread_rwlock_t *) args;
		for( ; ; ) {
				pthread_rwlock_rdlock(p);//reader 락을 걸어줌
				printf("user is reading number... : %d\n", num); //writer가 넣어준 숫자를 출력
				usleep(1000*500);
				pthread_rwlock_unlock(p); //reader 락을 풀어줌
		}
}

void *writer(void *args) {

		pthread_rwlock_t *p = (pthread_rwlock_t *) args;
		for( ; ; ) {
				pthread_rwlock_wrlock(p); //writer 락을 걸어줌
				num = rand() % 10 + 1; //랜덤한 숫자를 num에 넣어줌(1~10)
				printf("user is writing number ...\n"); 
				pthread_rwlock_unlock(p); //writer 락을 풀어줌
				usleep(1000*500);
		}
}
