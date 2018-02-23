#include "server.h"
#include <signal.h>
int open_listenfd(int port){
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

int main(){
	int listenfd,connfd,clientlen;
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
	while(1){
		clientlen = sizeof(clientaddr);
		if((connfd = accept(listenfd,(struct sockaddr*)&clientaddr,&clientlen)) == -1){
				perror("accept");
				exit(1);
		}
		printf("we accept:%s\n",inet_ntoa(clientaddr.sin_addr));
		doit(connfd);
		close(connfd);
	}
}
