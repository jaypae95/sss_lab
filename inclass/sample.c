#include "apue.h"

static void check_file_type(struct stat *);
static void check_file_permission(struct stat *);

int main (int argc, char *argv[]) {
		int i;
		struct stat buf;

		for(i=1; i<argc; i++) {
				printf("%s: ", argv[i]);

				if(stat(argv[i], &buf) < 0 ) {
						perror("stat errror");
						continue;
				}
				/*file type*/
				check_file_type(&buf);
				/*file permission*/
				check_file_permission(&buf);
				/*i-node number*/
				printf("i-node number : %ld \n", buf.st_ino);
				/*hard link number */
				printf("Number of hard links : %d \n", buf.st_nlink);
				/*owner id */
				printf("User ID : %d \n", buf.st_uid);
				/*group id*/
				printf("Group ID : %d \n", buf.st_gid);
				/*file size*/
				printf("Total Size : %ld \n", buf.st_size);
				/*total size of file block*/
				printf("Block Size : %ld \n", buf.st_blksize);
				/*block number*/
				printf("Number of blocks : %ld \n", buf.st_blocks);
		}
		exit(0);
}

/*file type*/
static void check_file_type(struct stat *buf) {
		char *ptr;
		printf("File Type : ");

		if(S_ISREG(buf->st_mode))
				ptr = "regular";
		else if (S_ISDIR(buf->st_mode))
				ptr = "directorty";
		else if (S_ISCHR(buf->st_mode))
				ptr = "character special";
		else if (S_ISBLK(buf->st_mode))
				ptr = "block special";
		else if (S_ISFIFO(buf->st_mode))
				ptr = "fifo";
		else if (S_ISSOCK(buf->st_mode))
				ptr = "socket";
		else ptr = "** unknown mode **";

		printf("%s\n", ptr);
}

/*file permission*/
static void check_file_permission(struct stat *buf) {
		char per_buf[10] = "----------";

		if((buf->st_mode & S_IRUSR))
				per_buf[0] = 'r';
		if((buf->st_mode & S_IWUSR))
				per_buf[1] = 'w';
		if((buf->st_mode & S_IXUSR))
				per_buf[2] = 'x';

		if((buf->st_mode & S_IRGRP))
				per_buf[3] = 'r';
		if((buf->st_mode & S_IWGRP))
				per_buf[4] = 'w';
		if((buf->st_mode & S_IXGRP))
				per_buf[5] = 'x';

		if((buf->st_mode & S_IROTH))
				per_buf[6] = 'r';
		if((buf->st_mode & S_IWOTH))
				per_buf[7] = 'w';
		if((buf->st_mode & S_IXOTH))
				per_buf[8] = 'x';

		if((buf->st_mode & S_ISUID))
				per_buf[2] = 'S';
		if((buf->st_mode & S_ISGID))
				per_buf[5] = 's';
		if((buf->st_mode & S_ISVTX))
				per_buf[8] = 't';
		printf("File Permission : %s\n", per_buf);
}
