#include <cstdio>

#define MAXK 1000

int N, K;
int x[MAXK];
int pozicija_r[MAXK], cilj_r[MAXK];
int pozicija_s[MAXK], cilj_s[MAXK];

void rotiraj_redak( int r, int pomak ) {
   for( int i = 0; i < K; ++i ) 
      if( pozicija_r[i] == r ) 
         pozicija_s[i] = (pozicija_s[i] + pomak) % N;
}
void rotiraj_stupac( int s, int pomak ) {
   for( int i = 0; i < K; ++i ) 
      if( pozicija_s[i] == s ) 
         pozicija_r[i] = (pozicija_r[i] + pomak) % N;
}

int main( void ) {
   scanf( "%d%d", &N, &K );
   for( int i = 0; i < K; ++i ) {
      scanf( "%d%d%d", &x[i], &cilj_r[i], &cilj_s[i] ); 
      --x[i];
      --cilj_r[i];
      --cilj_s[i];
      pozicija_r[i] = x[i] / N;
      pozicija_s[i] = x[i] % N;
   }

   for( int i = 0; i < K; ++i ) {
      int pomak_s = cilj_s[i] - pozicija_s[i];
      int pomak_r = cilj_r[i] - pozicija_r[i];
      if( pomak_s < 0 ) pomak_s += N;
      if( pomak_r < 0 ) pomak_r += N;

      rotiraj_redak( pozicija_r[i], pomak_s );
      rotiraj_stupac( pozicija_s[i], pomak_r );

      printf( "%d\n", pomak_s + pomak_r );
   }

   return 0;
}
