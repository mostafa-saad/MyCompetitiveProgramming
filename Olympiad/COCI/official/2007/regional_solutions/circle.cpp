
/*
  Croatian Regional Competition in Informatics 2007
  Task CIRCLE
  Programming language C++
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int n, k;

struct cmp {
   char *a;
   cmp( char *A ) { a = A; }
   bool operator () ( int x, int y ) { return strncmp( a + x, a + y, n ) < 0; }
};

int sorted[100];
void kanoniziraj( char *a ) {
   for( int i = 0; i < n; ++i ) a[n+i] = a[i];

   sort( sorted, sorted+n, cmp( a ) );

   for( int i = 0; i < n; ++i ) a[i] = a[sorted[0]+i];
   a[n] = 0;
}

char stavi( char x, char y ) { return x == y ? 'B' : 'W'; }

void transformacija( char *a, char *b ) {
   a[n] = a[0];
   for( int i = 0; i < n; ++i ) b[i] = stavi( a[i], a[i+1] );
}

int inverzna( char *a, char *b, char prvi ) {
   b[0] = prvi;
   for( int i = 1; i <= n; ++i ) b[i] = stavi( a[i-1], b[i-1] );
   return b[0] == b[n];
}

int m;
char kandidati[1024][200];

char razina[11][200];

void rec( int d ) {
   if( d == 0 ) {
      kanoniziraj( razina[0] );
      strncpy( kandidati[m++], razina[0], n );
      return;
   }

   if( inverzna( razina[d], razina[d-1], 'B' ) ) rec( d-1 );
   if( inverzna( razina[d], razina[d-1], 'W' ) ) rec( d-1 );
}

int main( void ) {
   scanf( "%d%d", &n, &k );
   scanf( "%s", razina );
   for( int i = 0; i < n; ++i ) sorted[i] = i;

   for( int i = 0; i < k; ++i ) transformacija( razina[i], razina[i+1] );

   rec( k );

   qsort( kandidati, m, sizeof kandidati[0], (int (*)(const void *, const void *))strcmp );

   int ret = 0;
   for( int i = 0; i < m; ++i )
      if( i == 0 || strcmp( kandidati[i], kandidati[i-1] ) )
         ++ret;
   printf( "%d\n", ret );

   return 0;
}
