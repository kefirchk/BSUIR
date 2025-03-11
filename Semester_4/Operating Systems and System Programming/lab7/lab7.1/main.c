#include "functions.h"

void list_of_threads();
void get_info();
void* producer_handle(void* active_status);
void* consumer_handle(void* active_status);

int main(int argc, char* argv[]) {

    char* option = (char*)malloc((MAX_STR_LEN+1)*sizeof(char));      //буфер ввода опции
  
    // Инициализация кольцевого буфера
    init_ring_buffer(&queue);
    
    puts("Enter 'h' for help");
    
    while (1) {
    
        rewind(stdin);
        strcpy(option, "");
        fgets(option, MAX_STR_LEN, stdin);

        // Выполняем выбранную опцию
        if (!strcmp(option, "h\n")) {                 // h
            pthread_mutex_lock(&stdout_mutex);
            instructions();
            pthread_mutex_unlock(&stdout_mutex);
     
        } else if (!strcmp(option, "+p\n")) {         // +p
            pthread_mutex_lock(&stdout_mutex);
            producer_threads[producer_number].active = 1;
            pthread_create(&(producer_threads[producer_number].thread), 
            		NULL, 
            		producer_handle,
            		&producer_threads[producer_number].active);
            
            ++producer_number;
            printf("Producer_%d has been created\n", producer_number);
            pthread_mutex_unlock(&stdout_mutex);
            
        } else if (!strcmp(option, "+c\n")) {         // +c
            pthread_mutex_lock(&stdout_mutex);
            
            consumer_threads[consumer_number].active = 1;
            pthread_create(&consumer_threads[consumer_number].thread, 
            		NULL, 
            		consumer_handle,
            		&consumer_threads[consumer_number].active);
            ++consumer_number;
            printf("Consumer_%d has been created\n", consumer_number);
            pthread_mutex_unlock(&stdout_mutex);
            
        } else if (!strcmp(option, "-p\n")) {         // -p
            pthread_mutex_lock(&stdout_mutex);
            if(producer_number > 0) {
                --producer_number;
            	producer_threads[producer_number].active = 0;
                pthread_cond_broadcast(&write_cond);
            	//pthread_join(producer_threads[producer_number].thread, NULL);
            	printf("Producer_%d has been killed\n", producer_number+1);
            } else {
            	printf("Error: amount of producer's threads is zero\n");
            }
            pthread_mutex_unlock(&stdout_mutex);
            
        } else if (!strcmp(option, "-c\n")) {         // -c
            pthread_mutex_lock(&stdout_mutex);
            if(consumer_number > 0) {
                --consumer_number;            	
            	consumer_threads[consumer_number].active = 0;
                pthread_cond_broadcast(&read_cond);
            	//pthread_join(consumer_threads[consumer_number].thread, NULL);
            	printf("Consumer_%d has been killed\n", consumer_number+1);
            } else {
            	printf("Error: amount of consumer's threads is zero\n");
            }
            pthread_mutex_unlock(&stdout_mutex);

        } else if (!strcmp(option, "l\n")) {          // l
            pthread_mutex_lock(&stdout_mutex);
            list_of_threads();
            pthread_mutex_unlock(&stdout_mutex);
        
        } else if (!strcmp(option, "i\n")) {          // i
            pthread_mutex_lock(&stdout_mutex);
            get_info();
            pthread_mutex_unlock(&stdout_mutex);
        
        } else if (!strcmp(option, "q\n")) {          // q
            pthread_mutex_lock(&stdout_mutex);
            
            for(int i = 0; i < producer_number; ++i) {
            	producer_threads[i].active = 0;
                pthread_cond_broadcast(&write_cond);

            	//pthread_join(producer_threads[i].thread, NULL);
            }
            printf("All producers are killed\n");
            
            for(int i = 0; i < consumer_number; ++i) {
            	consumer_threads[i].active = 0;
                pthread_cond_broadcast(&read_cond);

            	//pthread_join(consumer_threads[i].thread, NULL);
            }
            printf("All consumers are killed\n");
            pthread_mutex_unlock(&stdout_mutex);
            break;
        } else {
        	fprintf(stderr, "Error: command not found\n");
        }
        
    }
    
    pthread_mutex_destroy(&write_mutex);	
    pthread_mutex_destroy(&read_mutex);
    pthread_mutex_destroy(&stdout_mutex);
    pthread_cond_destroy(&read_cond);
    pthread_cond_destroy(&write_cond);
    free(queue.buffer);
    free(option);
    
    return 0;
}


void list_of_threads()
{
    puts(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	puts("List of threads:");
	puts("----------------------------------------");
	printf("Main thread: id = %ld\n", pthread_self());
	puts("----------------------------------------");
	printf("PRODUCERS[all = %d]:\n", producer_number);
	for(int i = 0; i < producer_number; ++i) {
		printf("Producer_%d, thread id=%ld\n", i+1, producer_threads[i].thread);
	}
	puts("----------------------------------------");	
	printf("CONSUMERS[all = %d]:\n", consumer_number);
	for(int i = 0; i < consumer_number; ++i) {
		printf("Consumers_%d, thread id=%ld\n", i+1, consumer_threads[i].thread);
	}
    puts("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
}

void get_info() {
    puts(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    printf("Length of buffer: %d\n", queue.size);
    printf("Number of added message: %d\n", queue.push_msg);
    printf("Number of deleted message: %d\n", queue.pop_msg);
    puts("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
}

void* producer_handle(void* active_status){
    
    int* active = (int*)active_status;
    // "Производство" сообщений
    while(*active == 1) {
    	pthread_mutex_lock(&write_mutex);
    	if(queue.full != 1) {
    		push_msg(&queue, init_msg());
            pthread_cond_signal(&read_cond);
    	} else {
            while(queue.full == 1) {
                sleep(0.5);
    		    pthread_mutex_lock(&stdout_mutex);
    		    printf("BUFFER IS FULL\n");
    		    pthread_mutex_unlock(&stdout_mutex);

                pthread_cond_wait(&write_cond, &write_mutex);

                if(*active == 0) {
                    pthread_mutex_unlock(&write_mutex);
                    pthread_exit(NULL);
                }
            }
    	}
    	
    	pthread_mutex_unlock(&write_mutex);
    	sleep(SLEEP_DELAY);
    }
    pthread_exit(NULL);
}



void* consumer_handle(void* active_status) {

    int* active = (int*)active_status;
    struct message msg;
    
    // "Потребительство" сообщений
    while(*active == 1){
        pthread_mutex_lock(&read_mutex);
    	if(queue.empty != 1) {
        	pthread_mutex_lock(&stdout_mutex);
    		msg = pop_msg(&queue);
            pthread_cond_signal(&write_cond);
    		printf("\n=============================Begin of eating==================================\n");
    		printf("Message size: %d\n", msg.size);
    		printf("------------------------------------------------------------------------------\n");
    		for(int i = 0; i < msg.size; i++){
    			printf("%d ", msg.data[i]);
    		}
    		printf("\n=============================End of eating====================================\n");
        	pthread_mutex_unlock(&stdout_mutex);
    	} else {
            while(queue.empty == 1) {
                sleep(0.5);
        	    pthread_mutex_lock(&stdout_mutex);
    		    printf("BUFFER IS EMPTY\n");
        	    pthread_mutex_unlock(&stdout_mutex);

                pthread_cond_wait(&read_cond, &read_mutex);

                if(*active == 0) {
                    pthread_mutex_unlock(&read_mutex);
                    pthread_exit(NULL);
                }
            }
    	}
    	pthread_mutex_unlock(&read_mutex);
    	sleep(SLEEP_DELAY);
    }
    pthread_exit(NULL);
}
