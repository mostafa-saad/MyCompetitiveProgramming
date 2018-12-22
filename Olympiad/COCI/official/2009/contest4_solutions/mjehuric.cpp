#include <algorithm>
#include <cstdio>

int a[5];

int main( void ) {
   for( int i = 0; i < 5; ++i ) scanf( "%d", &a[i] );

   int changes = 1;
   while( changes ) {
      changes = 0;
      for( int i = 1; i < 5; ++i ) 
         if( a[i-1] > a[i] ) {
            changes = 1;
            std::swap( a[i-1], a[i] );
            
            for( int j = 0; j < 5; ++j ) {
               if( j ) printf( " " );
               printf( "%d", a[j] );
            }
            printf( "\n" );
         }
   }
   return 0;
}
