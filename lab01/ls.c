/*--------------------------------------------------------------------------------------------
*	파일:ls.c
*	기능:ls 명령어 구현 (-a: 숨김 파일/디렉토리 까지 보여줌, -l 파일/디렉토리의 정보를 보여줌)
*	개발자: 20520934 배재훈
*	날짜: 1차 개발: 2018년 3월 9일
---------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int ls(char *argv_opt, char *argv_dir);

int main(int argc, char *argv[]) {
    
	if (argc == 1) {//ls
		ls("empty","./");// ls => ls ./
	}
	else if (argc ==2 ) { //ls + option or directory or file

		if (!strcmp(argv[1], "-a") || !strcmp(argv[1], "-l")) //ls -a, ls -l
			ls(argv[1], "./");
		else ls("empty",argv[1]); //ls directory or file
	}
	else if (argc == 3) { //ls + option + directory or file
		ls(argv[1],argv[2]);
	}
	else printf("ls: cannot access: No such file or directory\n");//err 

	return 0;

}

int ls(char *argv_opt, char *argv_dir) {

	DIR *dir;
	struct dirent *dirnt;
	struct stat st;
	
	memset(&dirnt, '\0', sizeof(dirnt)); //intiallize
	memset(&st, '\0', sizeof(st)); //intiallize

	stat(argv_dir, &st); //to check argv_dir is directory or file
		
	if((dir = opendir(argv_dir)) == NULL) { //if argv_dir is not directory
		if(S_ISREG(st.st_mode) == 1 ) { //not directory but file
			if(!strcmp(argv_opt, "empty") || !strcmp(argv_opt, "-a")) //file with no option or -a
				 printf("%s\n", argv_dir); //just print the file's name
			else if(!strcmp(argv_opt, "-l")) //file with -l
				 execl("/bin/ls","ls","-l",argv_dir, NULL); //show the file's information
			return 1;
		}
		else { //not directory nor file.
			printf("ls: cannot access %s: No such file or directory.\n", argv_dir);//err
			return 1;
		}
	}
   
	 //directory

    chdir(argv_dir); //change directory
   
	while((dirnt = readdir(dir)) != NULL) { //read one data per each loop 
		
		if(!strcmp(argv_opt, "empty")) { // ls with directory with no option
			if(dirnt->d_name[0] != '.') { //if it is not hidden file, or directory
				printf("%s   ", dirnt->d_name); //print out the file or directory
			}
		}
		else if(!strcmp(argv_opt, "-a")) { //ls with directory with -a
			 printf("%s   ", dirnt->d_name); //print all the file or directory
		}
		else if(!strcmp(argv_opt, "-l")) { //ls with directory with -l
			 execl("/bin/ls", "ls", "-l", NULL); //show the file's or directory's information
		}
	} //while
	printf("\n");
	closedir(dir); //close directory.
 }

