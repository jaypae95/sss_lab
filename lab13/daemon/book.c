/* ----------------------------------------------------------------------------------------------------
*  파일: book.c
*  기능	: 도서 대여/반납 관리 서버
*  개발자: 201520934 배재훈
*  날짜	: 1차 개발 : 2018년 6월 8일
*----------------------------------------------------------------------------------------------------*/
#include "fake_apue.h"

int book_rental(char *book_name, char* id) {


		char *book_info = (char *)malloc(256);
		int exist = 0;

		fseek(fp2, 0, SEEK_SET);
		memset(book_info, 0, 256);
		while(fgets(book_info, 256, fp2) > 0) { //한 줄씩 읽어옴
				book_info[strlen(book_info)-10] = '\0'; //, 0001, V\n 에서 맨앞에 ,자리에 null
				if(!strcmp(book_info, book_name)) { //도서 이름을 비교해서 일치하면
						exist =1; //존재
						break;
				}
		}
		if(exist == 0) { //존재 하지 않으면
				send(s_c_sock, "not exist\0", 30, 0); //일치하지 않는다는 정보 전송
		}
		else {  //존재하면
				char valid = '\0';
				fseek(fp2, -2, SEEK_CUR); //-2만큼 이동 후 (V\n)
				fscanf(fp2, "%c ", &valid); //V 또는 I 를 받아옴
				if(valid == 'I') { //I면 (invalid)
						send(s_c_sock, "cannot rent\0", 30, 0); //대여할 수 없다는 메시지 전송
				}
				else if(valid == 'V') { //V면 (valid)
						fseek(fp2, -2, SEEK_CUR); //다시 -2만큼 이동 후 (2만큼 읽었기 때문에)
						fprintf(fp2, "I"); //V를 I로 바꿈
						fflush(fp2);
						fprintf(fp3, "%s,%s\n", book_name, id); // rent.txt에 대여 정보를 출력
						fflush(fp3);
						send(s_c_sock, "success!\0", 30, 0); //성공 했다는 메시지 전송
				}
		}
		
		free(book_info);
		return 0;

}

int book_return(char *id) {
		char rent_info[100] = {0, };
		char to_return[100] = {0, };
		char * token = NULL;
		char **buf = (char**)malloc(sizeof(char*)*2);
		int exist = 0;
		char temp_info[100];
		FILE *temp = fopen("./temp.txt", "w+"); //임시 파일 오픈
		fseek(fp3, 0, SEEK_SET);
		send(s_c_sock, "===============List===============\0", 128, 0); //클라이언트에 전송
		while(fgets(rent_info, 100, fp3) > 0) { //대여 목록을 한줄 씩 읽어와서
				rent_info[strlen(rent_info)-1] = '\0';
				memset(temp_info, 0, 100);

				strcpy(temp_info, rent_info);

				token = strtok(temp_info, ","); // ','단위로 잘라줌
				int i=0;
				while(token != NULL) {
						buf[i] = (char*)malloc(30);
						memset(buf[i], 0, 30);
						buf[i] = token; //잘라 준 것을 buf[i]에 넣어줌
										//처음엔 도서 명 두번 째는 id
						buf[i][strlen(buf[i])] = '\0';
						i++;
						token=strtok(NULL, ",");
				}
				if(!strcmp(buf[1], id)) { //id가 일치 한다면
						exist = 1; //존재
						send(s_c_sock, buf[0], 128, 0); //도서 명을 전송
						fseek(fp2, 0, SEEK_SET); //rent.txt 오프셋을 처음으로 이동
						while(fgets(to_return, 100, fp2) >0) { //한줄 씩 받아와서
								token = strtok(to_return, ","); //,단위로 잘라서
								if(!strcmp(token, buf[0])) { //첫번째 토큰(도서명)이 일치하면
										fseek(fp2, -2, SEEK_CUR); //I자리에
										fprintf(fp2, "V\n"); //V를 입력
										fflush(fp2);
								}
								memset(to_return, 0, 100);
						}
				}
				else { //일치하지 않다면
						fprintf(temp, "%s\n", rent_info); //임시파일에 정보 출력
				}
		}
		if(exist == 0) {//존재하지 않는다면
				send(s_c_sock, "You have not rent any book\0", 128, 0); //대여한 책이 없다는 메시지 전송
		}
		else {
				send(s_c_sock, "\n\nComplete Returning\0", 128, 0); //완료 메시지 전송
		}
		send(s_c_sock, "done\0", 128, 0); //done 메시지 전송
		system("rm -f ./rent.txt"); //rent.txt파일 삭제
		rename("./temp.txt", "./rent.txt"); //암시파일 이름을 rent.txt로 변경
		
		fclose(fp3); //fp3(기존 rent.xt)를 닫음
		fp3 = fopen("./rent.txt", "a+"); //fp3을 새로운 rent.txt로

		return 0;
}

