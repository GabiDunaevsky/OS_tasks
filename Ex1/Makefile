CC=gcc
FLAGS= 

all: mync myshell mytee

mync: mync.c
	$(CC) $(FLAGS) mync.c -o mync

myshell: myshell.c
	$(CC) $(FLAGS) myshell.c -o myshell

mytee: mytee.c
	$(CC) $(FLAGS) mytee.c -o mytee

.PHONY: 
	clean all

clean:
	rm -f *.o *.a *.so mync myshell mytee tmppp.txt