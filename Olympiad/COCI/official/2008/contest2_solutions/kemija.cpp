#include <cstdio>

#define MAX 10000

int n;
int A[MAX];
int B[MAX];

void add( int x, int value ) {
   int i = x;
   do { 
      A[i] += value;
      i = (i+3)%n;
   } while( i != x );
}

int init( int x ) {
   int value = 0;
   int min_value = 0;

   int i = x;
   do {
      min_value <?= A[i] = value;
      i = (i+1)%n;

      value -= B[i];
      i = (i+1)%n;

      value += B[i];
      i = (i+1)%n;
   } while( i != x );

   return min_value;
}

int main( void ) {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) scanf( "%d", &B[i] );

   if( n%3 != 0 ) {
      init( 0 );
      add( 0, (B[1] - A[0] - A[1] - A[2])/3 );
   } else {
      add( 0, 1-init( 0 ) );
      add( 1, 1-init( 1 ) );
      init( 2 );
      add( 2, B[1] - A[0] - A[1] );
   }

   for( int i = 0; i < n; ++i ) printf( "%d\n", A[i] );
   
   return 0;
}
