
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 6 - Task KAMEN
  Programming language C++
*/

#include <cstdio>

using namespace std;

int R, S, N;
char a[30000][32];

struct putanja {
   char stupac[30000];
   int r;

   void ubaci() {
      a[r-1][stupac[r-1]] = 'O';
   }

   void sredi() {
      for( ;; ) {
         int s = stupac[r-1];

         if( r > 1 && a[r-1][s] != '.' ) { --r; continue; }

         if( r == R ) break;
         if( a[r][s] == 'X' ) break;
         if( a[r][s] == '.' ) {
            stupac[r++] = s;
         } else {
            if( s > 0 && a[r][s-1] == '.' && a[r-1][s-1] == '.' ) {
               stupac[r++] = s-1;
            } else if( s+1 < S && a[r][s+1] == '.' && a[r-1][s+1] == '.' ) {
               stupac[r++] = s+1;
            } else {
               break;
            }
         }
      }
   }
} P[30];

int main( void ) {
   scanf( "%d%d", &R, &S );
   for( int r = 0; r < R; ++r ) scanf( "%s", a[r] );

   for( int i = 0; i < S; ++i ) {
      P[i].stupac[0] = i;
      P[i].r = 1;
      P[i].sredi();
   }

   scanf( "%d", &N );
   for( int i = 0; i < N; ++i ) {
      int s;
      scanf( "%d", &s ); --s;
      P[s].ubaci();
      for( int i = 0; i < S; ++i ) P[i].sredi();
   }

   for( int r = 0; r < R; ++r ) printf( "%s\n", a[r] );

   return 0;
}
