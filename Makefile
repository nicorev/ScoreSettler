CC = gcc

all: server.x logic.x client.x

clean: 
	rm -f *.o *.x

server.x:
	$(CC) server.c -o server.x

client.x:
	$(CC) client.c -o client.x

logic.x:
	$(CC) logic.c -o logic.x
