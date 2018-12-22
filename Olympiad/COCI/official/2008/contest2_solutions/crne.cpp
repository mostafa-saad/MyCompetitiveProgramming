#include <cstdio>

int main( void ) {
   int n;
   scanf( "%d", &n );

   int h = n/2;
   int v = n-h;

   printf( "%d\n", (h+1)*(v+1) );

   return 0;
}
