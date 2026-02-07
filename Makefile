CC = gcc
CFLAGS = -Wall -pthread

all:server

server: server.c logger.c
	$(CC) $(CFLAGS) server.c logger.c -o server

clean:
	rm -f server game.log score.txt