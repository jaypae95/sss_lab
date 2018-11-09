#include "apue.h"
#include <errno.h>
#include <fcntl.h>

void set_fl(int, int);
void clr_fl(int, int);

char buf[500000];

int main() {
		int ntowrite, nwrite;
		char *ptr;

		ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
		fprintf(stderr, "read %d bytes\n", ntowrite);

		set_fl(STDOUT_FILENO, O_NONBLOCK);

		ptr = buf;
		while (ntowrite > 0) {
				errno = 0;
				nwrite = write(STDOUT_FILENO, ptr, ntowrite);
				fprintf(stderr, "nwrite = %d, errno = %d, ntowrite = %d\n", nwrite, errno, ntowrite);

				if(nwrite > 0) {
						ptr +=nwrite;
						ntowrite -= nwrite;
				}
		}

		clr_fl(STDOUT_FILENO, O_NONBLOCK);

		exit(0);
}

void set_fl(int fd, int flags) {
		int val;

		if((val = fcntl(fd, F_GETFL, 0)) < 0) {
				printf("fcntl F_GETFL err\n");
				exit(0);
		}
		val |= flags;

		if (fcntl(fd, F_SETFL, val) < 0) {
				printf("fcntl F_SETFL err\n");
				exit(0);
		}
}

void clr_fl(int fd, int flags) {
		int val;

		if((val - fcntl(fd, F_GETFL, 0)) < 0) {
				printf("fcntl F_GETFL err\n");
				exit(0);
		}

		val &= ~flags;

		if(fcntl(fd, F_SETFL, val) < 0) {
				printf("fcntl F_SETFL, err\n");
				exit(0);
		}

}
