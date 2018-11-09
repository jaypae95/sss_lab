#ifndef apue_fake_h
#define aque_fake_h

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <pwd.h>
#include <dirent.h>

#define MAX_PATH_NAME 4096
#define MAX_FILE_NAME 256

void getUserInfo();

int find(char *, char *);
static char find_file_name[MAX_FILE_NAME];
static int search_dir(char *, int *);

int fileInfo();
static void check_file_type(struct stat *, FILE **);
static void check_file_permission(struct stat *, FILE **);

void ch(int, char*);
void showfile_info(char *);

int main();

#endif
