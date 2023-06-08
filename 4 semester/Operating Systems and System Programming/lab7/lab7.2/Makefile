#makefile
CC = gcc
CFLAGS = -W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic

SOURCES1 = main.c functions.c
SOURCES2 = generator.c functions.c
OBJECTS1 = $(SOURCES1:.c=.o)
OBJECTS2 = $(SOURCES2:.c=.o)
EXECUTABLE1 = main
EXECUTABLE2 = generator

.PHONY: clean

all: $(SOURCES1) $(SOURCES2) $(EXECUTABLE1) $(EXECUTABLE2)

$(EXECUTABLE1): $(OBJECTS1)
	$(CC) $(CFLAGS) $(OBJECTS1) -o $@

$(EXECUTABLE2): $(OBJECTS2)
	$(CC) $(CFLAGS) $(OBJECTS2) -o $@
    
clean:
	rm -f $(OBJECTS1) $(OBJECTS2) $(EXECUTABLE1) $(EXECUTABLE2)
