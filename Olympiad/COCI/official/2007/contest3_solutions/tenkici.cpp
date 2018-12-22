
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 3 - Task TENKICI
  Programming language C++
*/

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

typedef pair<int,char> par;
vector<par> rjesenje;

// rasporedjuje tenkice po retcima (stupcima)
void rasporedi( int a[500], int n, char X, char Y ) {
   int index[500];
   for( int i = 0; i < n; ++i ) index[i] = i;

   // sortiraj
   for( int i = 0; i < n; ++i )
      for( int j = i+1; j < n; ++j )
         if( a[j] < a[i] ) {
            swap( a[i], a[j] );
            swap( index[i], index[j] );
         }

   // pomakni sve koji idu gore (lijevo)
   for( int i = 0; i < n; ++i )
      for( ; a[i] > i; --a[i] )
         rjesenje.push_back( par( index[i]+1, X ) );

   // pomakni sve koji idu dolje (desno)
   for( int i = n-1; i >= 0; --i )
      for( ; a[i] < i; ++a[i] )
         rjesenje.push_back( par( index[i]+1, Y ) );
}

int main( void ) {
   int n;
   scanf( "%d", &n );

   int r[500], s[500];
   for( int i = 0; i < n; ++i ) {
      scanf( "%d%d", &r[i], &s[i] );
      --r[i]; --s[i];
   }

   rasporedi( r, n, 'U', 'D' ); // rasporedi tenkice po retcima
   rasporedi( s, n, 'L', 'R' ); // rasporedi tenkice po stupcima

   printf( "%d\n", rjesenje.size() );
   for( vector<par>::iterator it = rjesenje.begin(); it != rjesenje.end(); ++it )
      printf( "%d %c\n", it->first, it->second );

   return 0;
}
