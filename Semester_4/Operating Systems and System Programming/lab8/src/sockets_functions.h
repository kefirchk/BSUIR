#ifndef SOCKETS_FUNCTIONS_H
#define SOCKETS_FUNCTIONS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "config.h"

int Socket(int domain, int type, int protocol);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Inet_pton(int af, const char *src, void *dst);
void recv_file(int* sock, const char* file_to_get);
void send_file(int* sock, const char* file_name);

#endif //SOCKETS_FUNCTIONS_H
