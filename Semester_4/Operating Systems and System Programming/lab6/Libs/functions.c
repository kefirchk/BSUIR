#include "functions.h"

uint64_t get_amount_of_records(uint64_t amount_of_records) {
	
    if(amount_of_records <= 0) {
        fprintf(stderr, "Error: index size in records must be greater than zero\n");
        return -1;
    }
    if(amount_of_records % MULTIPLE_NUMBER != 0) {
        fprintf(stderr, "Error: index size in records must be a multiple of %d\n", MULTIPLE_NUMBER);
        return -1;
        //amount_of_records -= (amount_of_records % MULTIPLE_NUMBER) + MULTIPLE_NUMBER;  // автоподгонка размера
    }
	return amount_of_records;
}


double generate_julian_day() {
    double jd;
    jd = (rand() % ((int)MODIFIED_JULIAN_DAY - (int)JD_FIRST_LIMIT)) + JD_FIRST_LIMIT;
    jd += (double)rand() / RAND_MAX + 0.5;
    return jd;
}