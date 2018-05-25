#ifndef DRINK_H
#define DRINK_H

#include <stdio.h>
#include <string.h>

typedef
struct _drink
{
  int no;
  char brand[30]; // ten ?
  int price;
} drink;

void readDrinkInfo(drink all_drink[20],int *max_drink);
char *no2brand(drink all_drink[20], int max_drink, int no);
int brand2no(drink all_drink[20], int max_drink, char* brand);

#endif
