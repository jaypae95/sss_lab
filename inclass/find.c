#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include <stdio.h>
#include <string.h>

#define MAX_PATH_NAME 4096
#define MAX_FILE_NAME 256

static void search_dir(char *);
static char find_file_name[MAX_FILE_NAME];

//exmaple of finding "passwd" file in "etc" directory
//  ./find passwd /etc
int main(int argc, char *argv[]) {
		if(argc != 3) {
				printf("Usage : a.out [file name] [start directory] \n");
				return;
		}
		strcpy(find_file_name, argv[1]); //passwd
		search_dir(argv[2]); // /etc

		return;
}

static void search_dir(char *pathname) { // /etc
		char new_pathname[MAX_PATH_NAME];
		struct stat fstat_buf;
		struct dirent *dir_buf;
		DIR *dir_ptr;
		char *find_splash;
		int fdsl_cnt;

		for(fdsl_cnt = strlen(pathname) -1 ; fdsl_cnt>0; fdsl_cnt --) {
				if(*(pathname+fdsl_cnt) == '/') 
						break;
		}

		if(!strcmp(pathname+(fdsl_cnt+1), find_file_name)) //
				printf("find result : %s \n", pathname);
		if(lstat(pathname, &fstat_buf) < 0) {
				fprintf(stderr, "error at lstat() %s\n", pathname);
				return;
		}

		if(S_ISDIR(fstat_buf.st_mode) == 0) {
				return;
		}
		if((dir_ptr = opendir(pathname)) == NULL ) {
				fprintf(stderr, "error at opendir() %s\n", pathname);
				return;
		}

		while((dir_buf = readdir(dir_ptr)) != NULL) {
				if(!strcmp(dir_buf->d_name, ".") || !strcmp(dir_buf->d_name, ".."))
								continue;
				memset(new_pathname, 0, sizeof(new_pathname));
				if(*(pathname + (strlen(pathname) -1)) == '/')
						sprintf(new_pathname, "%s%s", pathname, dir_buf->d_name);
				else sprintf(new_pathname, "%s/%s", pathname, dir_buf->d_name);
				
				search_dir(new_pathname);
		}

		closedir(dir_ptr);
}
