#include <cstdio>

#define MAX 1000

const int inf = 1000000000;

int N, M;
int A, B, K, G;
int prolazak[MAX][MAX];
int t_george[MAX][MAX];
int put[MAX];
int udalj[MAX];
int bio[MAX];

int min( int a, int b ) { return a < b ? a : b; }
int max( int a, int b ) { return a > b ? a : b; }

int main( void ) {
   scanf( "%d%d", &N, &M );
   for( int i = 0; i < N; ++i )
      for( int j = 0; j < N; ++j )
         prolazak[i][j] = t_george[i][j] = inf;

   scanf( "%d%d%d%d", &A, &B, &K, &G ); --A; --B;
   for( int i = 0; i < G; ++i ) {
      scanf( "%d", &put[i] ); --put[i];
   }

   for( int i = 0; i < M; ++i ) {
      int u, v, d;
      scanf( "%d%d%d", &u, &v, &d ); --u; --v;
      prolazak[u][v] = d;
      prolazak[v][u] = d;
   }

   for( int i = 1, t = 0; i < G; ++i ) {
      t_george[put[i-1]][put[i]] = t;
      t_george[put[i]][put[i-1]] = t;
      t += prolazak[put[i-1]][put[i]];
   }

   for( int i = 0; i < N; ++i ) {
      udalj[i] = inf;
      bio[i] = 0;
   }
   udalj[A] = K;

   for( int i = 0; i < N; ++i ) {
      int m = -1;
      for( int j = 0; j < N; ++j ) {
         if( bio[j] ) continue;
         if( m == -1 || udalj[j] < udalj[m] ) m = j;
      }
      bio[m] = 1;

      for( int j = 0; j < N; ++j )
         if( udalj[m] < t_george[m][j] )
            udalj[j] = min( udalj[j], udalj[m] + prolazak[m][j] );
         else
            udalj[j] = min( udalj[j], max( t_george[m][j] + prolazak[m][j], udalj[m]) + prolazak[m][j] );
   }

   printf( "%d\n", udalj[B]-udalj[A] );

   return 0;
}
