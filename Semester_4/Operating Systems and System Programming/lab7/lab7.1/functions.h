#pragma once
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>

#define RING_BUFFER_LENGTH 10          //длина кольцевого буфера
#define MAX_STR_LEN 80                 //максимальная длина строкового буфера
#define MAX_THREAD_AMOUNT 20
#define SLEEP_DELAY 2

static pthread_mutex_t write_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t read_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t stdout_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t write_cond = PTHREAD_COND_INITIALIZER;
static pthread_cond_t read_cond = PTHREAD_COND_INITIALIZER;

struct consumer {
	int active;
	pthread_t thread;
};

struct producer {
	int active;
	pthread_t thread;
};

static struct consumer consumer_threads[MAX_THREAD_AMOUNT];
static struct producer producer_threads[MAX_THREAD_AMOUNT];
static int producer_number = 0;        //номер производителя
static int consumer_number = 0;        //номер потребителя

static struct ring_buffer queue;

// структура сообщения
struct message {
	char type;
	unsigned short hash;
	int size;
	int data[256];
};

// структура кольцевого буфера 
struct ring_buffer{
	struct message *buffer;
	int read_index;
	int write_index;
	int size;
	int full;
	int empty;
	int push_msg;
	int pop_msg;
};

void instructions();
int rand_generator();
struct message init_msg();
void init_ring_buffer(struct ring_buffer* queue);
void push_msg(struct ring_buffer* ptr_info, struct message msg);
struct message pop_msg(struct ring_buffer* ptr_info);
