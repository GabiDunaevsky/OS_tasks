CC=gcc
FLAGS= 

all: mutex fcntl cond server client

run: all
	./mutex
	./fcntl 
	./cond 
	./server & ./client

mutex: mutex.c
	$(CC) $(FLAGS) mutex.c -o mutex

fcntl: fcntl.c
	$(CC) $(FLAGS) fcntl.c -o fcntl

cond: cond.c
	$(CC) $(FLAGS) cond.c -pthread -o cond

server: server.c
	$(CC) $(FLAGS) server.c -o server

client: client.c
	$(CC) $(FLAGS) client.c -o client

.PHONY: 
	clean all run

clean:
	rm -f *.o *.a mutex fcntl cond server client