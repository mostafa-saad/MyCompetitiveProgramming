#include <cstdio>
#include <cstdlib>
#include <cstring>

int n, m;
char s[32];
char a[30000][32];

char sorted[30000][32];
int counter[30000][32];
int before[30000][32];
int id[30000];

int cmp( const void *e1, const void *e2 ) {
   return strcmp( (const char *)e1, (const char *)e2 );
}

int find_border( char x, int column, int lo, int hi ) {
   if( x > sorted[hi-1][column] ) return hi;

   while( lo + 1 < hi ) {
      int mid = (lo+hi-1)/2;
      if( x > sorted[mid][column] ) lo = mid+1; else hi = mid+1;
   }

   return lo;
}

int begin[32], end[32];

int search( char *s, int column, int lo, int hi ) {
   begin[column] = end[column] = -1;

   if( s[column] == 0 ) return sorted[lo][column] == 0 ? lo : -1;

   begin[column] = find_border( s[column], column, lo, hi );
   end[column] = find_border( s[column]+1, column, lo, hi );
   
   if( begin[column] == end[column] ) return -1;
   
   return search( s, column + 1, begin[column], end[column] );
}

int main( void ) {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) {
      scanf( "%s", a[i] );
      strcpy( sorted[i], a[i] );
   }
   qsort( sorted, n, 32, cmp );

   for( int i = 0; i < n; ++i ) {
      int row = search( a[i], 0, 0, n );      
      id[row] = i+1;

      for( int column = 0; begin[column] < end[column]; ++column )
         before[row][column] = ++counter[begin[column]][column];      
   }

   scanf( "%d", &m );
   for( int qq = 0; qq < m; ++qq ) {
      scanf( "%s", s );
   
      int ret = 0;
      int row = search( s, 0, 0, n );
      if( row == -1 ) {
         ret += n;
         for( int column = 0; begin[column] < end[column]; ++column )
            ret += counter[begin[column]][column];
      } else {
         ret += id[row];
         for( int column = 0; s[column]; ++column ) 
            ret += before[row][column];
      }

      printf( "%d\n", ret );
   }
   
   return 0;
}
