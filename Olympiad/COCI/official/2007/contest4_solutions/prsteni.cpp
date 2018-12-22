
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 4 - Task PRSTENI
  Programming language C++
*/

#include <cstdio>

int gcd( int a, int b ) { return b != 0 ? gcd( b, a%b ) : a; } // najveca zajednicka mjera od a i b

int main(void) {
   int n, first, k;
   scanf( "%d%d", &n, &first );
   for( int i = 0; i < n-1; i++ ) {
      scanf( "%d", &k );
      printf( "%d/%d\n", first/gcd( first, k ), k/gcd( first, k ) );
   }
   return 0;
}
