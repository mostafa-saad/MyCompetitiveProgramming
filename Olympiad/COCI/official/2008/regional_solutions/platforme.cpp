#include <stdio.h>

int N;
struct { int y, x1, x2; } platforme[100];

int spusti(double x, int y) {
   int rez = 0;
   for ( int i=0; i<N; ++i ) {
      if ( platforme[i].y  < y &&
           platforme[i].x1 < x &&
           platforme[i].x2 > x &&
           platforme[i].y  > rez ) {
         rez = platforme[i].y;
      }
   }
   return rez;
}

int main() {
   scanf( "%d", &N );
   for ( int i=0; i<N; ++i )
      scanf( "%d%d%d", &platforme[i].y, &platforme[i].x1, &platforme[i].x2 );

   int rez = 0;
   for ( int i=0; i<N; ++i ) {
      rez += platforme[i].y - spusti(platforme[i].x1 + 0.5, platforme[i].y);
      rez += platforme[i].y - spusti(platforme[i].x2 - 0.5, platforme[i].y);
   }
   printf( "%d\n", rez );

   return 0;
}
