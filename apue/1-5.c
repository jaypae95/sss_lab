#include "apue.h"

int main() {
		int c;
		while(( c = getc(stdin)) != EOF)
				if (putc(c, stdout) == EOF) {
						printf("err\n");
						return 0;
				}

		if(ferror(stdin)) {
				printf("input error");
				return 0;
		}

		exit(0);
}
