#include "sort_index_functions.h"

void* sort_index(void* thread_args);  // обработчик потока сортировки
void merge_buffers(int fd);

int main(int argc, char* argv[]) {

    if(argc != 5) {
        fprintf(stderr, "Error: command line arguments are incorrect\n");
        printf("Format: ./sort_index [размер_буфера] [количество_блоков] [количество_потоков] [имя_файла]\n");
        return -1;
    }
    // Получение аргументов из командной строки с их валидацией
    cmd_args = get_cmd_args(argv);
    if(cmd_args == NULL) {
        return -1;
    }

    pthread_barrier_init(&barrier, NULL, cmd_args->amount_of_threads);
    busy_map = init_busy_map(cmd_args->amount_of_blocks);
    threads = init_thread_array(cmd_args->amount_of_threads);

    int fd = open(argv[4], O_RDWR);
    if(fd == -1) {
        fprintf(stderr, "Error: file cannot be opened\n");
        return -1;
    }
    fstat(fd, &file_statistics);

    //-------------------------------------------------
    // Начало основного алгоритма программы сортировки
    //-------------------------------------------------

    int amount_of_buffers = get_amount_of_buffers(file_statistics.st_size, cmd_args->buffer_size);
    int block_size;
    void* buffer_address;

    for(int i = 0; i < amount_of_buffers; ++i) {

        // Вычисление размера блоков
        if(i != amount_of_buffers - 1) {
            block_size = cmd_args->buffer_size / cmd_args->amount_of_blocks;
        } else {
            block_size = (file_statistics.st_size - (i * cmd_args->buffer_size)) / cmd_args->amount_of_blocks;
        }

        // Отображение памяти в адресное пространство
        buffer_address = mmap(NULL, 
                            cmd_args->buffer_size, 
                            PROT_READ | PROT_WRITE, MAP_SHARED, 
                            fd, 
                            i * cmd_args->buffer_size);

        // Зануление карты занятости потоков
        for(int i = 0; i < cmd_args->amount_of_blocks; ++i) {
            busy_map[i] = 0;
        }

        // Создание потоков сортировки
        for(int j = 0; j < cmd_args->amount_of_threads; ++j) {
            busy_map[j] = 1;
            threads[j].amount_of_blocks = cmd_args->amount_of_blocks;
            threads[j].block_size = block_size;
            threads[j].thread_number = j;
            threads[j].buffer_address = buffer_address;
            pthread_create(&threads[j].thread, NULL, sort_index, &threads[j]);
        }

        // Ожидание завершение потоков
        for(int j = 0; j < cmd_args->amount_of_threads; ++j) {
            pthread_join(threads[j].thread, NULL);
        }

        munmap(buffer_address, cmd_args->buffer_size);
    }

    // Финальная стадия слияния буферов
    merge_buffers(fd);

    //-------------------------------------------------
    // Конец основного алгоритма программы сортировки
    //-------------------------------------------------

    // Освобождение ресурсов
    pthread_mutex_destroy(&map_mutex);
    pthread_barrier_destroy(&barrier);
    close(fd);
    free(cmd_args);
    free(busy_map);
    free(threads);

    return 0;
}

// Проверка карты занятости
int check_busy_map(int amount_of_blocks) {
    for(int i = 0; i < amount_of_blocks; ++i) {
        if(busy_map[i] == 0) {
            busy_map[i] = 1;
            return i;
        }
    }
    return -1;
}

// Слияние буферов
void merge_buffers(int fd) {
    struct index_s* address = NULL;
    struct index_s* buffer = NULL;

    int current_records_in_buffer = 0;
    int j = 0, k = 0, p = 0;

    int records_in_file = file_statistics.st_size / sizeof(struct index_s);
    int amount_of_buffers = get_amount_of_buffers(file_statistics.st_size, cmd_args->buffer_size);
    int records_in_buffer = cmd_args->buffer_size / sizeof(struct index_s);

    if(amount_of_buffers > 1) {
        buffer = (struct index_s*)malloc(records_in_file * sizeof(struct index_s));
        if(buffer == NULL) {
            fprintf(stderr, "Error: failed to allocate memory\n");
            exit(EXIT_FAILURE);
        }
        address = mmap(NULL, file_statistics.st_size, 
                    PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

        
        for(int i = 0; i < amount_of_buffers - 1; ++i, j = 0, k = 0, p = 0) {

            if(i != (amount_of_buffers - 2)) {
                current_records_in_buffer = records_in_buffer;
            } else {
                current_records_in_buffer = (file_statistics.st_size - ((i + 1) * cmd_args->buffer_size)) / sizeof(struct index_s);
            }

            while (j < (records_in_buffer * (i + 1)) && k < current_records_in_buffer) {
                if (address[j].time_mark < address[(records_in_buffer * (i + 1)) + k].time_mark) {
                    buffer[p++] = address[j++];
                } else {
                    buffer[p++] = address[(records_in_buffer * (i + 1)) + k++];
                }
            }
            while (j < (records_in_buffer * (i + 1))){
                buffer[p++] = address[j++];
            }
            while (k < current_records_in_buffer){
                buffer[p++] = address[(records_in_buffer * (i + 1)) + k++];
            }

            for(int t = 0; t < ((records_in_buffer * (i + 1)) + current_records_in_buffer); t++){
                address[t] = buffer[t];
            }
        }
        munmap(address, file_statistics.st_size);
        free(buffer);
    }

}

// Обработчик потоков сортировки
void* sort_index(void* thread_args) {
    struct thread_s* thread = (struct thread_s*)thread_args;
    int sort_offset, merge_offset = 0;

    pthread_barrier_wait(&barrier);

    // Сортировка блока потоком, который был поручен ему в первый раз
    qsort((char*)thread->buffer_address + (thread->thread_number * thread->block_size), 
            thread->block_size / sizeof(struct index_s),
            sizeof(struct index_s),
            (int(*)(const void*, const void*))comparator_for_qsort);
    
    // Сортировка блоков потоком после первой итерации
    do {
        pthread_mutex_lock(&map_mutex);
        sort_offset = check_busy_map(thread->amount_of_blocks);
        pthread_mutex_unlock(&map_mutex);
        if(sort_offset != -1) {
            qsort((char*)thread->buffer_address + (sort_offset * thread->block_size), 
                thread->block_size / sizeof(struct index_s),
                sizeof(struct index_s),
                (int(*)(const void*, const void*))comparator_for_qsort);
        }
    } while(sort_offset != -1);

    pthread_barrier_wait(&barrier);

    // Цикл по слиянию блоков
    for(int i = thread->amount_of_blocks, k = 2; i != 1; i /= 2, k *= 2) {

        // Один из потоков обнуляет карту (с номером '0')        
        pthread_barrier_wait(&barrier);
        for(int j = 0; thread->thread_number == 0 && j < i / 2; ++j) {
            busy_map[j] = 0;
        }
        pthread_barrier_wait(&barrier);

        // Слияние очередных блоков
        do {
            pthread_mutex_lock(&map_mutex);
            merge_offset = check_busy_map(i);
            pthread_mutex_unlock(&map_mutex);
            if(merge_offset != -1) {
                merge_blocks((char*)thread->buffer_address + (k * merge_offset * thread->block_size),
                            thread->block_size * k / 2);
            }
        } while (merge_offset != -1);
    }

    pthread_barrier_wait(&barrier);
    pthread_exit(NULL);
}