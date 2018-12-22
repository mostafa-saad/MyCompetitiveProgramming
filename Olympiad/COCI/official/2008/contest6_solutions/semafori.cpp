#include <cstdio>

int main( void ) {
   int N, D;
   scanf( "%d%d", &N, &D );

   int x = 0, t = 0;
   for( int i = 0; i < N; ++i ) {
      int L, C, Z;
      scanf( "%d%d%d", &L, &C, &Z );
      t += L-x;
      x = L;
      while( t % (C+Z) < C ) ++t;
   }
   t += D-x;
   x = D;

   printf( "%d\n", t );

   return 0;
}
