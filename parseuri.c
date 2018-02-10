#include "server.h"
int parseuri(char *uri, char *filename, char *cgiargs){
	int is_static=1;
	if(!strstr(uri,"cgi-bin")){/*static content*/
		strcpy(cgiargs,"");
		strcpy(filename,".");
		strcat(filename,uri);
		int uri_len=strlen(uri);
		if(uri[uri_len-1] == '/')
			strcat(filename,"home.html");
		return is_static;
	}
	else{/* dynamic content*/
		char *ptr = index(uri,'?');
		if(ptr){
			strcpy(cgiargs,ptr+1);
			*ptr = '\0';
		}
		else{
			strcpy(cgiargs,"");
		}
		strcpy(filename,".");
		strcat(filename,uri);
		return is_static-1;
	}
}
