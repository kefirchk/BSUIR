#makefile
CC = gcc
CFLAGS = -W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic -pthread -Wno-pointer-arith

SOURCES1 = ./Sort_index/sort_index.c ./Sort_index/sort_index_functions.c
SOURCES2 = ./Generator/generator.c ./Libs/functions.c
SOURCES3 = ./Reader/reader.c ./Libs/functions.c
OBJECTS1 = $(SOURCES1:.c=.o)
OBJECTS2 = $(SOURCES2:.c=.o)
OBJECTS3 = $(SOURCES3:.c=.o)
EXECUTABLE1 = sort_index
EXECUTABLE2 = generator
EXECUTABLE3 = reader

.PHONY: clean

all: $(SOURCES1) $(SOURCES2) $(SOURCES3) $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)

$(EXECUTABLE1): $(OBJECTS1)
	$(CC) $(CFLAGS) $(OBJECTS1) -o $@

$(EXECUTABLE2): $(OBJECTS2)
	$(CC) $(CFLAGS) $(OBJECTS2) -o $@

$(EXECUTABLE3): $(OBJECTS3)
	$(CC) $(CFLAGS) $(OBJECTS3) -o $@
    
clean:
	rm -f $(OBJECTS1) $(OBJECTS2) $(OBJECTS3) $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)
