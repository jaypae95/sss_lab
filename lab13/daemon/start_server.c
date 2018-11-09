/* ----------------------------------------------------------------------------------------------------
*  ����: start_server.c
*  ���	: ���� ���� ����
*  ������: 201520934 ������
*  ��¥	: 1�� ���� : 2018�� 6�� 8��
*----------------------------------------------------------------------------------------------------*/
#include "fake_apue.h"

int main() {
		int s_sock, len, rc, status, nsockopt;
		int bytes_rec = 0; 
 		struct sockaddr_in s_addr; //���� �ּ�
		struct sockaddr_in c_addr; // Ŭ���̾�Ʈ �ּ�
 		char buf[512]; 
 		int backlog = 10; 
 		memset(&s_addr, 0, sizeof(struct sockaddr_in)); 
 		memset(&c_addr, 0, sizeof(struct sockaddr_in));

		len = sizeof(c_addr);

		daemonize("daemon"); //����ȭ

		//create socket
 		s_sock = socket(AF_INET, SOCK_STREAM, 0); 
		if(s_sock == -1) { 
				printf("SOCKET ERROR\n"); 
 				exit(0); 
	 	} 
		bzero(&s_addr, sizeof(s_addr));

		//prepare the sockkaddr_in structure
		s_addr.sin_family = AF_INET; //ipv4 ���ͳ� ��������
 		s_addr.sin_addr.s_addr = htonl(INADDR_ANY); //������ ip�ּҸ� �ڵ����� ã�Ƽ� ��������
 		s_addr.sin_port = htons(60005); //��Ʈ��ȣ 60004

		//���� ��Ʈ�� ���� �� �� �ֵ��� ����
		nsockopt = 1;
		if(setsockopt(s_sock, SOL_SOCKET, SO_REUSEADDR, &nsockopt, sizeof(nsockopt))==-1) {
				printf("SETSOCKOPT ERROR\n");
				close(s_sock);
				exit(0);
		}

		//bind(������ ������ ���� �������� ���)
 		rc = bind(s_sock, (struct sockaddr *)&s_addr, sizeof(s_addr)); 
 		if (rc == -1) { 
				printf("BIND ERROR\n"); 
 				close(s_sock); 
 				exit(0); 
 		} 

		//listen(���� ������ ���� Ŭ���̾�Ʈ�� ���� ��û�� Ȯ���ϵ��� ����)
 		rc = listen(s_sock, backlog); 
 		if (rc == -1) { 
				printf("LISTEN ERROR\n"); 
 				close(s_sock); 
 				exit(0); 
 		} 

		//accept connection from an incoming client
		//Ŭ���̾�Ʈ ���� ��û ���
		//Ŭ���̾�Ʈ�� ����� ���� �� socket����
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
