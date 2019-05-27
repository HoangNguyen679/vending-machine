/*
 * primary lib
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/*
 * socket - system lib
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/msg.h>
#include <sys/ipc.h>

/*
 * database lib
 * 
 * #include <mysql.h>
 */

#include <netdb.h>


/*
 * signal - error
 */

#include <errno.h>
#
#include <signal.h>
#include <termios.h>


/*
 * define size 
 */

#define HUGE_BUFF_SIZE 8192
#define BUFF_SIZE      2048
#define BASE_LENGTH	256

#define BACKLOG 10   // Number of allowed connections

/*
 * file data name
 */

#define salesHistory  "salesHistory.txt"


