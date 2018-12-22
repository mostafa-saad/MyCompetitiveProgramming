
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 5 - Task TRIK
  Programming language C
*/

#include <stdio.h>

int main()
{
   char s[51];
   int gdje = 1, i;
   scanf( "%s", s );

   for ( i=0; s[i]!='\0'; ++i ) {
      if      ( s[i] == 'A' && gdje != 3 ) gdje = 3-gdje;
      else if ( s[i] == 'B' && gdje != 1 ) gdje = 5-gdje;
      else if ( s[i] == 'C' && gdje != 2 ) gdje = 4-gdje;
   }

   printf( "%d\n", gdje );

   return 0;
}
