#include <cstdio>

#define MAXN 100

int n, m, l[MAXN][MAXN], r[MAXN][MAXN], u[MAXN][MAXN], d[MAXN][MAXN];
char grid[MAXN][MAXN+1];

void load() {
   scanf( "%d%d", &n, &m );
   for( int i = 0; i < n; ++i ) scanf( "%s", grid[i] );
}

void init() {
   for( int i = 0; i < n; ++i )
      for( int j = 0; j < m; ++j ) {
         if( grid[i][j] != 'x' ) continue;

         u[i][j] = l[i][j] = 1;

         if( i ) u[i][j] += u[i-1][j];
         if( j ) l[i][j] += l[i][j-1];
      }

   for( int i = n-1; i >= 0; --i )
      for( int j = m-1; j >= 0; --j ) {
         if( grid[i][j] != 'x' ) continue;

         d[i][j] = r[i][j] = 1;

         if( i+1 < n ) d[i][j] += d[i+1][j];
         if( j+1 < m ) r[i][j] += r[i][j+1];
      }
}

int min( int a, int b ) { return a<b ? a : b; }

void solve() {
   for( int i = 0; i < n; ++i )
      for( int j = 0; j < m; ++j ) {
         if( grid[i][j] != 'x' ) continue;

         int L = l[i][j]-1, R = r[i][j]-1;
         int U = u[i][j]-1, D = d[i][j]-1;

         int s = (L>0) + (R>0) + (D>0) + (U>0);

         if( s < 2 ) grid[i][j] = -1;
         if( s > 2 ) continue;

         if( L && U ) grid[ i-min(L,U) ][ j-min(L,U) ] = -min(L,U)-1;
         if( L && D ) grid[ i ][ j-min(L,D) ] = -min(L,D)-1;
         if( R && U ) grid[ i-min(R,U) ][ j ] = -min(R,U)-1;
         if( R && D ) grid[ i ][ j ] = -min(R,D)-1;
      }
}

void output() {
   int li = -1, lj, s = 0;
   for( int i = 0; i < n; ++i )
      for( int j = 0; j < m; ++j )
         if( grid[i][j] < 0 ) {
            printf( "%d %d %d\n", i+1, j+1, -grid[i][j] );
            li = i+1;
            lj = j+1;
            ++s;
         }
   if( s == 1 ) printf( "%d %d 1\n", li, lj );
}

int main(void) {
   load();
   init();
   solve();
   output();
   return 0;
}
