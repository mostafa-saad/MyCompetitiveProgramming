
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 1 - Task BOND
  Programming language C++
*/

#include <cstdio>
using namespace std;

int n;
double prob[21][21];

char vec_rijesio[1<<21];
double memo[1<<21];

double rijesi( int d, int s ) {
   if ( d == n )
      return 1.0;

   if ( vec_rijesio[s] ) return memo[s];
   vec_rijesio[s] = 1;
   double &ret = memo[s];
   ret = 0.0;

   for ( int i=0; i<n; ++i )
      if ( ( s & (1<<i) ) == 0 ) {
         double tmp = prob[d][i] * rijesi(d + 1, s|(1<<i));
         if ( tmp > ret ) ret = tmp;
      }

   return ret;
}

int main() {
   scanf( "%d", &n );

   for ( int i=0; i<n; ++i )
      for ( int j=0; j<n; ++j ) {
         int x;
         scanf( "%d", &x );
         prob[i][j] = x / 100.0;
      }

   double ret = rijesi( 0, 0 );
   printf( "%.6f\n", ret*100.0 );

   return 0;
}
