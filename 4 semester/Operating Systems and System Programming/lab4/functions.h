#pragma once
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/wait.h>

#define RING_BUFFER_LENGTH 10          //длина кольцевого буфера
#define MAX_STR_LEN 80                 //максимальная длина строкового буфера
#define MAX_SIZE_NAME 80               //максимальная длина имени процесса
#define PRODUCER_PARTNAME "Producer_"  //часть имени процесса производителя
#define CONSUMER_PARTNAME "Consumer_"  //часть имени процесса потребителя

static key_t sem_key = 111;            //ключ для семафора
static key_t shm_key = 333;            //ключ для общей памяти

static pid_t* producer_pids = NULL;    //массив производителей
static pid_t* consumer_pids = NULL;    //массив потребителей
static int producer_number = 0;        //номер производителя
static int consumer_number = 0;        //номер потребителя


enum SEM_INDEXES {
	R_SEM = 0,       // read from ring buffer
	W_SEM = 1,       // write to the ring buffer
	STDOUT_SEM = 2   // write to the stdout
};


union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};

// структура сообщения
struct message {
	char type;
	unsigned short hash;
	int size;
	int data[256];
};

// структура кольцевого буфера 
struct ring_buffer{
	struct message buffer[RING_BUFFER_LENGTH];
	int read_index;
	int write_index;
	int size;
	int full;
	int empty;
	int push_msg;
	int pop_msg;
};



// Producer's and Consumer's functions:
void set_producer_name(char** name, int number);
void set_consumer_name(char** name, int number);
void add_producer();
void add_consumer();
void kill_producer();
void kill_consumer();
void kill_all_producers();
void kill_all_consumers();



// memory functions:
char* get_str_mem(int size);
int create_shm(key_t key, int size);
void delete_shm(int shm_id);
void* attach_shm(int shm_id, void* ptr);
void detach_shm(void* ptr);




// additional functions:
void instructions();
void list_of_processes();
int rand_generator();



// semaphores:
int create_sem(key_t key, int sem_num);
void delete_sem(int sem_id);
void set_sem_val(int sem_id, int sem_num);
void manage_sem(int sem_id, int sem_num, int value);



// ring buffer:
struct message init_msg();
void init_ring_buffer(struct ring_buffer* ptr_info);
void push_msg(struct ring_buffer* ptr_info, struct message msg);
struct message pop_msg(struct ring_buffer* ptr_info);


