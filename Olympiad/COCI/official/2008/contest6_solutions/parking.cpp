#include <cstdio>

int cijena[4];
int koliko[100];

int main( void ) {
   for( int i = 1; i <= 3; ++i ) scanf( "%d", &cijena[i] );
   for( int i = 1; i <= 3; ++i ) {
      int t1, t2;
      scanf( "%d%d", &t1, &t2 );
      for( int t = t1; t < t2; ++t ) ++koliko[t];
   }

   int ukupno = 0;
   for( int t = 0; t < 100; ++t ) ukupno += koliko[t] * cijena[koliko[t]];
   printf( "%d\n", ukupno );

   return 0;
}
