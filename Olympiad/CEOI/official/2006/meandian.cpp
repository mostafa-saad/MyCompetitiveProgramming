#include "libmeandian.h"

using namespace std;

int n;

void swap( int &a, int &b ) { int t = a; a = b; b = t; }

void cetiri( int &a, int &b, int &c, int &d, int e ) {
   int t, m = Meandian( a, b, c, d );

   swap( a, e ); t = Meandian( a, b, c, d );
   if( t > m ) m = t; else swap( a, e );
   swap( b, e ); t = Meandian( a, b, c, d );
   if( t > m ) m = t; else swap( b, e );
   swap( c, e ); t = Meandian( a, b, c, d );
   if( t > m ) m = t; else swap( c, e );
   swap( d, e ); t = Meandian( a, b, c, d );
   if( t > m ) m = t; else swap( d, e );
}

void preslozi( int &a, int &b, int &c, int &d ) {
   int e;
   for( e = 1; (e == a) || (e == b) || (e == c) || (e == d); ++e );
   int ta = Meandian( b, c, d, e );
   int tb = Meandian( a, c, d, e );
   int tc = Meandian( a, b, d, e );
   int td = Meandian( a, b, c, e );
   if( ta > tb ) { swap( ta, tb ); swap( a, b ); }
   if( ta > tc ) { swap( ta, tc ); swap( a, c ); }
   if( ta > td ) { swap( ta, td ); swap( a, d ); }
   if( tb > tc ) { swap( tb, tc ); swap( b, c ); }
   if( tb > td ) { swap( tb, td ); swap( b, d ); }
   if( tc > td ) { swap( tc, td ); swap( c, d ); }
}

int niz[101];

void rijesi( int a, int b, int c ) {
   int d, e, f;
   for( d = 1; (d == a) || (d == b) || (d == c); ++d );
   for( e = 1; (e == a) || (e == b) || (e == c) || (e == d); ++e );

   int bc = Meandian( a, b, c, d )*2;
   int bd = Meandian( a, b, d, e )*2;
   int cd = Meandian( a, c, d, e )*2;
   niz[c] = (bc+cd-bd)/2;
   int t, m = cd/2;
   for( int i = 1; i <= n; ++i ) {
      f = i;
      if( (f == a) || (f == b) || (f == c) || (f == d) || (f == e) ) continue;

      swap( d, f ); t = Meandian( a, c, d, e );
      if( t < m ) m = t; else swap( d, f );
      swap( e, f ); t = Meandian( a, c, d, e );
      if( t < m ) m = t; else swap( e, f );

      niz[f] = Meandian( a, c, e, f ) * 2 - niz[c];
   }
}

int main( void ) {
   n = Init();
   for( int i = 1; i <= n; ++i ) niz[i] = -1;
   int a = 1, b = 2, c = 3, d = 4;
   for( int i = 5; i <= n; ++i ) cetiri( a, b, c, d, i );
   preslozi( a, b, c, d );
   rijesi( a, b, c );
   Solution(niz+1);
   return 0;
}
