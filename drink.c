#include "drink.h"

void
readDrinkInfo(drink all_drink[20], int *max_drink)
{
  FILE *f = fopen("drink.txt", "r");
  int i = 0;
  while(!feof(f))
    {
      fscanf(f,"%d %s %d",
	     &all_drink[i].no,
	     all_drink[i].brand,
	     &all_drink[i].price);
      i++;
    }

  *max_drink = i;
  
}



char *
no2brand(drink all_drink[20],int max_drink, int no)
{
  for(int i = 0; i < max_drink; i++)
    {
      if(all_drink[i].no == no)
	{
	  return all_drink[i].brand;
	}
    }
  
  return NULL;
}



