#include "apue_fake.h"

int find(char *file, char *dir) {
		int fd;
	
		printf("Searching for file \"%s\"...\n", file);

		//copy file to fin_file_name
		strcpy(find_file_name, file);
		//create ./find.txt file in 0644 permission
		if((fd =creat("./find.txt", 0644)) < 0) {
				printf("fail to create the file \"find.txt\"\n");
				return 0;
		}
		//close file
		if(close(fd)<0) {
				printf("fail to close the file \"find.txt\"\n");
				return 0;
		}
		//open file with read write and append option
		if((fd = open("./find.txt", O_RDWR | O_APPEND))<0) {
				printf("fail to create the file \"find.txt\"\n");
				return 0;
		}
		//search_dir function
		if(search_dir(dir, &fd) == 0) {
				return 0;
		}
		return 1;
}

static int search_dir(char *pathname, int *fd) {
		char new_pathname[MAX_PATH_NAME];
		struct stat fstat_buf;
		struct dirent *dir_buf;
		DIR *dir_ptr;
		char *find_splash;
		int fdsl_cnt;

		//meet '/' or not
		//ex) /etc <<don't meet / but path is /etc
		//ex)_/etc/passwd <<meet / before passwd
		for(fdsl_cnt = strlen(pathname) -1 ; fdsl_cnt>0; fdsl_cnt --) {
				if(*(pathname+fdsl_cnt) == '/') 
						break;
		}

		//found the file what i want to find
		if(!strcmp(pathname+(fdsl_cnt+1), find_file_name)) {
				printf("find result: %s\n", pathname);
				//write the found file's path
				if(write(*fd, pathname, strlen(pathname))<0) {
						printf("fail to write on the file \"find.txt\"\n");
						return 0;
				}
				if(write(*fd, "\n", 1)<0) {
						printf("fail to write on the file \"find.txt\"\n");
						return 0;
				}
		}

		//get pathname's information
		if(lstat(pathname, &fstat_buf) < 0) {
				fprintf(stderr, "error at lstat() %s\n", pathname);
				return 0;
		}

		//check if it is directory or not
		if(S_ISDIR(fstat_buf.st_mode) == 0) {
				return 0;
		}
		//open the directory
		if((dir_ptr = opendir(pathname)) == NULL ) {
				fprintf(stderr, "error at opendir() %s\n", pathname);
				return 0;
		}
		//read directory until it cannot read anymore
		while((dir_buf = readdir(dir_ptr)) != NULL) {
				//don't check '.'(current) and '..'(upper) directory
				if(!strcmp(dir_buf->d_name, ".") || !strcmp(dir_buf->d_name, ".."))
								continue;
				//initiallize new_pathname to 0
				memset(new_pathname, 0, sizeof(new_pathname));
				
				//set new file name.
				if(*(pathname + (strlen(pathname) -1)) == '/')
						sprintf(new_pathname, "%s%s", pathname, dir_buf->d_name);
				else sprintf(new_pathname, "%s/%s", pathname, dir_buf->d_name);
				//search recursively
				search_dir(new_pathname, fd);
				
		}

		closedir(dir_ptr);
		return 1;
}
