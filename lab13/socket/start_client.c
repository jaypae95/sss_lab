#include "fake_apue.h"

int main() {
		int rc, len, status; 
    	struct sockaddr_in c_addr; 
    	char buf[512]; 

		memset(&c_addr, 0, sizeof(struct sockaddr_in)); 
 
	    c_sock = socket(AF_INET, SOCK_STREAM, 0); 
	    if(c_sock == -1) { 
				printf("SOCKET ERROR\n"); 
				exit(0); 
    	} 

		c_addr.sin_family = AF_INET; 
		c_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		c_addr.sin_port = htons(60004);

 	   	len = sizeof(c_addr);

	   	rc = connect(c_sock, (struct sockaddr *)&c_addr, len); 
	   	if(rc == -1) { 
				printf("CONNECT ERROR\n"); 
				close(c_sock); 
				exit(0); 
		} 

		printf("Connected!!\n");

		_client();

}
