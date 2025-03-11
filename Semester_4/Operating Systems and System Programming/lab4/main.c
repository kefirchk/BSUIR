#include "functions.h"

int main(int argc, char* argv[]) {

    char* option = get_str_mem(MAX_STR_LEN + 1);      //буфер ввода опции
    char* consumer_name = get_str_mem(MAX_SIZE_NAME); //имя процесса потребителя
    	
    int shm_id = 0;
    int sem_id = 0;
    struct ring_buffer* buffer_ptr = NULL;
    
    // Получение общей разделяемой памяти
    shm_id = create_shm(shm_key, sizeof(struct ring_buffer));
    buffer_ptr = attach_shm(shm_id, buffer_ptr);
    
    // Инициализация кольцевого буфера
    init_ring_buffer(buffer_ptr);
    
    // Получение набора семафоров
    sem_id = create_sem(sem_key, 3);
    
    // Установка начальных значений для семафоров
    set_sem_val(sem_id, R_SEM);      // read from ring buffer
    set_sem_val(sem_id, W_SEM);      // write to the ring buffer
    set_sem_val(sem_id, STDOUT_SEM); // write to the stdout

    puts("Enter 'h' for help\n");
    
    while (1) {
    
        rewind(stdin);
        strcpy(option, "");
        fgets(option, MAX_STR_LEN, stdin);

        // Выполняем выбранную опцию
        if (!strcmp(option, "h\n")) {                 // h
            manage_sem(sem_id, STDOUT_SEM, -1);
            instructions();
            manage_sem(sem_id, STDOUT_SEM, 1);
     
        } else if (!strcmp(option, "+p\n")) {         // +p
	    manage_sem(sem_id, STDOUT_SEM, -1);            
            add_producer();
            manage_sem(sem_id, STDOUT_SEM, 1);
            
        } else if (!strcmp(option, "+c\n")) {         // +c
            manage_sem(sem_id, STDOUT_SEM, -1);            
            add_consumer();
            manage_sem(sem_id, STDOUT_SEM, 1);
            
        } else if (!strcmp(option, "-p\n")) {         // -p
            manage_sem(sem_id, STDOUT_SEM, -1);
            kill_producer();
            manage_sem(sem_id, STDOUT_SEM, 1);
            
        } else if (!strcmp(option, "-c\n")) {         // -c
            manage_sem(sem_id, STDOUT_SEM, -1);
            kill_consumer();
            manage_sem(sem_id, STDOUT_SEM, 1);

        } else if (!strcmp(option, "l\n")) {          // l
            manage_sem(sem_id, STDOUT_SEM, -1);
            list_of_processes();
            manage_sem(sem_id, STDOUT_SEM, 1);
        
        } else if (!strcmp(option, "q\n")) {          // q
            manage_sem(sem_id, STDOUT_SEM, -1);
            kill_all_producers();
            kill_all_consumers();
            manage_sem(sem_id, STDOUT_SEM, 1);
            free(option);
            break;
        } else {
        	fprintf(stderr, "Error: command not found\n");
        }
        
    }
    
    delete_shm(shm_id);
    detach_shm(buffer_ptr);
    delete_sem(sem_id);
    
    return 0;
}
