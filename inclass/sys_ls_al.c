#include <unistd.h>
#include <stdio.h>

int main (int argc, char ** argv) {
		int i = 0;
		int val;
		val = system("ls -al");
		printf("val : %d\n", val);
}
