#define _GNU_SOURCE

#define MODIFIED_JULIAN_DAY 60094.53819  // юлианский день на 31.05.2023 21:46
#define JD_FIRST_LIMIT 15020.0
#define MULTIPLE_NUMBER 256

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

struct index_s {
	double time_mark;        // временная метка (модифицированная юлианская дата)
	uint64_t recno;          // первичный индекс в таблице БД
};

struct index_hdr_s {
	uint64_t records;        // количество записей
	struct index_s* idx;     // массив записей в количестве records
};

// generator:
uint64_t get_amount_of_records(uint64_t amount_of_records);
double generate_julian_day();
