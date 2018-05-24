#include "menu.h"

void
menu_home()
{
  printf("-------------------------\n");
  printf("--  Danh sách đồ uống: --"
	 "\n\n");
  printf("-- 1.  Pepsi           --\n"  
	 "-- 2.  Coca            --\n"
	 "-- 3.  Lala            --\n"
	 "-- 4. Quit             --\n");
  printf("-------------------------\n");
  printf("Your choice: ");
}

void 
menu_bye()
{
  printf("Bye\n");
}
