#include "apue_fake.h"
int main() {

		int menu=0;
		char select;
		char file[128];
		char dir[128];
		int mode;
		
		//loop until input is not number
		while(isdigit(menu+48)) { //+48 is for ASCII
			//menu
			printf("\nPlease Select Menu. (0 to exit)\n");
			printf("1.Get User Information\n");
			printf("2.Find a File\n");
			printf("3.Print and Save the File's Information\n");
			printf("4.Change the file \"find.txt\"'s Mode and Ownership\n");
			printf("INPUT : ");
			menu = 'd';
			scanf("%d", &menu);
			while(getchar() != '\n');
			
			//get user information
			if(menu == 1) {
					printf("===============get user information===============\n");
					getUserInfo();
					printf("\n");
			}
			//find a file
			else if(menu == 2) {
					printf("===================find the file==================\n");
					printf("Please enter [file name] [start directory] : ");
					scanf("%s %s", file, dir);

					if(find(file, dir) == 0) {
							printf("Failed..\n");
					}
					else printf("Complete!\n");
			}
			//print and save the file's information
			else if(menu == 3) { 
					printf("=================file information=================\n");
					fileInfo();
			}
			//change mode and ownership
			else if(menu == 4){
					printf("=============change mode and ownership============\n");
					printf("Please enter [file mode] [file name] : ");
					scanf("%o %s", &mode, file);
				
					ch(mode, file);
					printf("Complete!\n");
			}
	
			else if(menu == 0) {
					printf("End Program.\n");
					break;
			}
			else{	//if not digit end program
					if(!isdigit(menu+48)) {
							printf("Did not Inserted Number\nEnd Program\n");
							break;
					}
					//if not continue
					else printf("Inserted Wrong Number.\n");
			}
		}

		return 0;

}
