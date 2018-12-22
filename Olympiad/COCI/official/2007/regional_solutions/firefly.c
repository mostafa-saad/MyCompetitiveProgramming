
/*
  Croatian Regional Competition in Informatics 2007
  Task FIREFLY
  Programming language C
*/

#include <stdio.h>

#define MAXH 500000

int main()
{
   int N, H, i;
   static int gore[MAXH+1], dolje[MAXH+1];
   int rj1, rj2;

   scanf( "%d%d", &N, &H );
   for ( i=0; i<=H; ++i )
      gore[i] = dolje[i] = 0;

   for ( i=0; i<N; ++i ) {
      int x;
      scanf( "%d", &x );
      if ( i%2 == 0 )
         ++dolje[x];
      else
         ++gore[x];
   }

   for ( i=H-2; i>0; --i ) {
      gore[i] += gore[i+1];
      dolje[i] += dolje[i+1];
   }

   rj1 = N+1; rj2 = -1;
   for ( i=1; i<=H; ++i ) {
      int rusi = dolje[i] + gore[H-i+1];
      if ( rusi < rj1 ) {
         rj1 = rusi;
         rj2 = 1;
      }
      else if ( rusi == rj1 )
         ++rj2;
   }

   printf( "%d %d\n", rj1, rj2 );

   return 0;
}
