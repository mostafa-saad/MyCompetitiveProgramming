#include <cstdio>

char a[7][7+1];

int main( void ) {
   for( int r = 0; r < 7; ++r ) gets( a[r] );

   int ret = 0;
   for( int r = 0; r < 7; ++r ) 
      for( int c = 0; c < 7; ++c ) {
         if( r+2 <  7 && a[r][c] == 'o' && a[r+1][c] == 'o' && a[r+2][c] == '.' ) ++ret;
         if( r-2 >= 0 && a[r][c] == 'o' && a[r-1][c] == 'o' && a[r-2][c] == '.' ) ++ret;
         if( c+2 <  7 && a[r][c] == 'o' && a[r][c+1] == 'o' && a[r][c+2] == '.' ) ++ret;
         if( c-2 >= 0 && a[r][c] == 'o' && a[r][c-1] == 'o' && a[r][c-2] == '.' ) ++ret;
      } 
        
   printf( "%d\n", ret );

   return 0;
}
