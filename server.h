#include "inventory.h"
#include <sys/ipc.h>
#include <sys/shm.h>

#define MAX_CLIENTS 3

typedef struct _client_info {
	char *name;
} client_info;


client_info client_set[] = {
  { .name = "VM1" },
  { .name = "VM2" },
  { .name = "VM3" }
};

int clientName2id(char *name){
  int i = 0;
  for (i = 0; i < MAX_CLIENTS; i++){
    if(strcmp(name, client_set[i].name) == 0)
      return i;
  }
  return -1;
}

void connectMng();
void salesMng(int conn_sock, client_info *clt);
int equipInfoAccess(int action, int num, client_info *clt);
void deliveryMng(int conn_sock,int num);
void checkForDelivery(client_info *clt, int conn_sock);
client_info *findClient(char name[]);


