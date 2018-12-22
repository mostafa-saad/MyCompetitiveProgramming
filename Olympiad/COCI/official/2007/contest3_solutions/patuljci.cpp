
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 3 - Task PATULJCI
  Programming language C++
*/

#include <cstdio>

int main( void ) {
   int broj[9];

   int suma = 0;
   for( int i = 0; i < 9; ++i ) {
      scanf( "%d", &broj[i] );
      suma += broj[i];
   }

   for( int i = 0; i < 9; ++i )
      for( int j = i+1; j < 9; ++j )
         if( suma - broj[i] - broj[j] == 100 )
            for( int k = 0; k < 9; ++k )
               if( k != i && k != j )
                  printf( "%d\n", broj[k] );

   return 0;
}
