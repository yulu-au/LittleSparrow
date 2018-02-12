#include "server.h"
void doit(int fd){
		rio_t rbuffer;
		char buf[MAXLINE], method[MAXLINE],uri[MAXLINE],version[MAXLINE],filename[MAXLINE],cgi[MAXLINE];
		int is_static=0;
		struct stat sbuf;
		// init the buffer of rio
		rio_readinit(&rbuffer, fd);
		//read a line from fd
		rio_readline(&rbuffer, buf, MAXLINE);
		sscanf(buf,"%s %s %s", method, uri, version);
		if(strcmp("GET",method) != 0){
				send_error(fd, "501","Not Implemented");// send what
				return;
		}
		is_static = parseuri(uri,filename,cgi);
		
		if(stat(filename, &sbuf) < 0){
			send_error(fd, "404", "Not Found");
			return;
		}


		if(is_static){// serve static content
				printf("we would serve static content filename: %s cgi: %s\n",filename,cgi);
		}
		else{// serve dynamic content
				printf("we would serve dynamic content filename: %s cgi: %s\n",filename,cgi);
		}
}
