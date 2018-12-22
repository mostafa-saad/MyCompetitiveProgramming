#include <cstdio>

int main( void ) {
   int a, b, c;
   scanf( "%d%d%d", &a, &b, &c );
   
   if( b-a > c-b ) 
      printf( "%d\n", b-a-1 );
   else
      printf( "%d\n", c-b-1 );

   return 0;
}
