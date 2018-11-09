#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <ncurses.h>
#include <syslog.h>

FILE *fp; //file pointer
FILE *fp2;
FILE *fp3;
int fd1[2]; //pipe
int fd2[2]; //pipe
//char *root = "root";
#define KEY_CR_ 0x0d
#define KEY_BACKSPACE_ 0x7f

#define BUFLEN_MAX 255

#define TRY_MAX 3

#define INIT_X (0)
#define INIT_Y (0)

#define ID_X (INIT_X + 10)
#define ID_Y (INIT_Y + 3)

#define PASSWORD_X (ID_X)
#define PASSWORD_Y (ID_Y + 1)

#define RESULT_X (0)
#define RESULT_Y (PASSWORD_Y + 2)

#define EXPIRE_TIME 30
#define MODE_PASSWORD 1
#define MODE_ID 2

int _client();
int _server();
void sign_up();
void sign_in();
int get_string(int, char*);
int library_main();
int library_server(char *);
int get_string_count;
int get_user_info(char *);
int get_book_info_all();
int get_book_info_select();
int book_rental(char *, char*);
int book_return(char *);
