CC=gcc
CFLAGS=-w -pthread

PROGS = s c

all: ${PROGS}

s: server.c drink.c extra.c inventory.c
	$(CC) $(CFLAGS) -o $@ $^ 

c: client.c menu.c drink.c extra.c
	$(CC) $(CFLAGS) -o $@ $^ 

clean: *
	rm -f ${PROGS}

