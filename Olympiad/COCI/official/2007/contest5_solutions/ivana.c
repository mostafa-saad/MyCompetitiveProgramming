
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 5 - Task IVANA
  Programming language C
*/

#include <stdio.h>

#define MAXN 100

int max( int a, int b ) { return a>b ? a : b; }

int main()
{
   int n, i, L;
   static int f[2*MAXN][2*MAXN];
   int rj;

   scanf( "%d", &n );

   for ( i=0; i<n; ++i ) {
      int x;
      scanf( "%d", &x );
      x %= 2;
      f[i+n][i+n] = f[i][i] = x;
   }

   for ( L=2; L<=n; ++L )
      for ( i=0; i<2*n; ++i ) {
         int j = i+L-1;
         if ( j>=2*n ) break;

         f[i][j] = max( f[i][i] - f[i+1][j], f[j][j] - f[i][j-1] );
      }

   rj = 0;
   for ( i=0; i<n; ++i )
      if ( f[i][i] - f[i+1][i+n-1] > 0 )
         ++rj;
   printf( "%d\n", rj );

   return 0;
}
