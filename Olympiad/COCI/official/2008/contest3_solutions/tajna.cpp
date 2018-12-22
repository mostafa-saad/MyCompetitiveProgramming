#include <cstdio>
#include <cstring>

char a[100+1];

int main( void ) {
   scanf( "%s", a );
   int n = strlen( a );
   
   int R = 1;
   for( int r = 1; r < n; ++r ) {
      int s = n/r;
      if( r <= s && r*s == n ) R = r;
   }
   int S = n/R;
   
   for( int r = 0; r < R; ++r ) 
      for( int s = 0; s < S; ++s ) 
         printf( "%c", a[s*R+r] );
   printf( "\n" );

   return 0;
}
