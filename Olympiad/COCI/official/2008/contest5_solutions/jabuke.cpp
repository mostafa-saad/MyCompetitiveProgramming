#include <cstdio>

struct point { int x, y; };

int area( point A, point B, point C ) {
   int t = A.x*(B.y-C.y) + B.x*(C.y-A.y) + C.x*(A.y-B.y);
   if( t < 0 ) return -t; else return t;
}

int main( void ) {
   point A, B, C;
   scanf( "%d%d", &A.x, &A.y );
   scanf( "%d%d", &B.x, &B.y );
   scanf( "%d%d", &C.x, &C.y );   
   
   int n, trees = 0;
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) {
      point P;
      scanf( "%d%d", &P.x, &P.y );
      
      if( area(A,B,P) + area(A,C,P) + area(B,C,P) == area(A,B,C) )
         ++trees;
   }

   printf( "%.1lf\n", area(A,B,C) / 2.0 );
   printf( "%d\n", trees );
   
   return 0;
}
