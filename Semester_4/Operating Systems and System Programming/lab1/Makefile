#makefile
CC=gcc
CFLAGS= -g -pedantic -std=c11 -W -Wall -Wextra -o ./lab1
.PHONY : clean
all: main.o
main.o : lab1.c Makefile
	$(CC) $(CFLAGS) lab1.c -o lab1
clean:
	rm -rf lab1
