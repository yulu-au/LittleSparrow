#ifndef _RIO_H
#define _RIO_H

typedef struct {
		int fd;
		char buf[MAXLINE];
		char *pcurrent;
		int unread_size;
		int size;

} rio_t;

int rio_write(int fd,char *buf,int len);

void rio_readinit(rio_t *r, int fd);

int rio_readline(rio_t *r, char *buf, int max_size);

#endif

