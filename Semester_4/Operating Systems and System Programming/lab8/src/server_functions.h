#define _GNU_SOURCE

#include <stdbool.h>
#include <pthread.h>    //for threading , link with lpthread
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#include "sockets_functions.h"

int what_to_do(char* message);
void instructions();
int read_directory(char*** result);
void add_to_file_names(char*** result, int size, char* path);
char* determine_type(const char* filename);
char* change_dir(char* root_dir, char* new_dir); 

enum COMMAND {
	NOT_COMMAND = -1,
	QUIT = 0,
	ECHO = 1,
	INFO = 2,
	LIST = 3,
	CD = 4,
	FILE_COMMAND = 5
};

struct client {  // Параметры очередного клиента в потоке
    
    int sock;
    struct sockaddr_in client_addr;
    int id;
    bool is_closed;
};

static int thread_size = 0;                               // количество текущих потоков (клиентов)
static struct client connected_clients[MAX_CLIENT_SIZE];  // массив клиентов с параметрами
static pthread_t client_threads[MAX_CLIENT_SIZE];         // потоки клиентов
static int sockfd;
