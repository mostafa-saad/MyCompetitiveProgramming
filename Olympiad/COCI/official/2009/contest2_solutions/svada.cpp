#include <cstdio>

#define MAXN 100

int t, n, m;
int a[MAXN], b[MAXN], c[MAXN], d[MAXN];

void load() {
   scanf( "%d", &t );
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) scanf( "%d%d", &a[i], &b[i] );
   scanf( "%d", &m );
   for( int i = 0; i < m; ++i ) scanf( "%d%d", &c[i], &d[i] );
}

int f( int v, int x, int y ) {
   if( v < x ) return 0;
   return (v-x)/y + 1;
}

int koliko( int v, int *x, int *y, int q ) {
   int ret = 0;
   for( int i = 0; i < q; ++i ) ret += f( v, x[i], y[i] );
   return ret;
}

int moze( int v ) {
   return koliko( v, a, b, n ) <= koliko( t-v, c, d, m );
}

int solve() {
   int l = 1, r = t;
   while( r-l > 1 ) {
      int tt = (l+r)/2;
      if( moze(tt) ) l = tt;
      else r = tt;
   }
   return l;
}

int main(void) {
   load();
   printf( "%d\n", solve() );
   return 0;
}
