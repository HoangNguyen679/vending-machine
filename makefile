CC=gcc
CFLAGS=-w 

PROGS = s c

all: ${PROGS}

s: server.c drink.c
	$(CC) $(CFLAGS) -o $@ $^ 

c: client.c menu.c drink.c 
	$(CC) $(CFLAGS) -o $@ $^ 

clean: *
	rm -f ${PROGS}

