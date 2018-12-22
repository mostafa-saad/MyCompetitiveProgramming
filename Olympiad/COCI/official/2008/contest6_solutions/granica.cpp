#include <cstdio>

int n;
int a[100];

int ok( int M ) {
   int ostatak = a[0]%M;
   for( int i = 1; i < n; ++i )
      if( a[i]%M != ostatak )
         return 0;
   return 1;
}

int main( void ) {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) scanf( "%d", &a[i] );

   int razlika = a[0]-a[1];
   if( razlika < 0 ) razlika = -razlika;

   for( int d = 1; d*d <= razlika; ++d ) {
      if( razlika % d != 0 ) continue;

      int M1 = d, M2 = razlika/d;

      if( ok( M1 ) && M1 != 1  ) printf( "%d ", M1 );
      if( ok( M2 ) && M2 != M1 ) printf( "%d ", M2 );
   }
   printf( "\n" );

   return 0;
}
