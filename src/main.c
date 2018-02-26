#include "util.h"
#include "log.h"

static int open_listenfd(int);
static int make_socket_noblocking(int); 

int main(){
	int listenfd,connfd,clientlen;
	int efd,s;
	struct sockaddr_in clientaddr;

	struct sigaction sa;
	memset(&sa,'\0',sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	if(sigaction(SIGPIPE,&sa,NULL)){
			logerror("sig",errno);
			return -1;
	}

	if((listenfd = open_listenfd(PORT)) == -1){
			perror("open_listenfd");
			exit(1);
	}

	//init epoll
	struct epoll_event event;
	struct epoll_event events[MAXEVENTS];

	efd = epoll_create1(0);
	if(efd == -1){
			perror("epoll_create");
			exit(1);
	}
	event.data.fd = listenfd;
	event.events = EPOLLIN;
	s = epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&event);
	if(s == -1){
			perror("epoll_ctl");
			exit(1);
	}
	
	while(1){
			int count = epoll_wait(efd,events,MAXEVENTS,-1);
			if(count == -1){
					perror("epoll_wait");
					exit(1);
			}
			for(int i=0;i<count;i++){
					if(events[i].data.fd == listenfd){
							clientlen = sizeof(clientaddr);
							if((connfd = accept(listenfd, (struct sockaddr*)&clientaddr,&clientlen)) == -1){
									perror("accept");
									exit(1);
							}
							make_socket_noblocking(connfd);
							event.events = EPOLLIN | EPOLLET;
							event.data.fd = connfd;
							if(epoll_ctl(efd,EPOLL_CTL_ADD,connfd,&event) < 0){
									perror("add connfd to epoll");
									exit(1);
							}

					}
					else{
							doit(events[i].data.fd);

					}

			}
	}

}

static int open_listenfd(int port){
		int fd;
		struct sockaddr_in my_addr;
		if((fd = socket(AF_INET,SOCK_STREAM,0)) == -1){
				perror("socket");
				return -1;
		}
		my_addr.sin_family = AF_INET;
		my_addr.sin_port = htons(port);
		my_addr.sin_addr.s_addr = INADDR_ANY;
		bzero(&(my_addr.sin_zero),8);
		if(bind(fd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr)) == -1){
				perror("bind");
				return -1;
		}
		if(listen(fd,5) == -1){
				perror("listen");
				return -1;
		}
		return fd;

}



static int make_socket_noblocking(int fd){
		int flags,s;
		flags=fcntl(fd,F_GETFL,0);
		if(flags == -1){
				perror("fcntl");
				return -1;
		}
		flags |= O_NONBLOCK;
		s = fcntl(fd,F_SETFL,flags);
		if(s == -1){
				perror("fcntl");
				return -1;
		}
		return 0;
}
