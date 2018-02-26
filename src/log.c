#include "util.h"
#include "log.h"

void logerror(char *buf, int e){
		FILE *fp;
		fp = fopen("log.txt","a");
		if(NULL == fp){
				perror("log");
				return;
		}
		fprintf(fp,"where: %s why: %s \n", buf, strerror(e));
		fclose(fp);
}
