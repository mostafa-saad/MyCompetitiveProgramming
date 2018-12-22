
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 3 - Task LISTA
  Programming language C++
*/

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define MAX 500000

struct cvor { int L, R; } lista[MAX+2];

int prosli[MAX+1];
int M[MAX+1];

int main( void ) {
   int n, m;
   scanf( "%d%d", &n, &m );
   for( int i = 0; i <= n+1; ++i ) {
      lista[i].L = i-1;
      lista[i].R = i+1;
   }

   for( int i = 0; i < m; ++i ) {
      char c; int x, y;
      scanf( " %c%d%d", &c, &x, &y );

      // izbaci x iz liste
      lista[lista[x].R].L = lista[x].L;
      lista[lista[x].L].R = lista[x].R;

      // odredi nove susjede cvoru x
      if( c == 'A' ) {
         lista[x].L = lista[y].L;
         lista[x].R = y;
      } else {
         lista[x].L = y;
         lista[x].R = lista[y].R;
      }

      // ubaci x u listu
      lista[lista[x].R].L = x;
      lista[lista[x].L].R = x;
   }

   // nadji najdulji rastuci podniz
   M[0] = 0;
   for( int i = 1; i <= n; ++i ) M[i] = 1000000000;

   int najdulji = 0;
   for( int x = lista[0].R; x != n+1; x = lista[x].R ) {

      int d = upper_bound( M, M+n, x ) - M;
      M[d] = x;
      prosli[x] = M[d-1];
      najdulji >?= d;
   }

   printf( "%d\n", n - najdulji );

   vector<int> A;
   for( int x = M[najdulji]; x != 0; x = prosli[x] )
      A.push_back( x );
   reverse( A.begin(), A.end() );

   // ispisi niz operacija
   int i = 0, j = 1;
   while( i < najdulji ) {
      if( j == A[i] ) ++i;
      else printf( "A %d %d\n", j, A[i] );
      ++j;
   }
   int zadnji = A.back();
   while( j <= n ) {
      printf( "B %d %d\n", j, zadnji );
      zadnji = j;
      ++j;
   }

   return 0;
}
