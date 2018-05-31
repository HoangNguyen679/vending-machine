#include "extra.h"
#include "drink.h"

#define INVENTORY_INFO_FILENAME "inventoryInfo.txt"

int* readInventoryInfo(drink* all_drink, int max_drink);
void writeInventoryInfo(drink* all_drink, int max_drink, int* figures);
