#ifndef _SERVER_H_

#define _SERVER_H_
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#define PORT 80
#define MAXLINE 4096
//void doit(int);
//void send_error(int,char*,char*);

//int parseuri(char*, char*, char*);

typedef struct {
		int fd;
		char buf[MAXLINE];
		char *pcurrent;
		int unread_size;
		int size;

} rio_t;
#endif
