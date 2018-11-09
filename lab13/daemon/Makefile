all: server client

CC = gcc

server: server.o library_server.o daemon.o info.o book.o start_server.o
	$(CC) -o server server.o library_server.o info.o book.o daemon.o start_server.o

client: client.o get_string.o sign.o start_client.o
	$(CC) -o client client.o get_string.o sign.o start_client.o -lncurses
#===================================================================
#Release Mode object files.(SERVER)
#==================================================================

server.o: server.c
	$(CC) -o server.o -O server.c -c

librry_server.o: client_server.c
	$(CC) -o librry_server.o -O library_server.c -c
info.o: info.c
	$(CC) -o info.o -O info.c -c

book.o: book.c
	$(CC) -o book.o -O book.c -c
daemon.o: daemon.c
	$(CC) -o daemon.o -O daemon.c -c

start_server.o: start_server.c
	$(CC) -o start_server.o -O start_server.c -c
#================================================================
#Release Mode object files.(CLIENT)
#===============================================================

client.o: client.c
	$(CC) -o client.o -O client.c -c

get_string.o: get_string.c
	$(CC) -o get_string.o -O get_string.c -c

sign.o: sign.c
	$(CC) -o sign.o -O sign.c -c

start_client.o: start_client.c
	$(CC) -o start_client.o -O start_client.c -c

clean:
	rm -f *.o *~ server client


	
