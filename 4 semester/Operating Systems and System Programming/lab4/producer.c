#include "functions.h"

struct ring_buffer* buffer_ptr = NULL;

void sigterm_handler(int signum){
    if(buffer_ptr != NULL) {
    	detach_shm(buffer_ptr);
    }
    raise(SIGKILL);
}

int main (int argc, char* argv[], char* envp[]){
    
    int sem_id = 0;
    int shm_id = 0;
    
    signal(SIGTERM, sigterm_handler);
    
    sem_id = create_sem(sem_key, 3);
    
    shm_id = create_shm(shm_key, sizeof(struct ring_buffer));
    buffer_ptr = attach_shm(shm_id, buffer_ptr);
    
    // "Производство" сообщений
    while(1){
    	manage_sem(sem_id, W_SEM, -1);
    	if(buffer_ptr->full != 1){
    		push_msg(buffer_ptr, init_msg());
    	} else {
    		manage_sem(sem_id, STDOUT_SEM, -1);
    		printf("BUFFER IS FULL\n");
    		manage_sem(sem_id, STDOUT_SEM, 1);
    	}
    	manage_sem(sem_id, W_SEM, 1);
    	sleep(1);
    }
    detach_shm(buffer_ptr);
    
    return 0;
}

