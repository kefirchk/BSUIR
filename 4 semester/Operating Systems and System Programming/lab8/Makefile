#makefile
CC = gcc
CFLAGS = -W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic

SOURCES1 = ./src/server.c ./src/server_functions.c ./src/sockets_functions.c
SOURCES2 = ./src/client.c ./src/sockets_functions.c
OBJECTS1 = $(SOURCES1:.c=.o)
OBJECTS2 = $(SOURCES2:.c=.o)
EXECUTABLE1 = server
EXECUTABLE2 = client

.PHONY: clean

all: $(SOURCES1) $(SOURCES2) $(EXECUTABLE1) $(EXECUTABLE2)

$(EXECUTABLE1): $(OBJECTS1)
	$(CC) $(CFFLAGS) $(OBJECTS1) -o $@

$(EXECUTABLE2): $(OBJECTS2)
	$(CC) $(CFFLAGS) $(OBJECTS2) -o $@

clean:
	rm -f $(OBJECTS1) $(OBJECTS2) $(EXECUTABLE1) $(EXECUTABLE2)
