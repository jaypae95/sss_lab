/* ----------------------------------------------------------------------------------------------------
 *  파일: dining_ph1.c
 *  기능	: 동기화가 되지 않은 dining philosopher 프로그램. 젓가락을 2개 들면 식사
 *  개발자: 201520934 배재훈
 *  날짜	: 1차 개발 : 2018년 5월 4일 
 *----------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int chopstick[5] = { 1, 1, 1, 1, 1}; //5개의 chopstick 초기화
void * philosopher (void *);
int main() {
		int i;
		pthread_t tid[5]; //5개의 철학자 쓰레드 배열

		for(i = 0; i < 5; i++) {
				if(pthread_create(&tid[i], NULL, philosopher, (void *) i) != 0) {//5개의 철학자 쓰레드 생성
						printf("fail to create thread\n");
						return 0;
				}
		}
		for(i = 0; i<5; i++) {
				if(pthread_join(tid[i], NULL) != 0) { //5개의 철학자 쓰레드를 기다림
						printf("fail to join thread\n");
						return 0;
				}
		}
}

void * philosopher (void * args) {
		int k;
		int p_right = 0; //철학자의 오른손
		int p_left = 0; //철학자의 왼손
		int right = ((int)args + 4) % 5; //오른쪽 젓가락을 나타내기 위함
		int left = ((int)args + 1) % 5; //왼쪽 젓가락을 나타내기 위함

		for(k = 1 ; ;k++ ) {
				if(chopstick[left] == 1) { //왼쪽 젓가락이 식탁에 놓여져 있으면
						chopstick[left] = 0; //젓가락을 든다.
						p_left = 1; //철학자의 왼손에 젓가락이 있음
				}
				//usleep(1);
				if(chopstick[right] == 1) { //오른쪽 젓가락이 식탁에 놓여져 있으면
						chopstick[right] = 0; //젓가락을 든다.
						p_right = 1; //철학자의 오른손에 젓가락이 있음
				}
				if(p_left == 1  && p_right == 1) { //만약 철학자의 왼손과 오른손에 젓가락이 있으면
						//0.01초 동안 식사를 한다
						printf("#%d philosopher is EATING..\t     <<%d>>\n", (int)args+1, k);
						usleep(1000*10);
						p_left = 0; //식사 완료 후 젓가락을 내려 놓는다.
						p_right = 0; // "
						chopstick[left] = 1;  // "
						chopstick[right] = 1; // "
						usleep(1);
				}
				else {		//양손에 젓가락이 없거나 하나 있는 경우 0.01초 동안 생각한다.
						printf("#%d philosopher is thinking..(r:%d l:%d)<<%d>>\n", (int)args+1, p_right, p_left, k);
						usleep(1000*10); 
				}
		}					
}

