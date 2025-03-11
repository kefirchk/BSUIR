#include "sockets_functions.h"

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}

void Listen(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);
    if (res == -1) {
        perror("Listen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Accept failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    return res;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Connect failed");
        close(sockfd);
    }
    return res;
}

void Inet_pton(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        perror("Inet_pton failed: src does not contain a character"
               " string representing a valid network address in the specified"
               " address family\n");
        exit(EXIT_FAILURE);
    }
    if (res == -1) {
        perror("Inet_pton failed");
        exit(EXIT_FAILURE);
    }
}


//отправка файла
void send_file(int* sock, const char* file_name)
{
	FILE* file;
	file = fopen(file_name, "rb");
	if(file == NULL)
	{
		perror("memory allocation");
		exit(EXIT_FAILURE);
	}
	
	fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    rewind(file);
	
    char* bytes = (char*)malloc(file_size * sizeof(char));
	
	fread(bytes, sizeof(char), file_size, file);
	
	char file_size_str[16] = "";
	sprintf(file_size_str, "%d", file_size);
	
	
    send(*sock, file_size_str, 16, 0);
    send(*sock, bytes, file_size, 0);

    free(bytes);
    fclose(file);
}

//получение файла
void recv_file(int* sock, const char* file_to_get){

    char file_size_str[MAX_SIZE_INT_STR];

    recv(*sock, file_size_str, 16, 0);
    int file_size = atoi(file_size_str);
    char* bytes = (char*)malloc(file_size*sizeof(char));

	FILE* file;
	file = fopen(file_to_get, "wb");
	if(file == NULL)
	{
		perror("memory allocation");
		exit(EXIT_FAILURE);
	}
	
	recv(*sock, bytes, file_size, MSG_WAITALL);
    fwrite(bytes, sizeof(char), file_size, file);
	
    free(bytes);
    fclose(file);
}




