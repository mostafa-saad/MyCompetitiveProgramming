#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 201;

int left[MAXN], right[MAXN];
int lo[MAXN], hi[MAXN];
int n, m;

int match[MAXN], vis[MAXN];

vector< int > E[MAXN];

int dfs( int x ) {
  if ( vis[x] ) return 0;
  vis[x] = 1;
  for ( int i = 0; i < (int)E[x].size(); ++i ) {
    int w = E[x][i];
    if ( match[w] == -1 || dfs( match[w] ) ) {
      match[w] = x;
      return 1;
    }
  }
  return 0;
}

int main() {
  scanf( "%d%d", &n, &m );  
  
  for( int i = 0; i < n; ++i ) {
    lo[i] = left[i] = 0;
    hi[i] = right[i] = n-1;
  }

  for( int i = 0; i < m; ++i ) {
    int t, x, y, v;
    scanf( "%d%d%d%d", &t, &x, &y, &v );
    --x, --y, --v;
    left[v] = max( left[v], x );
    right[v] = min( right[v], y );
    for( int j = x; j <= y; ++j ) {
      if ( t == 1 ) hi[j] = min( hi[j], v );
      else lo[j] = max( lo[j], v );
    }
  }

  memset( match, -1, sizeof match ); 

  for( int i = 0; i < n; ++i )
    for( int j = left[i]; j <= right[i]; ++j )
      if ( i >= lo[j] && i <= hi[j] )
        E[i].push_back(j);
  
  int flag = 1; 
  for( int i = 0; i < n && flag; ++i ) {
    memset( vis, 0, sizeof vis );
    flag = dfs(i);
  }

  if ( flag ) {
    for( int i = 0; i < n; ++i ) 
      printf( "%d%c", match[i]+1, " \n"[i==n-1] );
  } else {
    puts( "-1" );
  }

  return 0;
}
