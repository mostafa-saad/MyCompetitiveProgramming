#include <cstdio>
#include <cstring>

const int inf = 1000000000;

int n;
int pristojba[1000];
int memo[1000][1000];

int opt( int polje, int skok ) {
   if( polje < 0 || polje >= n ) return inf;
   if( polje == n-1 ) return pristojba[polje];

   if( memo[polje][skok] != -1 ) return memo[polje][skok];

   return memo[polje][skok] = pristojba[polje] + ( opt( polje-skok, skok ) <? opt( polje+skok+1, skok+1 ) );
}

int main( void ) {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) scanf( "%d", &pristojba[i] );

   memset( memo, -1, sizeof memo );

   printf( "%d\n", opt( 1, 1 ) );

   return 0;
}
