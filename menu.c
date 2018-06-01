#include "menu.h"

void
menu_home(int* figures)
{
  printf("---------------------------\n");
  printf("--  Danh sách đồ uống:   --\n");
  printf("-- 1.  Pepsi           %2d--\n"  
	 "-- 2.  Coca            %2d--\n"
	 "-- 3.  Lala            %2d--\n"
	 "-- 4.  Quit              --\n", figures[0], figures[1], figures[2]);
  printf("---------------------------\n");
  printf("Your choice: ");
}

void 
menu_bye()
{
  printf("Bye\n");
}
