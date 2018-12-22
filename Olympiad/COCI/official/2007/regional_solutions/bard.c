
/*
  Croatian Regional Competition in Informatics 2007
  Task BARD
  Programming language C
*/

#include <stdio.h>
#include <string.h>

#define MAXN 100
#define MAXV 50

int main()
{
   int N, V, i;
   int npjesama = 0;
   int zna[MAXN+1][MAXV];

   scanf( "%d", &N );
   scanf( "%d", &V );

   for ( i=0; i<V; ++i ) {
      int j, k;
      int veceras;
      int prisutan[MAXN+1];
      int pjevase[MAXV];

      for ( j=1; j<=N; ++j )
         prisutan[j] = 0;
      for ( j=0; j<npjesama; ++j )
         pjevase[j] = 0;

      scanf( "%d", &veceras );
      for ( j=0; j<veceras; ++j ) {
         int tko;
         scanf( "%d", &tko );
         prisutan[tko] = 1;
      }

      if ( prisutan[1] ) {
         pjevase[npjesama++] = 1;
      }
      else {
         for ( j=0; j<npjesama; ++j )
            for ( k=1; k<=N; ++k )
               pjevase[j] |= prisutan[k] && zna[k][j];
      }

      for ( k=1; k<=N; ++k )
         for ( j=0; j<npjesama; ++j )
            zna[k][j] |= prisutan[k] && pjevase[j];
   }

   for ( i=1; i<=N; ++i ) {
      int j, znasve = 1;
      for ( j=0; j<npjesama; ++j )
         znasve &= zna[i][j];
      if ( znasve )
         printf( "%d\n", i );
   }

   return 0;
}
