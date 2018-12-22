#include <algorithm>
#include <cstdio>

#define MAXP 50
#define MAXN 30000

int N, K;
int P, p[MAXP+1];
int p_start;
char ret[MAXN+1][MAXP+1];

int koliko[26];

int main( void ) {
   scanf( "%d%d", &N, &K );
   for( int i = 0; i < K; ++i ) {
      char c; int x;
      scanf( " %c%d", &c, &x );
      koliko[c-'A'] = x;      
   }

   int neparnih = 0;
   for( int i = 0; i < 26; ++i ) 
      if( koliko[i]&1 )
         ++neparnih;
   
   if( neparnih > N ) {
      printf( "IMPOSSIBLE\n" );
      return 0;
   }

   scanf( "%d", &P );
   for( int i = 0; i < P; ++i ) scanf( "%d", &p[i] );
   p[P] = N+1;
   
   int slovo;
   p_start = 0;
   for( int r = 1; r <= N; ++r ) {
      int prvi, prvi_neparni;      
      
      neparnih = 0;
      for( int i = 25; i >= 0; --i ) {
         if( koliko[i] > 0 ) prvi = i;
         if( koliko[i]&1 ) { prvi_neparni = i; ++neparnih; }
      }
      if( N-r+1 > neparnih ) slovo = prvi;
      else slovo = prvi_neparni;

      --koliko[slovo];
      int cijeli_red = r == p[p_start];
      if( cijeli_red ) ret[r][p_start] = slovo+'A';      

      slovo = 0;
      int s = r + 1;
      int pos = p_start + cijeli_red;
      while( s <= N ) {
         while( koliko[slovo] < 2 ) ++slovo;

         if( cijeli_red ) ret[s][p_start] = slovo+'A';
         if( s == p[pos] ) ret[r][pos++] = slovo+'A';
         
         int next_s = p[pos];
         if( cijeli_red ) next_s = s+1;
         next_s = std::min( next_s, s + koliko[slovo]/2 );
         
         koliko[slovo] -= (next_s-s)*2;

         s = next_s;
      }
      if( cijeli_red ) ++p_start;

      printf( "%s\n", ret[r] );
   }

   return 0;
}
