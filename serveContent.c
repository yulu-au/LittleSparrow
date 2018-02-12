void serve_static(int fd, char *filename, int filesize){
		char filetype[1024],buf[MAXLINE];
		int file = 0;
		char *src;

		get_file_type(filename, filetype);

		sprintf(buf,"HTTP/1.1 200 ok\r\n");
		sprintf(buf,"%sServer: toy server \r\n",buf);
		sprintf(buf,"%sContent-length: %d\r\n",buf,filesize);
		sprintf(buf,"%sContent-type: %s\r\n\r\n",buf,filetype);
		rio_write(fd, buf, strlen(buf));
		
		file = open(filename, O_RDONLY, 0);
		if(-1 == file){
				perror("open");
				return;
		}
		src = mmap(0, filesize, PORT_READ, MAP_PRIVATE, file, 0);
		if(src == (void*)-1){
				perror("mmap");
				return;
		}
		close(fd);
		rio_write(fd, src, filesize);
		munmap(src, filesize);
}

void serve_dynamic(int fd, char *filename, char *cgi){


}

void get_file_type(char *filename, char *type){
		if(strstr(filename, ".html"))
				strcpy(type, "text/html");
		else if(strstr(filename, ".gif"))
				strcpy(type, "image/gif");
		else if(strstr(filename, ".jpg"))
				strcpy(type, "image/jepg");
		else
				strcpy(type, "text/plain");
}
