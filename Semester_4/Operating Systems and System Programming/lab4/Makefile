#makefile
CC = gcc
CFLAGS = -W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic

SOURCES1 = main.c functions.c
SOURCES2 = producer.c functions.c
SOURCES3 = consumer.c functions.c
OBJECTS1 = $(SOURCES1:.c=.o)
OBJECTS2 = $(SOURCES2:.c=.o)
OBJECTS3 = $(SOURCES3:.c=.o)
EXECUTABLE1 = main
EXECUTABLE2 = producer
EXECUTABLE3 = consumer

.PHONY: clean

all: $(SOURCES1) $(SOURCES2) $(SOURCES3) $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)

$(EXECUTABLE1): $(OBJECTS1)
	$(CC) $(CFFLAGS) $(OBJECTS1) -o $@

$(EXECUTABLE2): $(OBJECTS2)
	$(CC) $(CFFLAGS) $(OBJECTS2) -o $@

$(EXECUTABLE3): $(OBJECTS3)
	$(CC) $(CFFLAGS) $(OBJECTS3) -o $@
    
clean:
	rm -f $(OBJECTS1) $(OBJECTS2) $(OBJECTS3) $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)
