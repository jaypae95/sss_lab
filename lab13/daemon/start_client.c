/* ----------------------------------------------------------------------------------------------------
*  ����: start_client.c
*  ���	: Ŭ���̾�Ʈ ����
*  ������: 201520934 ������
*  ��¥	: 1�� ���� : 2018�� 6�� 8��
*----------------------------------------------------------------------------------------------------*/
#include "fake_apue.h"

int main() {
		int rc, len, status; 
    	struct sockaddr_in c_addr; 
    	char buf[512]; 

		memset(&c_addr, 0, sizeof(struct sockaddr_in)); 

		//create socket
	    c_sock = socket(AF_INET, SOCK_STREAM, 0); 
	    if(c_sock == -1) { 
				printf("SOCKET ERROR\n"); 
				exit(0); 
    	} 

		//prepare the sockkaddr_in structure
		c_addr.sin_family = AF_INET; //ipv4 ���ͳ� ��������
		c_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //ip 127.0.0.1
		c_addr.sin_port = htons(60005); //��Ʈ��ȣ 60004


 	   	len = sizeof(c_addr);

		//connect to remote server
	   	rc = connect(c_sock, (struct sockaddr *)&c_addr, len); 
	   	if(rc == -1) { 
				printf("CONNECT ERROR\n"); 
				close(c_sock); 
				exit(0); 
		} 

		printf("Connected!!\n");

		_client();

}
