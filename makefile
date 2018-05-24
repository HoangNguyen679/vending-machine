CC=gcc
CFLAGS=-w 

PROGS = s c

all: ${PROGS}

s: server.c 
	$(CC) $(CFLAGS) -o $@ $^ 

c: client.c menu.c 
	$(CC) $(CFLAGS) -o $@ $^ 

clean: *
	rm -f ${PROGS}

