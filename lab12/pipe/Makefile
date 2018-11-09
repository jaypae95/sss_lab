all: main

CC = gcc

main: client.o server.o get_string.o sign.o library_server.o info.o book.o main.o
	$(CC) -o main client.o server.o get_string.o sign.o library_server.o info.o book.o main.o -lncurses
#===================================================================
#Release Mode object files.
#==================================================================

client.o: client.c
	$(CC) -o client.o -O client.c -c

server.o: server.c
	$(CC) -o server.o -O server.c -c

get_string.o: get_string.c
	$(CC) -o get_string.o -O get_string.c -c

sign.o: sign.c
	$(CC) -o sign.o -O sign.c -c

librry_server.o: client_server.c
	$(CC) -o librry_server.o -O library_server.c -c

info.o: info.c
	$(CC) -o info.o -O info.c -c

book.o: book.c
	$(CC) -o book.o -O book.c -c

main.o: main.c
	$(CC) -o main.o -O main.c -c

clean:
	rm -f *.o  main


	
