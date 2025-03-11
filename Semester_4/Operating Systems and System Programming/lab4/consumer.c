#include "functions.h"

struct ring_buffer* buffer_ptr = NULL;

void sigterm_handler(int signum){
    if(buffer_ptr != NULL) {
    	detach_shm(buffer_ptr);
    }
    raise(SIGKILL);
}

int main (int argc, char* argv[], char* envp[]) {

    int shm_id = 0;
    int sem_id = 0;
    struct message msg;
    
    signal(SIGTERM, sigterm_handler);
    
    sem_id = create_sem(sem_key, 3);

    shm_id = create_shm(shm_key, sizeof(struct ring_buffer));
    buffer_ptr = attach_shm(shm_id, buffer_ptr);
        
    // "Потребительство" сообщений
    while(1){
    	manage_sem(sem_id, R_SEM, -1);
    	if(buffer_ptr->empty != 1) {
    		manage_sem(sem_id, STDOUT_SEM, -1);
    		msg = pop_msg(buffer_ptr);
    		printf("\n=============================Begin of eating==================================\n");
    		for(int i = 0; i < msg.size; i++){
    			printf("%d ", msg.data[i]);
    		}
    		printf("\n=============================End of eating====================================\n");
    		manage_sem(sem_id, STDOUT_SEM, 1);
    	} else {
    		manage_sem(sem_id, STDOUT_SEM, -1);
    		printf("BUFFER IS EMPTY\n");
    		manage_sem(sem_id, STDOUT_SEM, 1);
    	}
    	manage_sem(sem_id, R_SEM, 1);
    	sleep(1);
    }
    detach_shm(buffer_ptr);
    
    return 0;
}

