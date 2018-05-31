#include "inventory.h"

int* readInventoryInfo(drink* all_drink, int max_drink){
  int* countPerDrink  = (int *)malloc(max_drink * sizeof(int)) ;
  if( countPerDrink == NULL){
    throwMallocException();
  }
  int i = 0, tmp_count; 
  FILE *f = fopen(INVENTORY_INFO_FILENAME, "r");
  if (f == NULL){
    for (i = 0; i < max_drink; i++)
      countPerDrink[i] = 0;
    return countPerDrink;
  }
  char nameDrink[BASE_LENGTH]; // su dung brand nhu 1 dinh danh ?
  while (i < max_drink){
    fscanf(f, "%s\t%d\n", nameDrink, &tmp_count);
    countPerDrink[brand2no(all_drink, max_drink, nameDrink)] = tmp_count; // id_drink > max_len ?
    i++;
  }
  fclose(f);
  return countPerDrink;
}

void writeInventoryInfo(drink* all_drink, int max_drink, int* figures){
  FILE *f = fopen(INVENTORY_INFO_FILENAME, "w");
  int i = 0;
  while(i < max_drink){
    fprintf(f, "%s\t%d\n", no2brand(all_drink, max_drink, i), figures[i]);
    i++;
  }
  fclose(f);
}

// void writeInventoryInfo(client_info *clt, int* figures){
//   FILE *f = fopen(INVENTORY_INFO_FILENAME, "w");
//   int i = 0;
  
//   while(i < max_drink){
//     fprintf(f, "%s\t%d\n", no2brand(all_drink, max_drink, i), figures[i]);
//     i++;
//   }
//   fclose(f);
// }