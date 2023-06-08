#makefile
CC = gcc
CFLAGS = -W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic -pthread

SOURCES1 = main.c functions.c
OBJECTS1 = $(SOURCES1:.c=.o)
EXECUTABLE1 = main

.PHONY: clean

all: $(SOURCES1) $(EXECUTABLE1)

$(EXECUTABLE1): $(OBJECTS1)
	$(CC) $(CFFLAGS) $(OBJECTS1) -o $@
    
clean:
	rm -f $(OBJECTS1) $(EXECUTABLE1)
