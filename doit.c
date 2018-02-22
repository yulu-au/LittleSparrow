#include "server.h"

static int make_socket_noblocking(int);

void doit(int fd){
		rio_t rbuffer;
		char buf[MAXLINE], method[MAXLINE],uri[MAXLINE],version[MAXLINE],filename[MAXLINE],cgi[MAXLINE];
		int is_static=0;
		struct stat sbuf;
		make_socket_noblocking(fd);
		// init the buffer of rio
		rio_readinit(&rbuffer, fd);
		//read a line from fd
		rio_readline(&rbuffer, buf, MAXLINE);
		sscanf(buf,"%s %s %s", method, uri, version);
		if(strcmp("GET",method) != 0){
				send_error(fd, "501","Not Implemented");// send what
				logerror("501",errno);
				return;
		}
		is_static = parseuri(uri,filename,cgi);
		
		if(stat(filename, &sbuf) < 0){
			send_error(fd, "404", "Not Found");
			logerror("not found file",errno);
			return;
		}

		
		if(is_static){// serve static content
				if(!(S_ISREG(sbuf.st_mode))||!(S_IRUSR & sbuf.st_mode)){
						send_error(fd, "403", "Forbidden");
						logerror("forbidden",errno);
						return;
				}
				logerror("server_static",errno);
				serve_static(fd, filename, sbuf.st_size);
				printf("we would serve static content filename: %s cgi: %s\n",filename,cgi);
		}
		else{// serve dynamic content
				if(!(S_ISREG(sbuf.st_mode))||!(S_IXUSR & sbuf.st_mode)){
						 send_error(fd, "403", "Forbidden"); 
						 return;                 
				}
				//printf("we would serve dynamic content filename: %s cgi: %s\n",filename,cgi);
				send_error(fd, "501", "Not Implemented");
		}
}

static make_socket_noblocking(int fd){
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
