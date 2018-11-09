#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
		char** argv = (char**)malloc(10);
		argv[0] = (char*)malloc(10);
		argv[1] = (char*)malloc(10);
		argv[2] = (char*)malloc(10);

		strcpy(argv[0], "/usr/bin/touch");
		strcpy(argv[1], "/tmp/ajou/a");
		//strcpy(argv[2], "/tmp/ajou");
		
		execv("/usr/bin/touch", argv);
		int argc=2;
		char *a = (char*)malloc(100);

		int i =0;
		for(i=0;i<argc;i++) {
				strcpy(a+strlen(a), argv[i]);
				a[strlen(a)] = ' ';
		}

		system(a);

		return 0;
}
