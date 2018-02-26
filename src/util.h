#ifndef _UTIL_H_

#define _UTIL_H_

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
#include <signal.h>
#include <sys/epoll.h>
#define PORT 80
#define MAXLINE 4096
#define MAXEVENTS 1024

void doit(int fd);

#endif
