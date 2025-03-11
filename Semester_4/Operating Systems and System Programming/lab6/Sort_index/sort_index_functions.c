#include "sort_index_functions.h"

// Получение аргументов командной строки
struct cmd_args_s* get_cmd_args(char* argv[]) {
    
    // Выделение памяти под структуру аргумментов командной строки
    struct cmd_args_s* cmd_args = (struct cmd_args_s*)malloc(1 * sizeof(struct cmd_args_s));
    if(cmd_args == NULL) {
        fprintf(stderr, "Error: failed to allocate memory\n");
        return NULL;
    }

    // Получение размер буфера
    cmd_args->buffer_size = atoi(argv[1]);
    if(cmd_args->buffer_size <= 0 || cmd_args->buffer_size % getpagesize() != 0) {
        fprintf(stderr, "Error: wrong buffer size\n");
        free(cmd_args);
        return NULL;
    }

    // Получение количества потоков
    cmd_args->amount_of_threads = atoi(argv[3]);
    long num_cores = sysconf(_SC_NPROCESSORS_ONLN);  // получаем количестов ядров процессора
    int max_amount_of_threads = 8 * num_cores;
    
    if(cmd_args->amount_of_threads > max_amount_of_threads || 
        cmd_args->amount_of_threads < MIN_AMOUNT_OF_THREADS) 
    {
        fprintf(stderr, "Error: wrong number of threads\n");
        free(cmd_args);
        return NULL;
    }

    // Получение размера блоков
    cmd_args->amount_of_blocks = atoi(argv[2]);
    int max_amount_of_blocks = getpagesize();
    if(cmd_args->amount_of_blocks <= 0 || cmd_args->amount_of_blocks > max_amount_of_blocks || 
        (cmd_args->amount_of_blocks & (cmd_args->amount_of_blocks - 1)) != 0 || // проверка, что количество блоков - это степень двойки 
        cmd_args->amount_of_blocks <= cmd_args->amount_of_threads)                        // проверка, что количество блоков > количество потоков
    {
        fprintf(stderr, "Error: wrong number of blocks\n");
        free(cmd_args);
        return NULL;
    }

    return cmd_args;
}

// Инициализация карты
int* init_busy_map(int amount_of_blocks) {
    int* ptr = (int*)calloc(amount_of_blocks, sizeof(int));
    if(ptr == NULL) {
        fprintf(stderr, "Error: failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// Инициализация массива потоков
struct thread_s* init_thread_array(int amount_of_threads) {
    struct thread_s* ptr = (struct thread_s*)malloc(amount_of_threads * sizeof(struct thread_s));
    if(ptr == NULL) {
        fprintf(stderr, "Error: failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// Получение количества буферов
int get_amount_of_buffers(int filesize, int buffer_size) {
    int amount_of_buffers = filesize / buffer_size;
    if((filesize % buffer_size) != 0) {
        ++amount_of_buffers;
    }
    return amount_of_buffers;
}

// Компаратор для сортировки
int comparator_for_qsort(const void* first_arg, const void* second_arg) {
    struct index_s* first = (struct index_s*)first_arg;
    struct index_s* second = (struct index_s*)second_arg;

    if(first->time_mark > second->time_mark) {
        return 1;
    } else if(first->time_mark < second->time_mark) {
        return -1;
    } else {
        return 0;
    }
}

// Слияние блоков
void merge_blocks(void* block_address, int block_size) {
    struct index_s* first = block_address;
    struct index_s* second = block_address + block_size;
    struct index_s* result = NULL;

    unsigned long int amount_of_records = block_size / sizeof(struct index_s);
    unsigned long int i = 0, j = 0, k = 0;

    result = (struct index_s*)malloc((2 * amount_of_records) * sizeof(struct index_s));
    if(result == NULL) {
        fprintf(stderr, "Error: failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    while(i < amount_of_records && j < amount_of_records) {
        if(first[i].time_mark < second[j].time_mark) {
            result[k++] = first[i++];
        } else {
            result[k++] = second[j++];
        }
    }

    while(i < amount_of_records) {
        result[k++] = first[i++];
    }
    
    while(j < amount_of_records) {
        result[k++] = second[j++];
    }
    
    for(unsigned long int c = 0; c < amount_of_records * 2; ++c) {
        first[c] = result[c];
    }
   
    free(result);
}
