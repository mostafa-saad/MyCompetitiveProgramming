#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

typedef pair<int,int> par;

#define MAXR 100
#define MAXS 100

int R, S;
char a[MAXR][MAXS+1];
char bio[MAXR][MAXS+1];

vector<par> nakupina;

void dfs( int r, int s ) {
   if( r < 0 || r >= R ) return;
   if( s < 0 || s >= S ) return;
   if( a[r][s] == '.' ) return;
   if( bio[r][s] ) return;
   bio[r][s] = 1;
   nakupina.push_back( par(r,s) );
   dfs( r, s-1 );
   dfs( r, s+1 );
   dfs( r-1, s );
   dfs( r+1, s );
}

void srusi() {
   memset( bio, 0, sizeof bio );

   for( int r = 0; r < R; ++r ) {
      for( int s = 0; s < S; ++s ) {
         if( a[r][s] == '.' || bio[r][s] ) continue;
         
         nakupina.clear();
         dfs( r, s );

         vector<int> najniza( S, -1 );
         for( vector<par>::iterator it = nakupina.begin(); it != nakupina.end(); ++it ) {
            najniza[it->second] = max( najniza[it->second], it->first );
            a[it->first][it->second] = '.';
         }

         int padni = R;
         for( int i, j = 0; j < S; ++j ) {
            if( najniza[j] == -1 ) continue;
            for( i = najniza[j]+1; i < R && a[i][j] == '.'; ++i );
            padni = min( padni, i-najniza[j]-1 );
         }
         
         for( vector<par>::iterator it = nakupina.begin(); it != nakupina.end(); ++it ) {
            it->first += padni;
            a[it->first][it->second] = 'x';
            bio[it->first][it->second] = 1;
         }
      }
   }
}

int main( void ) {
   scanf( "%d%d", &R, &S );
   for( int r = 0; r < R; ++r ) scanf( "%s", a[r] );

   int N;
   scanf( "%d", &N );
   for( int i = 0; i < N; ++i ) {
      int h;
      scanf( "%d", &h );

      int r = R-h;
      if( i % 2 == 0 ) {
         for( int s = 0; s < S; ++s )
            if( a[r][s] == 'x' ) { a[r][s] = '.'; break; }
      } else {
         for( int s = S-1; s >= 0; --s )
            if( a[r][s] == 'x' ) { a[r][s] = '.'; break; }
      }
      
      srusi();
   }

   for( int r = 0; r < R; ++r ) printf( "%s\n", a[r] );
   return 0;
}
