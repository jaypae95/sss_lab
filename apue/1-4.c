#include "apue.h"

#define BUFFSIZE 4096

int main () {
		int n;
		char buf[BUFFSIZE];

		while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) >0) {
				if(write(STDOUT_FILENO, buf, n) != n) {
						printf("write error");
						return 0;
				}

		}

		if(n<0) {
				printf("read error");
		}

		exit(0);

}
