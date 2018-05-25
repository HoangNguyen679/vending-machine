#ifndef EXTRA_H
#define EXTRA_H
#include "lib.h"

void va_cli(int argc, char *argv[],
	    char *server_ip, int *server_port);

void va_ser(int argc, char *argv[], int *port);

void sig_chld(int signo);

void throwMallocException();
/*
 * check argument valid in client 
 */

#endif
