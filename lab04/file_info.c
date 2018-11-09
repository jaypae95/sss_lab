#include "apue_fake.h"

int fileInfo () {
		int i;
		struct stat buf;

		FILE *fp1;
		FILE *fp2;
		int fd;
		char *file = (char*)malloc(sizeof(char)*512);

		//open find.txt with reading mode
		if((fp1 = fopen("./find.txt", "r")) == NULL) {
				printf("fail  to open the file \"./find.txt\"\n");
				return 0;
		}
		//create file_info.txt
		if((fd = creat("./file_info.txt", 0644))<0) {
				printf("fail to create the file \"./file_info\"\n");
				return 0;
		}
		//close file_info.txt
		if(close(fd) < 0) {
				printf("fail to close the file \"./file_info\"\n");
				return 0;
		}
		//open file_info.txt with writing mode
		if((fp2 = fopen("./file_info.txt", "w")) == NULL) {
				printf("fail to open the file \"./file_info\"\n");
				return 0;
		}

		//get file(path) from file by line
		while((fgets(file, 128, fp1)!=NULL)) {
				//change '\n' to '\0'
				file[strlen(file)-1] = '\0';
				//get file's information
				if(stat(file, &buf) < 0 ) {
						perror("stat error");
						continue;
				}
				printf("%s : ", file);
				
				fprintf(fp2, "%s : ", file);
				/*file_type*/
				check_file_type(&buf, &fp2);
				/*file permission*/
				check_file_permission(&buf, &fp2);
				/*i-node number*/
				printf("i-node number : %ld \n", buf.st_ino);
				fprintf(fp2, "i-node number : %ld \n", buf.st_ino);
				/*hard link number */
				printf("Number of hard links : %d \n", buf.st_nlink);
				fprintf(fp2, "Number of hard link : %d \n", buf.st_nlink);
				/*owner id */
				printf("User ID : %d \n", buf.st_uid);
				fprintf(fp2, "User ID : %d \n", buf.st_uid);
				/*group id*/
				printf("Group ID : %d \n", buf.st_gid);
				fprintf(fp2, "Group ID : %d \n", buf.st_gid);
				/*file size*/
				printf("Total Size : %ld \n", buf.st_size);
				fprintf(fp2, "Total Size : %ld \n", buf.st_size);
				/*total size of file block*/
				printf("Block Size : %ld \n", buf.st_blksize);
				fprintf(fp2, "Block Size : %ld \n", buf.st_blksize);
				/*block number*/
				printf("Number of blocks : %ld \n\n", buf.st_blocks);
				fprintf(fp2, "Number of blocks : %ld \n\n", buf.st_blocks);
		}
		//close find.txt
		if(fclose(fp1) != 0) {
				printf("fail to close the file \"./find.txt\"\n");
				return 0;
		}
		//close file_info.txt
		if(fclose(fp2) != 0) {
				printf("fail to close the file \"./file_info\"\n");
				return 0;
		}
		return 0;

}

/*file type*/
static void check_file_type(struct stat *buf,FILE **fp) {
		char *ptr;
		printf("File Type : ");

		//regular file
		if(S_ISREG(buf->st_mode))
				ptr = "regular";
		//directory
		else if (S_ISDIR(buf->st_mode))
				ptr = "directorty";
		//character special file
		else if (S_ISCHR(buf->st_mode))
				ptr = "character special";
		//block special file
		else if (S_ISBLK(buf->st_mode))
				ptr = "block special";
		//fifo
		else if (S_ISFIFO(buf->st_mode))
				ptr = "fifo";
		//socket
		else if (S_ISSOCK(buf->st_mode))
				ptr = "socket";
		//unknown mode
		else ptr = "** unknown mode **";

		printf("%s\n", ptr);
		fprintf(*fp, "%s\n", ptr);
}

/*file permission*/
static void check_file_permission(struct stat *buf, FILE **fp) {
		//initiallize
		char per_buf[10] = "---------\0";
 		//read permission for user
		if((buf->st_mode & S_IRUSR))
				per_buf[0] = 'r';
		//write permission for user
		if((buf->st_mode & S_IWUSR))
				per_buf[1] = 'w';
		//execute permission for user
		if((buf->st_mode & S_IXUSR))
				per_buf[2] = 'x';

		//read/write/execute permission for group
		if((buf->st_mode & S_IRGRP))
				per_buf[3] = 'r';
		if((buf->st_mode & S_IWGRP))
				per_buf[4] = 'w';
		if((buf->st_mode & S_IXGRP))
				per_buf[5] = 'x';

		//read/write/execute permission for other
		if((buf->st_mode & S_IROTH))
				per_buf[6] = 'r';
		if((buf->st_mode & S_IWOTH))
				per_buf[7] = 'w';
		if((buf->st_mode & S_IXOTH))
				per_buf[8] = 'x';

		//Set-UID bit
		if((buf->st_mode & S_ISUID))
				per_buf[2] = 'S';
		//Set-GID bit
		if((buf->st_mode & S_ISGID))
				per_buf[5] = 's';
		//sticky bit
		if((buf->st_mode & S_ISVTX))
				per_buf[8] = 't';
		printf("File Permission : %s\n", per_buf);
		fprintf(*fp, "File Permission : %s\n", per_buf);
}
