#include "apue_fake.h"

void ch(int mode, char* file) {

		int uid = 1001; //set uid
		int gid = 1002; //set gid
		
		printf("<<Before changing mode and ownership>>\n");
		//show mode and ownership before change
		showfile_info(file);

		chmod(file, mode);
		chown(file, uid, gid);
		
		printf("<<After changing mode and ownership>>\n");
		//show mode and ownership after change
		showfile_info(file);

		return;
}

void showfile_info(char *file) {
		struct stat buf;

		if(stat(file, &buf) < 0) {
				perror("stat error");
				return;
		}
		char per[10] = "---------\0";
		
		//read/write/execute permission for user
		if((buf.st_mode & S_IRUSR))
				per[0] = 'r';
		if((buf.st_mode & S_IWUSR))
				per[1] = 'w';
		if((buf.st_mode & S_IXUSR))
				per[2] = 'x';
		
		//read/write/execute permission for group
		if((buf.st_mode & S_IRGRP))
				per[3] = 'r';
		if((buf.st_mode & S_IWGRP))
				per[4] = 'w';
		if((buf.st_mode & S_IXGRP))
				per[5] = 'x';
		
		//read/write/execute permission for other
		if((buf.st_mode & S_IROTH))
				per[6] = 'r';
		if((buf.st_mode & S_IWOTH))
				per[7] = 'w';
		if((buf.st_mode & S_IXOTH))
				per[8] = 'x';
		
		//Set_UID bit
		if((buf.st_mode & S_ISUID))
				per[2] = 'S';
		//Set_GID bit
		if((buf.st_mode & S_ISGID))
				per[5] = 's';
		//sticky bit
		if((buf.st_mode & S_ISVTX))
				per[8] = 't';

		printf("File Permission : %s\n", per);
		printf("User ID : %d\n", buf.st_uid);
		printf("Group ID : %d\n", buf.st_gid);
		printf("\n");
}
