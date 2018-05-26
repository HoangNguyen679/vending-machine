#include "extra.h"
#include "drink.h"
#include "inventory.h"
#include <sys/ipc.h>
#include <sys/shm.h>

void connectMng();
void salesMng(int conn_sock);
int equipInfoAccess(int action, int num);
void deliveryMng();
void checkForDelivery();


