
/*
  Hrvatsko otvoreno natjecanje iz informatike 2006/2007
  2. kolo - Zadatak R2
  Programski jezik C

  Po definiciji aritmeticke sredine vrijedi s=(r1+r2)/2. Iz te
  jednadzbe slijedi r2=2*s-r1.
*/

#include <stdio.h>

int main(void)
{
   int r1, s;
   scanf("%d%d", &r1, &s);
   printf("%d\n", 2*s-r1);

   return 0;
}
