#include "apue_fake.h"

void getUserInfo() {
		struct passwd *pw;
		uid_t uid;
		time_t time_now;

		//uid = getuid();
		uid = 500; //my uid

		pw = getpwuid(uid); //get my user information by uid

		//print my name, user id, group id, home directory
		printf("My Information = name : %s, \nuid : %d, gid : %d, \nhome : %s\n"
						,pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir); 

		endpwent();  //close password file
		return;
}
