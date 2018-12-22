#include <algorithm>
#include <cstdio>

using namespace std;

struct data { int all0, all1, rec; };

const int inf = 1000000000;

int n;
char a[512][513];
char b[512][513];

data rec( int r_lo, int c_lo, int r_hi, int c_hi ) {
   data ret;
   if( r_lo+1 == r_hi ) {
      ret.all0 = a[r_lo][c_lo] != '0';
      ret.all1 = a[r_lo][c_lo] != '1';
      ret.rec = 0;
      b[r_lo][c_lo] = a[r_lo][c_lo];
   } else {
      int size = (r_hi-r_lo)/2;
      int r_mid = r_lo + size;
      int c_mid = c_lo + size;

      data kvadrati[2][2];
      kvadrati[0][0] = rec( r_lo, c_lo, r_mid, c_mid );
      kvadrati[1][0] = rec( r_mid, c_lo, r_hi, c_mid );
      kvadrati[0][1] = rec( r_lo, c_mid, r_mid, c_hi );
      kvadrati[1][1] = rec( r_mid, c_mid, r_hi, c_hi );
      
      ret.all0 = ret.all1 = 0;
      for( int kvad = 0; kvad < 4; ++kvad ) {
         ret.all0 += kvadrati[kvad>>1][kvad&1].all0;
         ret.all1 += kvadrati[kvad>>1][kvad&1].all1;
      }
      
      ret.rec = inf;
      int best[4];
      int kvads[4] = { 0, 1, 2, 3 };
      do {
         int val = 
            kvadrati[ kvads[0]>>1 ][ kvads[0]&1 ].all0 + 
            kvadrati[ kvads[1]>>1 ][ kvads[1]&1 ].all1 + 
            kvadrati[ kvads[2]>>1 ][ kvads[2]&1 ].rec + 
            kvadrati[ kvads[3]>>1 ][ kvads[3]&1 ].rec;

         if( val < ret.rec ) {
            ret.rec = val;
            for( int i = 0; i < 4; ++i ) best[i] = kvads[i];
         }
      } while( next_permutation( kvads, kvads+4 ) );

      for( int r = 0; r < size; ++r ) 
         for( int c = 0; c < size; ++c ) {
            b[ r_lo + (best[0]>>1)*size + r ][ c_lo + (best[0]&1)*size + c ] = '0';
            b[ r_lo + (best[1]>>1)*size + r ][ c_lo + (best[1]&1)*size + c ] = '1';
         }
   }
   return ret;
}

int main( void ) {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) scanf( "%s", a[i] );
   
   printf( "%d\n", rec( 0, 0, n, n ).rec );
   for( int i = 0; i < n; ++i ) printf( "%s\n", b[i] );

   return 0;
}
