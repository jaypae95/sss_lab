/* ----------------------------------------------------------------------------------------------------
 *  파일: pt_counter_word.c
 *  기능 : 장문의 각 단어의 개수를 세고, 단어의 종류를 파일에 저장 (8개의 스레드 사용)
 *  개발자: 201520934 배재훈 
 *  날짜	: 1차 개발 : 2018년 5월 11일 
 *----------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>

int fd;
FILE *fp;
char *arr;
void parse();
void *count(void *);
int num=0, wasspace=0, totalnum = 0, off = 0;
int word[1024] = {0};
pthread_mutex_t sync_mutex;
pthread_barrier_t b;

int main() {
		struct timeval start, end; //시간측정
		long long startusec, endusec; //"
		double elapsed; //"
		gettimeofday(&start, NULL); //"

		pthread_t tid[8]; //쓰레드배열 생성
		pthread_mutex_init(&sync_mutex, NULL); //뮤텍스락 초기화
		arr = (char*)malloc(sizeof(char)*20);
		int i;
		if((fd = open("./long.txt", O_RDONLY))<0) { //장문파일 읽기모드로 열기
				printf("fail to open \"./long.txt\"\n");
				return 0;
		}
		fp = fopen("./tmp.txt", "w+");  //tmp.txt 파일 쓰기모드로 생성 후 열기
		parse(); //파일의 단어를 파싱해서 tmp파일에 저장
		fclose(fp); //파일 닫아줌
		off /=  8; //8개로 나눠줌
		totalnum /= 8; //8개로 나눠줌
		fp = fopen("./word.txt", "w+");//word.txt 파일 쓰기모드로 생성 후 열기

		pthread_barrier_init(&b, NULL, 9); //배리어 생성
		for(i=0; i<8; i++) {
				if(pthread_create(&tid[i], NULL, count, (void*)i) != 0) { //스레드를 생성 후 count함수 실행
						printf("fail to create thread\n");
						return 0;
				}
		}
		pthread_barrier_wait(&b); //모든 쓰레드를 기다려줌

		char *buf = (char*)malloc(sizeof(char)*20);
		fseek(fp, 0, SEEK_SET); //파일의 위치를 처음으로 설정
		for(i = 0; i<num; i++) { //각 단어의 개수 출력
				fgets(buf, 20, fp);
				buf[strlen(buf)-1] = '\0';
				printf("%s : ", buf);
				printf("%d\n", word[i]);
		}
		fclose(fp); //파일 닫아줌

		gettimeofday(&end, NULL); //시간측정
		startusec = start.tv_sec * 1000000 + start.tv_usec;
		endusec = end.tv_sec * 1000000 + end.tv_usec;
		elapsed = (double)(endusec - startusec) / 1000000.0;
		printf("time : %.4fseconds\n", elapsed ); //시간출력
} 

void *count(void *i) {
		FILE *fp2;
		char alph;
		char *buf = (char*)malloc(sizeof(char)*20);
		char *infile = (char*)malloc(sizeof(char)*20);
		int till, fpoff;
		int pos=-1, isinfile = 0, readonemore=0, first=1;

		fpoff = off*(int)i; //오프셋 * 쓰레드 번호 
		fp2 = fopen("./tmp.txt", "r"); //tmp.txt 파일을 읽기 모드로 열어줌
		fseek(fp2, fpoff, SEEK_SET);
		if(((int)i) != 0) {
	 		while(1) { //병렬 처리를 위해 쓰레드마다 오프셋 변경
					fread(&alph, sizeof(char), 1, fp2); 
					if(alph == '\n'){
							break;
					}
					first=0;
					fseek(fp2, -2, SEEK_CUR);
			}
		}
		int j;
		till = totalnum; //8개로 나눈 만큼
		for(j = 0; j<till+7; j++) { //포문 돌림 + 나머지
				if(fgets(buf, 20, fp2) == 0) { //tmp파일에서 한 줄씩 읽어옴
						break;//파일 끝에 도달하면 while문 종료
				}
				buf[strlen(buf)-1] = '\0'; //줄바꿈문자를 널문자로 바꿔줌
				pthread_mutex_lock(&sync_mutex); //락 걸어줌
				fseek(fp, 0, SEEK_SET); //파일의 위치를 처음으로 설정
				while(fgets(infile, 20, fp) != 0) { //word.txt에서 한 줄씩 읽어옴
						pos++; //각 단어의 개수를 올리기위한 위치 index
						infile[strlen(infile)-1] = '\0'; //줄바꿈문자를 널문자로 바꿔줌
						if(!strcmp(infile, buf)) { //읽어온 두 단어 비교
								isinfile = 1; //파일에 존재
								memset(infile, 0, strlen(infile)); //배열 초기화
								break;
						}
						memset(infile, 0, strlen(infile));//배열 초기화
				}
				if(isinfile==0) {  //파일에 이미 존재하지 않으면
						fseek(fp, 0, SEEK_END); //파일 맨 끝으로 이동
						fprintf(fp, "%s\n", buf); //읽어온 스트링 파일에 출력
						word[num]++; //새로운 단어이므로 0에서 1로 증가
						num++; //num index값 증가
						pthread_mutex_unlock(&sync_mutex); //락을 풀어줌
						pos = -1; //pos 초기화
						memset(buf, 0, strlen(buf));//배열 초기화
				}
				else {
						word[pos]++;  //단어의 개수 증가
						pos = -1; //pos 초기화
						pthread_mutex_unlock(&sync_mutex); //락을 풀어줌
						memset(buf, 0, strlen(buf));//배열 초기화
						isinfile = 0;  //isinfile 초기화
				}
		}
		pthread_barrier_wait(&b); //모든쓰레드를 기다림
}

void parse() {
		char* infile = (char*)malloc(sizeof(char)*20);
		int res;
		char alph;
		int index=0;
		while(1) {
				if((res = read(fd, &alph, 1)==0)) { //한 글자씩 읽어옴
						break; 
				}
				if(res < 0) {
						return;
				}
				if(alph == ' ' || alph == '\n') { //줄바꿈이나 space를 만날 경우
						if(wasspace == 1) { //이전 것도 space였거나 줄바꿈이였을 경우
								continue;  //pass 
						}
						fseek(fp, 0, SEEK_SET); //파일의 위치를 맨 처음으로 이동
								arr[index] = '\0'; //배열 마지막에 null문자를 넣어주고
								fseek(fp, 0, SEEK_END); //파일 맨 뒤로 이동
								fprintf(fp, "%s\n", arr); //파일에 배열 출력
								totalnum++;  //단어의 총 개수 증가
								index=0;
								wasspace = 1; //공백이였음을 알림
								memset(arr, 0, strlen(arr));//배열 초기화				
				}
				else if(isalpha((int)alph) || alph == '-' || alph == '\'') {
								//알파벳이거나 ‘-‘이거나 작은따음표일 때
						if(isupper((int)alph)) { //대문자는 소문자로 바꿔줌
								alph += 32;
						}
								arr[index++] = alph; //글자를 배열에 넣어줌
								wasspace = 0; //wasspace초기화
				}
		}
		fseek(fp, 0, SEEK_END); //오프셋을 끝으로 이동후
		off = ftell(fp); //파일 위치를 알려줌(오프셋 총 수를 알고자함)
	return;
}
