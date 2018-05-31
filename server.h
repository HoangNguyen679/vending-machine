#include "extra.h"
#include "drink.h"
#include "inventory.h"
#include <sys/ipc.h>
#include <sys/shm.h>

#define MAX_CLIENTS 3

typedef struct {
	char *name;
	int max_drink;
	drink all_drink[20];
} client_info;

void connectMng();
void salesMng(int conn_sock, client_info *);
int equipInfoAccess(int action, int num, client_info *);
void deliveryMng();
void checkForDelivery();
client_info *findClient(char name[]);


