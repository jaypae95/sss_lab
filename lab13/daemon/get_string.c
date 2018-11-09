#include "fake_apue.h"

int get_string(int mode, char *buf) {
		
		int n, res;
		char ch;
		if((mode != MODE_PASSWORD) && (mode != MODE_ID)) //if mode is not id or password
				return -1; //return error
		memset(buf, 0, strlen(buf));
		noecho();
		//mode == MODE_PASSWORD ? move(PASSWORD_Y, PASSWORD_X) : move(ID_Y, ID_X);
		move(ID_Y+get_string_count, ID_X);
		refresh();
		n = 0;
		while((res = read(0, &ch, 1))) { //read one character
				if(res<0) return -1;
				if(ch == KEY_CR_) break; //if enter, break
				if(ch == KEY_BACKSPACE_) { //if key is backspace
						if(n>0) {
								n--; //move to front
								move(ID_Y+get_string_count, ID_X + n);
								printw(" "); //switch character to space,to be seems nothing there
								move(ID_Y+get_string_count, ID_X + n);
								buf[n] = '\0';
								refresh();
						}
				}
				else {
						mode == MODE_PASSWORD ? printw("*") : printw("%c", ch); //if mode is password, mask to *
						refresh();
						buf[n++] = ch; //inset on buf one by one
						if(n>= BUFLEN_MAX) return -1;
				}
		}
		buf[n] = '\0';
		get_string_count++;
		return n;
}
