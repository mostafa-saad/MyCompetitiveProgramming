
/*
  Hrvatsko otvoreno natjecanje iz informatike 2006/2007
  2. kolo - Zadatak ABC
  Programski jezik C

  Ucitamo brojeve A, B i C te odredimo pravilan redoslijed sa tri
  usporedbe i zamjenama po potrebi.

  Zatim ucitamo trazeni redoslijed, brojeve A, B i C stavimo u
  pomocni niz u trazenom redoslijedu te ispisemo pomocni niz.
*/

#include <stdio.h>

int main(void)
{
   int a, b, c, t;
   char str[4];
   int i, izlaz[3];

   scanf( "%d%d%d", &a, &b, &c );
   if ( a > b ) { t = a; a = b; b = t; }
   if ( a > c ) { t = a; a = c; c = t; }
   if ( b > c ) { t = b; b = c; c = t; }

   scanf( "%s", str );
   for ( i=0; i<3; ++i ) {
      if      ( str[i] == 'A' ) izlaz[i] = a;
      else if ( str[i] == 'B' ) izlaz[i] = b;
      else if ( str[i] == 'C' ) izlaz[i] = c;
   }
   printf( "%d %d %d\n", izlaz[0], izlaz[1], izlaz[2] );

   return 0;
}
