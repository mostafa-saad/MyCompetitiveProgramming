
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 1 - Task MODULO
  Programming language C
*/

#include <stdio.h>

int main() {
   int i, sol = 0;
   int mods[42] = {0};

   for ( i=0; i<10; ++i ) {
      int x;
      scanf( "%d", &x );
      mods[ x%42 ] = 1;
   }
   for ( i=0; i<42; ++i )
      sol += mods[i];

   printf( "%d\n", sol );

   return 0;
}
