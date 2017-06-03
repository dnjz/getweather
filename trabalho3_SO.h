#ifndef trabalho3_SO_H
#define trabalho3_SO_H
#include "myinet.h"
#include "errorUtils.h"
#include <pthread.h>
#include "trabalho2_SO.h"

typedef struct {
     int sockfd;
     char buffer[DIM_BUFFER+1];              
} socket_t;

socket_t *socket_init_server(int port);

socket_t *socket_init_client(char *host, int port);

socket_t *socket_accept(socket_t *passiveSocket);

int socket_close(socket_t *socket);

int socket_read(socket_t *socket, char *buf, ssize_t size);

int socket_write(socket_t *socket, char *buf, ssize_t size);


#endif
