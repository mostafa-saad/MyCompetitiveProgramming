#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 500005;

int s[MAXN], f[MAXN];
int a[MAXN], sef[MAXN];
vector< int > E[MAXN];

int timer = 0;
void dfs( int x ) {
  s[x] = timer++;
  for( int i = 0; i < E[x].size(); ++i )
    dfs( E[x][i] );
  f[x] = timer;
}

int L[MAXN];
inline void add( int x, int y ) {
  for( ++x; x < MAXN; x += x&-x ) L[x] += y;
}
inline int sum( int x ) {
  int r = 0;
  for( ++x; x; x -= x&-x ) r += L[x];
  return r;
}

int main( void ) {
  int n, m;
  scanf( "%d %d", &n, &m );

  scanf( "%d", a + 0 );
  for( int i = 1; i < n; ++i ) {
    scanf( "%d %d", a+i, sef+i ); --sef[i];
    E[ sef[i] ].push_back( i );
  }

  dfs( 0 );
  for( int i = 0; i < m; ++i ) {
    char izbor[10];
    scanf( "%s", izbor );
    
    if( izbor[0] == 'p' ) {
      int a, x;
      scanf( "%d %d", &a, &x ); --a;
      add( s[a]+1, +x );
      add( f[a], -x );
    }
    if( izbor[0] == 'u' ) {
      int x;
      scanf( "%d", &x ); --x;
      printf( "%d\n", a[x] + sum( s[x] ) );
    }
  }

  return 0;
}
