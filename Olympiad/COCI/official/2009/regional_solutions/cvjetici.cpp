#include <cstdio>

int N;
int A[100001];
int B[1000];

int main( void ) {
   scanf( "%d", &N );
   for( int i = 0; i < N; ++i ) {
      int L, R;
      scanf( "%d%d", &L, &R );

      printf( "%d\n", A[L]+B[L>>8] + A[R]+B[R>>8] );

      A[L] = -B[L>>8];
      A[R] = -B[R>>8]; 
      
      int x = L+1;
      for( ; x < R && (x&0xFF); ++x ) ++A[x];
      for( ; x+256 <= R;   x += 256 ) ++B[x>>8];
      for( ; x < R;             ++x ) ++A[x];
   }

   return 0;
}
