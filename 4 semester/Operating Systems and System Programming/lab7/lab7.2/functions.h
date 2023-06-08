#pragma once
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

#define STRING_LENGTH 80               // длина строкового буфера
#define AMOUNT_OF_RECORDS 10           // количество записей в файле
#define MIN_AGE 10                     // максимальный возраст
#define MAX_AGE 80                     // минимальный возраст

struct record_s {
    char name[STRING_LENGTH];          // имя
    char surname[STRING_LENGTH];       // фамилия
    uint8_t age;                       // возраст
};

int get_random_number(int min, int max);
void instructions();
int set_lock(int fd, short type, short whence, off_t start, off_t len);
void table_hat();
void table_end();
void lst_function(int fd);
struct record_s get_function(int fd, int index);
