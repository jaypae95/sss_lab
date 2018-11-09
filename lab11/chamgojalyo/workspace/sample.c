#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
		int fd = open("./target.txt", O_RDONLY);

		if(fd<0) {
				printf("open error\n");
		}

		close(fd);
		return 0;
}
