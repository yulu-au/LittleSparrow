#include "util.h"
#include "log.h"
#include "rio.h"

int rio_write(int fd,char *buf,int len){
		int nleft=len,writed=0;
		char *ptr=buf;
		while(nleft > 0){
				writed = write(fd,ptr,nleft);
				if(writed <= 0){
						if(writed < 0 && errno == EINTR)
								writed = 0;
						else{
								logerror("write",errno);
								return -1;

						}
				}
				nleft = nleft - writed;
				ptr = ptr + writed;
		}
		return len;
}

void rio_readinit(rio_t *r, int fd){
		r->fd = fd;
		r->unread_size = 0;
		r->pcurrent = r->buf;
		r->size = MAXLINE;
}

int rio_readline(rio_t *r, char *buf, int max_size){
		if(0 == r->unread_size){
				int nleft = r->size ,r_v = 0;
				char *ptr = r->pcurrent;
				while(nleft >0){
						r_v = read(r->fd, ptr, nleft);
						if(-1 == r_v && errno == EINTR){
								continue;
						}
						else if(-1 == r_v && errno == EAGAIN){
								break;
						}
						else if(-1 == r_v)
								return -1;
						if(0 == r_v)
								break;
						nleft -= r_v;
						ptr += r_v;
						r->unread_size += r_v;
				}
				if(0 == r->unread_size)
						return 0;
		}
		int limit=0,count=0;
		char *ptr = r->pcurrent;
 		if(max_size > r->unread_size)
				limit = r->unread_size;
		else 
				limit = max_size;
		while(count < limit && *(ptr)!= '\n'){
				*(buf+count) = *ptr;
				++ptr;
				++count;
		}
		if('\n' == *ptr && count < limit)
				*(buf+count) = '\n';
		r->pcurrent += count;
		r->unread_size -= count;
		return count;
}
