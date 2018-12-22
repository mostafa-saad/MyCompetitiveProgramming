
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 3 - Task TROJKE
  Programming language C++
*/

#include <cstdio>

char a[100][100+1];

int n, m;
int x[26], y[26];

int main( void ) {
   scanf( "%d", &n );

   for( int i = 0; i < n; ++i ) {
      scanf( "%s", a[i] );
      for( int j = 0; j < n; ++j ) {
         if( a[i][j] == '.' ) continue;
         x[m] = i;
         y[m] = j;
         ++m;
      }
   }

   int rjesenje = 0;

   for( int i = 0; i < m; ++i )
      for( int j = i+1; j < m; ++j )
         for( int k = j+1; k < m; ++k )
            if( x[i]*(y[j]-y[k]) + x[j]*(y[k]-y[i]) + x[k]*(y[i]-y[j]) == 0 )
               ++rjesenje;

   printf( "%d\n", rjesenje );

   return 0;
}
