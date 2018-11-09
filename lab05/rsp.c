#include <stdio.h>
#include <time.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdlib.h>

jmp_buf pos;
void match();
int main() {
		int fd;
		FILE *fp;
		int number_of_match = 0;

		if((fd = creat("./report.txt", 0644))<0) { //create file
				printf("fail to create the file \"report.txt\"\n");
				return 0;
		}
		close(fd);

		if((fp = fopen("./report.txt", "w"))==NULL) { //open file
				printf("fail to open the file \"report.txt\"\n");
				return 0;
		}
		fprintf(fp, "=========================History=========================\n\n\n"); //only in file
		int who; //who you are going to match
		//R =1 P=2 S=3
		printf("You have to win three people [John], [Jack], [Jay] to exit the program.\n"); //game rule.
		who = setjmp(pos); //first who = 0 then longjmp's "count" variable
		if (who == 0 || who == 1) { //if first time or count is 1(setjmp's first return value is 0)
				printf("=========================Verses John(1)=========================\n"); //on screen
				fprintf(fp, "=========================Verses John(1)=========================\n"); //on file
		}
		else if(who == 2) { //if count is 2
				printf("=========================Verses Jack(2)=========================\n");
				fprintf(fp, "=========================Verses Jack(2)=========================\n");
		}
		else if(who ==3){ //if count is 3
				printf("=========================Verses Jay(3)==========================\n");
				fprintf(fp, "=========================Verses Jay(3)=========================\n");
		}
		else { //after won all of them
				printf("\n\n**You played %d games and finally won the game!!**\nEnd program.\n", number_of_match); //print number of match on screen
				fprintf(fp, "\n\n**You played %d games and finally won the game!!**\nEnd program.\n", number_of_match); //on file
				fprintf(fp, "\n\n=========================History Done=========================\n");
				fclose(fp); //close
				system("cat ./report.txt");
				return 0; //end progream
		}
		number_of_match++; //number of match
		match(fp); //rock paper scissors

}

void  match(FILE *fp) {
		static int count=1; //return value of jmp

		int myhand = 0; //my choice
		srand(time(NULL));
		printf("[1] for Rock // [2] for Paper // [3] for Scissors : ");
		scanf("%d", &myhand);
		int opphand = rand()%3 +1; //opponent choice, from 1 to 3 randomly
		if(myhand==1) { //me : rock
				if(opphand==1) { //opponent : rock
						printf("[You : Rock] [Computer : Rock]\nDraw!\n");
						fprintf(fp, "[You : Rock] [Computer : Rock]\nDraw!\n");
						//count doesn't change to rematch
						
				}
				else if(opphand==2) { //opponent : paper
						printf("[You : Rock] [Computer : Paper]\nLose!\n");
						fprintf(fp, "[You : Rock] [Computer : Paper]\nLose!\n");
						count--; //to go back to the person I just matched before
				}
				else { //opponent : scissors
						printf("[You : Rock] [Computer : Scissors]\nWin!\n");
						fprintf(fp, "[You : Rock] [Computer : Scissors]\nWin!\n");
						count++; //to match with next person
				}
		}
		else if(myhand==2) { //me : paper
				if(opphand==2) { //opponent : paper
						printf("[You : Paper] [Computer : Paper]\nDraw!\n");
						fprintf(fp, "[You : Paper] [Computer : Paper]\nDraw!\n");
						//count doesn't change to rematch
				}
				else if(opphand==3) { //opponent : scissors
						printf("[You : Paper] [Computer : Scissors]\nLose!\n");
						fprintf(fp, "[You : Paper] [Computer : Scissors]\nLose!\n");
						count--; //to go back to the person I just matched
				}
				else  { // opponent : rock
						printf("[You : Paper] [Computer : Rock]\nWin!\n");
						fprintf(fp, "[You : Paper] [Computer : Rock]\nWin!\n");
						count++; //to match with next person
				}
		}
		else if(myhand==3) { //me : scissors
				if(opphand==3) { //opponent : scissors
						printf("[You : Scissors] [Computer : Scissors]\nDraw!\n");
						fprintf(fp, "[You : Scissors] [Computer : Scissors]\nDraw!\n");
						//count doesn't change to rematch
				}
				else if(opphand==1) {//opponent : rock
						printf("[You : Scissors] [Computer : Rock]\nLose!\n");
						fprintf(fp, "[You : Scissors] [Computer : Rock]\nLose!\n");
						count--; //to go back to the person I just matched
				}
				else { //opponent : paper
						printf("[You : Scissors] [Computer : Paper]\nWin!\n");
						fprintf(fp, "[You : Scissors] [Computer : Paper]\nWin!\n");
						count++; //to match with next person
				}
		}
		else { //did not input 1 to 3
			printf("Wrong Choice\nEnd Program\n");
			exit(0);
		}
		if (count < 1) { //prevent count not to get smaller than 1
				count = 1;
		}
		longjmp(pos, count); //go to setjmp with "count"(setjmp's return value)
		return;



}

