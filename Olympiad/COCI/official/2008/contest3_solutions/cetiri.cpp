#include <cstdio>

int abs( int a ) { 
   if( a < 0 ) return -a;
   return a;
}

int min3( int a, int b, int c ) {
   if( a < b )
      if( a < c ) return a;
      else return c;
   else 
      if( b < c ) return b;
      else return c;
}

int main( void ) {
   int a1, a2, a3;
   scanf( "%d%d%d", &a1, &a2, &a3 );
   
   int a4 = min3( a1, a2, a3 );
   int d = min3( abs(a1-a2), abs(a1-a3), abs(a2-a3) );

   while( a4 == a1 || a4 == a2 || a4 == a3 ) a4 += d;

   printf( "%d\n", a4 );
   
   return 0;
}
