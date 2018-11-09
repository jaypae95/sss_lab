/* ----------------------------------------------------------------------------------------------------
*  파일: start_server.c
*  기능	: 데몬 서버 시작
*  개발자: 201520934 배재훈
*  날짜	: 1차 개발 : 2018년 6월 8일
*----------------------------------------------------------------------------------------------------*/
#include "fake_apue.h"

int main() {
		int s_sock, len, rc, status, nsockopt;
		int bytes_rec = 0; 
 		struct sockaddr_in s_addr; //서버 주소
		struct sockaddr_in c_addr; // 클라이언트 주소
 		char buf[512]; 
 		int backlog = 10; 
 		memset(&s_addr, 0, sizeof(struct sockaddr_in)); 
 		memset(&c_addr, 0, sizeof(struct sockaddr_in));

		len = sizeof(c_addr);

		daemonize("daemon"); //데몬화

		//create socket
 		s_sock = socket(AF_INET, SOCK_STREAM, 0); 
		if(s_sock == -1) { 
				printf("SOCKET ERROR\n"); 
 				exit(0); 
	 	} 
		bzero(&s_addr, sizeof(s_addr));

		//prepare the sockkaddr_in structure
		s_addr.sin_family = AF_INET; //ipv4 인터넷 프로토콜
 		s_addr.sin_addr.s_addr = htonl(INADDR_ANY); //서버의 ip주소를 자동으로 찾아서 대입해줌
 		s_addr.sin_port = htons(60005); //포트번호 60004

		//같은 포트로 접속 할 수 있도록 설정
		nsockopt = 1;
		if(setsockopt(s_sock, SOL_SOCKET, SO_REUSEADDR, &nsockopt, sizeof(nsockopt))==-1) {
				printf("SETSOCKOPT ERROR\n");
				close(s_sock);
				exit(0);
		}

		//bind(생성한 소켓을 서버 소켓으로 등록)
 		rc = bind(s_sock, (struct sockaddr *)&s_addr, sizeof(s_addr)); 
 		if (rc == -1) { 
				printf("BIND ERROR\n"); 
 				close(s_sock); 
 				exit(0); 
 		} 

		//listen(서버 소켓을 통해 클라이언트의 접속 요청을 확인하도록 설정)
 		rc = listen(s_sock, backlog); 
 		if (rc == -1) { 
				printf("LISTEN ERROR\n"); 
 				close(s_sock); 
 				exit(0); 
 		} 

		//accept connection from an incoming client
		//클라이언트 접속 요청 대기
		//클라이언트와 통신을 위해 새 socket생성
		printf("Waiting Connection...\n");
 		s_c_sock = accept(s_sock, (struct sockaddr*)&c_addr, &len); 
 		if (s_c_sock == -1) { 
				printf("ACCEPT ERROR\n"); 
 				close(s_sock); 
 				close(s_c_sock); 
 				exit(0); 
		} 
		printf("Connected!\n");
		_server();
}
