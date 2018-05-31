//#include "naming.h"
#include "extra.h"
#include "drink.h"



#define INVENTORY_INFO_FILENAME "inventoryInfo.txt"

int* readInventoryInfo(drink* all_drink, int max_drink);
void writeInventoryInfo(drink* all_drink, int max_drink, int* figures);
/*
#define MAX_CLIENTS 3

typedef struct _client_info {
	char *name;
} client_info;


client_info client_set[] = {
  { .name = "VM1" },
  { .name = "VM2" },
  { .name = "VM3" }
};
*/
