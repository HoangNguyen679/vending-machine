#include "inventory.h"

int* readInventoryInfo(drink* all_drink, int max_drink){
  int* countPerDrink  = (int *)malloc(3 * max_drink * sizeof(int)) ;
  if( countPerDrink == NULL){
    throwMallocException();
  }
  int i = 0, tmp_count;
  char a[100], b[100];
  FILE *f = fopen(INVENTORY_INFO_FILENAME, "r");
  if (f == NULL){
    for (i = 0; i < 3 * max_drink; i++)
      countPerDrink[i] = 0;
    return countPerDrink;
  }
  while (i < max_drink * 3){
    fscanf(f, "%s\t%s\t%d\n", a, b, &tmp_count);
    countPerDrink[i] = tmp_count; // id_drink > max_len ?
    i++;
  }
  fclose(f);
  return countPerDrink;
}

void writeInventoryInfo(drink* all_drink, int max_drink, int* figures){
  char* client_str[] = {"VM1", "VM2", "VM3"};
  FILE *f = fopen(INVENTORY_INFO_FILENAME, "w");
  int i = 0;
  while(i < max_drink * 3){
    printf("%d\n", figures[i]);
    int may = i /  3;
    int nhan = i % 3;
    fprintf(f, "%s\t%s\t%d\n", client_str[may], all_drink[nhan].brand, figures[i]);
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
