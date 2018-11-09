#include <stdio.h>
#include <unistd.h>

int main() {
		printf("your real user id is %d\n", getuid());
		printf("your effective user id is %d\n", geteuid());

		if(setuid(500) != 0 )
				perror("setuid() error");
		if(setuid(500) != 0 )
				perror ("seteuid() error");

		printf("##########################\n");
		printf("real uid : %d\n", getuid());
		printf("effective uid : %d\n", geteuid());

		return 0;
}
