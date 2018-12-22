#include <cstdio>

int R, C, kut;
char a[100][101];
char b[100][101];

void rot90() { 
   int tmp = R; R = C; C = tmp;
   for( int r = 0; r < R; ++r )
      for( int c = 0; c < C; ++c )
         b[r][c] = a[C-c-1][r];

   for( int r = 0; r < R; ++r ) 
      for( int c = 0; c < C; ++c ) 
         a[r][c] = b[r][c];
}

void output1() {
   for( int r = 0; r < R; ++r ) {
      for( int c = 0; c < C; ++c ) 
         printf( "%c", a[r][c] );
      printf( "\n" );
   }
}

void output2() { 
   for( int d = 0; d < R+C-1; ++d ) {
      int leading = (d < R) ? R-d-1 : d-R+1;
      for( int i = 0; i < leading; ++i ) printf( " " );
      
      int r = (d < R) ? d : R-1;
      int c = (d < R) ? 0 : d-R+1;

      printf( "%c", a[r][c] );
      for( ;; ) { 
         --r;
         ++c;
         if( r < 0 || c >= C ) break;
         printf( " %c", a[r][c] );
      }
      printf( "\n" );
   }
}

int main( void ) {
   scanf( "%d%d", &R, &C );
   for( int r = 0; r < R; ++r ) scanf( "%s", a[r] );
   scanf( "%d", &kut );

   while( kut >= 90 ) {
      kut -= 90;
      rot90();
   }

   if( kut == 0 ) output1();
   else output2();

   return 0;
}
