#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main () {
		int fd1, fd2;
		int count;
		void *map1, *map2;

		fd1 = open("./sample1.txt", O_RDONLY);
		fd2 = open("./sample2.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);

		count = lseek(fd1, 0, SEEK_END);

		if (lseek(fd2, count -1, SEEK_SET ) == -1) {
				printf("lseek err\n");
				return 0;
		}
		if (write(fd2, " ", 1 ) != 1) {
				printf("write err\n");
				return 0;
		}
		if((map1 = mmap(0, count, PROT_READ, MAP_SHARED, fd1, 0)) < (void*)0) {
				printf("mmap err\n");
				return 0;
		}
		if((map2 = mmap(0, count, PROT_WRITE, MAP_SHARED, fd2, 0))<(void*)0) {
				printf("mmap err\n");
				return 0;
		}

		memcpy((char*)map2, (char*)map1, count);

		munmap(map1, count);
		munmap(map2, count);

		close(fd1);
		close(fd2);

}
