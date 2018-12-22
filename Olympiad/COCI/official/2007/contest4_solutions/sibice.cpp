
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 4 - Task SIBICE
  Programming language C++
*/

#include <cstdio>

int main(void) {
   int n, w, h, k;
   scanf( "%d%d%d", &n, &w, &h );
   for( int i = 0; i < n; i++ ) {
      scanf( "%d", &k );
      printf( w*w+h*h >= k*k ? "DA\n": "NE\n" );
   }
   return 0;
}
