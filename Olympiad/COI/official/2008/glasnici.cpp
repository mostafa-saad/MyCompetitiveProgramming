#include <cstdio>

int N;
double K;
double D[100000];

int ok( double T ) {
  double x = D[0] + T;
  for (int i = 1; i < N; i++) {
     if( D[i]-T > x+K ) return 0;     
     x = (x + K) <? (D[i] + T);
  }
  return 1;
}

int main( void ) {
   scanf( "%lf", &K );
   scanf( "%d", &N );
   for( int i = 0; i < N; ++i ) scanf( "%lf", &D[i] );
      
   double lo = 0.0, hi = 1e9;
   for( int iter = 0; iter < 100; ++iter ) {
      double mid = (lo+hi)/2.0;
      
      if( ok( mid ) ) hi = mid; else lo = mid;
   }
   printf( "%.3lf\n", lo );
   
   return 0;
}
