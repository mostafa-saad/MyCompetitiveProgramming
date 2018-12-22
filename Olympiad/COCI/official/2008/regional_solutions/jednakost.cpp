#include <cstdio>
#include <cstring>

const int inf = 1000000000;

int n;
char A[1001]; int S;

int prva_nenula[1000];
int memo[1000][5001];

int opt( int i, int suma ) {
   if( i == n ) return suma == 0 ? 0 : inf;

   int &ret = memo[i][suma];
   if( ret != -1 ) return ret;

   ret = inf;
   int broj = 0;
   for( int j = prva_nenula[i]; j < n; ++j ) {
      broj = broj * 10 + A[j]-'0';
      if( broj > suma ) break;
      ret <?= 1 + opt( j+1, suma-broj );
   }

   return memo[i][suma] = ret;
}

int ispisi( int i, int suma ) {
   if( i == n ) {
      printf( "=%d\n", S );
      return 1;
   }

   if( i > 0 ) printf( "+" );

   int broj = 0;
   for( int j = i; j < n; ++j ) {
      printf( "%c", A[j] );
      broj = broj * 10 + A[j]-'0';

      if( opt( i, suma ) == 1 + opt( j+1, suma-broj ) )
         return ispisi( j+1, suma-broj );
   }

   printf( "Nema rjesenja!\n" );
   return 0;
}

int main( void ) {
   scanf( "%[^=]=%d", A, &S );
   n = strlen( A );

   prva_nenula[n-1] = n-1;
   for( int i = n-2; i >= 0; --i )
      prva_nenula[i] = (A[i] == '0') ? prva_nenula[i+1] : i;

   memset( memo, -1, sizeof memo );

   ispisi( 0, S );

   return 0;
}
