server: main.o doit.o error.o rio.o parseuri.o serveContent.o
	gcc -o ./bin/server main.o doit.o error.o rio.o parseuri.o serveContent.o
	rm *.o
main.o: main.c server.h
	gcc -c -g main.c
doit.o: doit.c server.h
	gcc -c -g doit.c
error.o: error.c server.h
	gcc -c -g error.c
rio.o: rio.c server.h
	gcc -c -g rio.c
parseuri.o: parseuri.c server.h
	gcc -c -g parseuri.c
serveContent.o: serveContent.c server.h
	gcc -c -g serveContent.c

.PHONY: clean
clean:
	rm -f ./bin/server
