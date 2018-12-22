
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 4 - Task JOGURT
  Programming language C++
*/

#include <cstdio>

#define maxt (1<<15)

int t, sol[maxt], depth[maxt]; // sol pamti stablo u preorderu, depth pamti dubinu nekog cvora

void next( int d ) {
   for( int i = t; i > 0; i-- ) { // kopiranje stabla dvaput
      sol[t+i] = sol[i] = sol[i-1]*2;
      depth[t+i] = depth[i] = depth[i-1]+1;
   }
   for( int i = 1; i <= t+t; i++ ) // dodavanje jedinice nekim elementima
      if( (depth[i]==d)^(i<=t) ) sol[i]++;

   sol[0] = 1; // dodavanje korijena
   depth[0] = 0;
   t = t+t+1; // stablo je sad dvaput vece
}

int main(void) {
   depth[0] = 0; // inicijalizacija, stablo ima samo jedan element
   sol[0] = t = 1;

   int n;
   scanf( "%d", &n );

   for( int i = 1; i < n; i++ ) next( i ); // udvostruci stablo n puta

   for( int i = 0; i < t; i++ ) printf( "%d ", sol[i] ); // ispisi rjesenje

   return 0;
}
