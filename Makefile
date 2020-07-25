CC = gcc

all: server.x logic.x client.x

clean: 
	rm -f *.o *.x

server.x: server.c
	$(CC) server.c -o server.x

client.x: client.c
	$(CC) client.c -o client.x

logic.x: logic.c
	$(CC) logic.c -o logic.x
