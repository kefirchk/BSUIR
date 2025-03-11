#include "functions.h"


//---------------------------------------------
// Producer's functions:
//---------------------------------------------
void set_producer_name(char** name, int number)
{
	strcpy(*name, PRODUCER_PARTNAME);
	char number_str[3] = "";
	sprintf(number_str, "%u", number);
	strcat(*name, number_str);
}


void add_producer()
{
	char* producer_name = get_str_mem(MAX_SIZE_NAME); //имя процесса производителя
	pid_t new_pid = fork();
    if (new_pid) {
    	++producer_number;
        producer_pids = (pid_t*)realloc(producer_pids, producer_number*sizeof(pid_t));
        producer_pids[producer_number - 1] = new_pid;
        printf("Producer_%d has been created, pid=%d\n", producer_number, new_pid);
    } else if (new_pid == -1) {
        puts("Error: producer is not created");
    } else {
        set_producer_name(&producer_name, producer_number + 1);
        execl("./producer", producer_name, NULL);
    }
    free(producer_name);
}


void kill_producer()
{
    int status = -1;
    int producer_status;
    if (producer_number > 0) { 
        status = kill(producer_pids[--producer_number], SIGTERM);
        waitpid(producer_pids[producer_number], &producer_status, 0);
        if (status == -1) {
            fprintf(stderr, "error: kill returned -1\n");
            return;
        }
        producer_pids = (pid_t*)realloc(producer_pids, producer_number * sizeof(pid_t));
    } else {
        fprintf(stderr, "error: size of producer's array is zero\n");
        return;
    }
    printf("Producer_%d has been killed\n", producer_number+1);
}


void kill_all_producers() 
{
	for (int i = producer_number; i; --i)
        kill_producer();
    printf("All producers are killed\n");
    free(producer_pids);
    producer_pids = NULL;
}


//---------------------------------------------
// Consumer's functions:
//---------------------------------------------
void set_consumer_name(char** name, int number)
{
	strcpy(*name, CONSUMER_PARTNAME);
	char number_str[3] = "";
	sprintf(number_str, "%u", number);
	strcat(*name, number_str);		
}


void add_consumer()
{
	char* consumer_name = get_str_mem(MAX_SIZE_NAME); //имя процесса производителя
	pid_t new_pid = fork();
    if (new_pid) {
    	++consumer_number;
        consumer_pids = (pid_t*)realloc(consumer_pids, consumer_number*sizeof(pid_t));
        consumer_pids[consumer_number - 1] = new_pid;
        printf("Consumer_%d has been created, pid=%d\n", consumer_number, new_pid);
    } else if (new_pid == -1) {
        puts("Error: consumer is not created");
    } else {
        set_consumer_name(&consumer_name, consumer_number + 1);
        execl("./consumer", consumer_name, NULL);
    }
    free(consumer_name);
}


void kill_consumer()
{
    int status = -1;
    int consumer_status;
    if (consumer_number > 0) { 
        status = kill(consumer_pids[--consumer_number], SIGTERM);
        waitpid(consumer_pids[consumer_number], &consumer_status, 0);
        if (status == -1) {
            fprintf(stderr, "error: kill returned -1\n");
            return;
        }
        consumer_pids = (pid_t*)realloc(consumer_pids, consumer_number * sizeof(pid_t));
    } else {
        fprintf(stderr, "error: size of consumer's array is zero\n");
        return;
    }
    printf("Consumer_%d has been killed\n", consumer_number+1);
}


void kill_all_consumers() 
{
    for (int i = consumer_number; i; --i)
    	kill_consumer();
    printf("All consumers are killed\n");
    free(consumer_pids);
    consumer_pids = NULL;
}


//---------------------------------------------
// Memory:
//---------------------------------------------
char* get_str_mem(int size) {
    char* tmp = (char*)malloc(size*sizeof(char));
    if(tmp == NULL)
    {
    	fprintf(stderr, "Failed to allocate memory");
	exit(EXIT_FAILURE);
    }
    return tmp;
}


int create_shm(key_t key, int size){
    int id = shmget(key, size, 0666 | IPC_CREAT);
    if(id == -1){
    	perror("shmget() ");
	errno = 0;
    }
    return id;
}


void delete_shm(int shm_id){
	struct shmid_ds *buf = NULL;
	errno = 0;
	shmctl(shm_id, IPC_RMID, buf);
	if(errno != 0){
		perror("shmctl() ");
		errno = 0;
	}
}


void* attach_shm(int shm_id, void* ptr){
	errno = 0;
	ptr = shmat(shm_id, NULL, 0);
	if(errno != 0){
		perror("shmat() ");
		errno = 0;
	}
	return ptr;
}


void detach_shm(void* ptr) {
	errno = 0;	
	shmdt(ptr);
	if(errno != 0){
		perror("shmdt() ");
		errno = 0;
	}
}




//---------------------------------------------
// Additionary:
//---------------------------------------------
void list_of_processes()
{
    puts(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	puts("List of processes:");
	puts("----------------------------------------");
	printf("Main process: pid = %d\n", getpid());
	puts("----------------------------------------");
	printf("PRODUCERS[all = %d]:\n", producer_number);
	for(int i = 0; i < producer_number; ++i) {
		printf("Producer_%d, pid=%d\n", i+1, producer_pids[i]);
	}
	puts("----------------------------------------");	
	printf("CONSUMERS[all = %d]:\n", consumer_number);
	for(int i = 0; i < consumer_number; ++i) {
		printf("Consumers_%d, pid=%d\n", i+1, consumer_pids[i]);
	}
    puts("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
}


void instructions()
{
    puts(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    printf("+p -- add producer\n"
           "+c -- add consumer\n"
           "-p -- delete producer\n"
           "-c -- delete consumer\n"
           "l -- list of processes\n"
           "q -- exit\n");
    puts("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
}


int rand_generator() {
	int number;
	do {
		number = rand() % 257;
	} while(number == 0);
	return number;
}





//---------------------------------------------
// Semaphores:
//---------------------------------------------
int create_sem(key_t key, int sem_num){
	errno = 0;
	int id = semget(key, sem_num, 0666 | IPC_CREAT);
	if(errno != 0){
		perror("semget() ");
		errno = 0;
	}
	return id;
}


void delete_sem(int sem_id){
	union semun sem_union;
	errno = 0;
	semctl(sem_id, 0, IPC_RMID, sem_union);
	if(errno != 0){
		perror("semctl() ");
		errno = 0;
	}
}


void set_sem_val(int sem_id, int sem_num){
	union semun sem_union;
	sem_union.val = 1;
	errno = 0;
	semctl(sem_id, sem_num, SETVAL, sem_union);
	if(errno != 0){
		perror("semctl() ");
		errno = 0;
	}
}


void manage_sem(int sem_id, int sem_num, int value){
	struct sembuf sem_buf;
	sem_buf.sem_num = sem_num;
	sem_buf.sem_op = value;
	sem_buf.sem_flg = SEM_UNDO;
	semop(sem_id, &sem_buf, 1);
}





//---------------------------------------------
// Ring buffer:
//---------------------------------------------
struct message init_msg() {
	struct message msg;
	msg.size = rand_generator();
	msg.hash = msg.size;
	for(int i = 0; i < msg.size; i++) {
		msg.data[i] = rand_generator();
		msg.hash += msg.data[i];
	}
	return msg;
}


void init_ring_buffer(struct ring_buffer* buffer_ptr) {
    buffer_ptr->read_index = 0;
    buffer_ptr->write_index = 0;
    buffer_ptr->size = RING_BUFFER_LENGTH;
    buffer_ptr->full = 0;
    buffer_ptr->empty = 1;
    buffer_ptr->push_msg = 0;
    buffer_ptr->pop_msg = 0;
}


void push_msg(struct ring_buffer* buffer_ptr, struct message msg){
	if(buffer_ptr->full != 1) {
		buffer_ptr->buffer[buffer_ptr->write_index] = msg;
		if((buffer_ptr->write_index + 1) == buffer_ptr->size) {
			buffer_ptr->write_index = 0;
		} else {
			buffer_ptr->write_index += 1;
		}
		buffer_ptr->push_msg += 1;
		buffer_ptr->empty = 0;
		
		if(buffer_ptr->write_index == buffer_ptr->read_index){
			buffer_ptr->full = 1;
		}
	}
}


struct message pop_msg(struct ring_buffer* buffer_ptr){
	struct message msg = {0, 0, 0, {0}};
	if(buffer_ptr->empty != 1){
		msg = buffer_ptr->buffer[buffer_ptr->read_index];
		if((buffer_ptr->read_index + 1) == buffer_ptr->size){
			buffer_ptr->read_index = 0;
		} else {
			buffer_ptr->read_index += 1;
		}
		buffer_ptr->pop_msg += 1;
		buffer_ptr->full = 0;
		
		if(buffer_ptr->write_index == buffer_ptr->read_index){
			buffer_ptr->empty = 1;
		}
	}
	return msg;
}


