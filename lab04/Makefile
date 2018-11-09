all: main debug

CC = gcc

main: get_userinfo.o find.o file_info.o main.o ch.o
	$(CC) -o main get_userinfo.o find.o file_info.o ch.o main.o

debug: get_userinfo.od find.od file_info.od main.od ch.od
	$(CC) -o debug get_userinfo.od find.od file_info.od ch.od main.od

#===================================================================
#Release Mode object files.
#==================================================================

get_userinfo.o: get_userinfo.c
	$(CC) -o get_userinfo.o -O get_userinfo.c -c

find.o: find.c
	$(CC) -o find.o -O find.c -c

file_info.o: file_info.c
	$(CC) -o file_info.o -O file_info.c -c

ch.o: ch.c
	$(CC) -o ch.o -O ch.c -c

main.o: main.c
	$(CC) -o main.o -O main.c -c

#===================================================================
#Debug Mode object files.
#==================================================================

get_userinfo.od: get_userinfo.c
	$(CC) -o get_userinfo.od -DDEBUG -g get_userinfo.c -c

find.od: find.c
	$(CC) -o find.od -DDEBUG -g find.c -c

file_info.od: file_info.c
	$(CC) -o file_info.od -DDEBUG -g file_info.c -c

ch.od: ch.c
	$(CC) -o ch.od -DDEBUG -g ch.c -c

main.od: main.c
	$(CC) -o main.od -DDEBUG -g main.c -c


clean:
	rm -f *.o *.od main debug


	
