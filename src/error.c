#include "util.h"
#include "error.h"
#include "rio.h"

void send_error(int fd,char *er_num,char *msg){
		char buf[MAXLINE],body[MAXLINE];
		//send response headers
		sprintf(buf,"HTTP/1.1 %s %s\r\n",er_num,msg);
		rio_write(fd,buf,strlen(buf));
		sprintf(buf,"Content-type: text/html\r\n");
		rio_write(fd,buf,strlen(buf));
		//need to send length of body so
		sprintf(body,"<html><title>error</title>");
		sprintf(body,"%s<body>\r\n<h1>error</h1>\r\n</body>\r\n</html>",body);
		sprintf(buf,"Content-length: %d\r\n\r\n",(int)strlen(body));
		rio_write(fd,buf,strlen(buf));
		rio_write(fd,body,strlen(body));
}
