/* ----------------------------------------------------------------------------------------------------
*  ����: book.c
*  ���	: ���� �뿩/�ݳ� ���� ����
*  ������: 201520934 ������
*  ��¥	: 1�� ���� : 2018�� 6�� 8��
*----------------------------------------------------------------------------------------------------*/
#include "fake_apue.h"

int book_rental(char *book_name, char* id) {


		char *book_info = (char *)malloc(256);
		int exist = 0;

		fseek(fp2, 0, SEEK_SET);
		memset(book_info, 0, 256);
		while(fgets(book_info, 256, fp2) > 0) { //�� �پ� �о��
				book_info[strlen(book_info)-10] = '\0'; //, 0001, V\n ���� �Ǿտ� ,�ڸ��� null
				if(!strcmp(book_info, book_name)) { //���� �̸��� ���ؼ� ��ġ�ϸ�
						exist =1; //����
						break;
				}
		}
		if(exist == 0) { //���� ���� ������
				send(s_c_sock, "not exist\0", 30, 0); //��ġ���� �ʴ´ٴ� ���� ����
		}
		else {  //�����ϸ�
				char valid = '\0';
				fseek(fp2, -2, SEEK_CUR); //-2��ŭ �̵� �� (V\n)
				fscanf(fp2, "%c ", &valid); //V �Ǵ� I �� �޾ƿ�
				if(valid == 'I') { //I�� (invalid)
						send(s_c_sock, "cannot rent\0", 30, 0); //�뿩�� �� ���ٴ� �޽��� ����
				}
				else if(valid == 'V') { //V�� (valid)
						fseek(fp2, -2, SEEK_CUR); //�ٽ� -2��ŭ �̵� �� (2��ŭ �о��� ������)
						fprintf(fp2, "I"); //V�� I�� �ٲ�
						fflush(fp2);
						fprintf(fp3, "%s,%s\n", book_name, id); // rent.txt�� �뿩 ������ ���
						fflush(fp3);
						send(s_c_sock, "success!\0", 30, 0); //���� �ߴٴ� �޽��� ����
				}
		}
		
		free(book_info);
		return 0;

}

int book_return(char *id) {
		char rent_info[100] = {0, };
		char to_return[100] = {0, };
		char * token = NULL;
		char **buf = (char**)malloc(sizeof(char*)*2);
		int exist = 0;
		char temp_info[100];
		FILE *temp = fopen("./temp.txt", "w+"); //�ӽ� ���� ����
		fseek(fp3, 0, SEEK_SET);
		send(s_c_sock, "===============List===============\0", 128, 0); //Ŭ���̾�Ʈ�� ����
		while(fgets(rent_info, 100, fp3) > 0) { //�뿩 ����� ���� �� �о�ͼ�
				rent_info[strlen(rent_info)-1] = '\0';
				memset(temp_info, 0, 100);

				strcpy(temp_info, rent_info);

				token = strtok(temp_info, ","); // ','������ �߶���
				int i=0;
				while(token != NULL) {
						buf[i] = (char*)malloc(30);
						memset(buf[i], 0, 30);
						buf[i] = token; //�߶� �� ���� buf[i]�� �־���
										//ó���� ���� �� �ι� °�� id
						buf[i][strlen(buf[i])] = '\0';
						i++;
						token=strtok(NULL, ",");
				}
				if(!strcmp(buf[1], id)) { //id�� ��ġ �Ѵٸ�
						exist = 1; //����
						send(s_c_sock, buf[0], 128, 0); //���� ���� ����
						fseek(fp2, 0, SEEK_SET); //rent.txt �������� ó������ �̵�
						while(fgets(to_return, 100, fp2) >0) { //���� �� �޾ƿͼ�
								token = strtok(to_return, ","); //,������ �߶�
								if(!strcmp(token, buf[0])) { //ù��° ��ū(������)�� ��ġ�ϸ�
										fseek(fp2, -2, SEEK_CUR); //I�ڸ���
										fprintf(fp2, "V\n"); //V�� �Է�
										fflush(fp2);
								}
								memset(to_return, 0, 100);
						}
				}
				else { //��ġ���� �ʴٸ�
						fprintf(temp, "%s\n", rent_info); //�ӽ����Ͽ� ���� ���
				}
		}
		if(exist == 0) {//�������� �ʴ´ٸ�
				send(s_c_sock, "You have not rent any book\0", 128, 0); //�뿩�� å�� ���ٴ� �޽��� ����
		}
		else {
				send(s_c_sock, "\n\nComplete Returning\0", 128, 0); //�Ϸ� �޽��� ����
		}
		send(s_c_sock, "done\0", 128, 0); //done �޽��� ����
		system("rm -f ./rent.txt"); //rent.txt���� ����
		rename("./temp.txt", "./rent.txt"); //�Ͻ����� �̸��� rent.txt�� ����
		
		fclose(fp3); //fp3(���� rent.xt)�� ����
		fp3 = fopen("./rent.txt", "a+"); //fp3�� ���ο� rent.txt��

		return 0;
}

