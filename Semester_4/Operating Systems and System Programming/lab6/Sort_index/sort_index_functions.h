#include "../Libs/functions.h"
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#define MIN_AMOUNT_OF_THREADS 2   // минимальное количество потоков

struct cmd_args_s {               // аргументы командной строки
    int buffer_size;              // размер буфера
    int amount_of_blocks;         // количество блоков в буфере
    int amount_of_threads;        // количество потоков
};

struct thread_s {                 // параметры потока
    pthread_t thread;             // поток
    void* buffer_address;         // адрес буфера
    int thread_number;            // номер потока
    int amount_of_blocks;         // количество блоков
    int block_size;               // размер блока
};

static struct cmd_args_s* cmd_args = NULL;                        // аргументы командной строки
static pthread_barrier_t barrier;                                 // барьер
static pthread_mutex_t map_mutex = PTHREAD_MUTEX_INITIALIZER;     // мьютекс для карты
static pthread_mutex_t stdout_mutex = PTHREAD_MUTEX_INITIALIZER;  // мьютекс для вывода
static int* busy_map;                                             // карта
static struct thread_s* threads = NULL;                           // массив потоков
static struct stat file_statistics;                               // статистика о файле

struct cmd_args_s* get_cmd_args(char* argv[]);                    // получить структуру аргументов командной строки
struct thread_s* init_thread_array(int amount_of_threads);        // инициализация массива потоков
int* init_busy_map(int amount_of_blocks);                         // инициализация карты
int get_amount_of_buffers(int filesize, int buffer_size);         // получить количество буферов
int comparator_for_qsort(const void*, const void*);               // компаратор для сортировки
void merge_blocks(void* block_address, int block_size);           // слияние блоков