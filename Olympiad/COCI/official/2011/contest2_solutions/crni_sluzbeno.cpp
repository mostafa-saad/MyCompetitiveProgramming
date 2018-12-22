#include <cstdio>
#include <algorithm>
#include <stack>

using namespace std;

const int MAX = 1010;
const int mod = 10007;

int n;
char grid[MAX][MAX];
int table[MAX][MAX];

int h[MAX];
int ans[MAX][MAX];

int ul[MAX][MAX];
int dl[MAX][MAX];

int UL[MAX][MAX];
int UR[MAX][MAX];
int DL[MAX][MAX];
int DR[MAX][MAX];

void flip_ver( int mat[MAX][MAX] ) {
  for( int i = 1; i <= n; ++i )
    for( int a = 1, b = n; a < b; ++a, --b )
      swap( mat[i][a], mat[i][b] );
}

void flip_hor( int mat[MAX][MAX] ) {
  for( int a = 1, b = n; a < b; ++a, --b )
    for( int i = 1; i <= n; ++i )
      swap( mat[a][i], mat[b][i] );
}

void copy( int a[MAX][MAX], int b[MAX][MAX] ) {
  for( int i = 1; i <= n; ++i )
    for( int j = 1; j <= n; ++j )
      b[i][j] = a[i][j];
}

void init( int mat[MAX][MAX] ) {
  for( int i = 1; i <= n; ++i )
    for( int j = 1; j <= n; ++j ) {
      mat[i][j] += mat[i-1][j];
      mat[i][j] += mat[i][j-1];
      mat[i][j] -= mat[i-1][j-1];
      mat[i][j] += mod;
      mat[i][j] %= mod;
    }
}

void solve() {
  for( int c = 1; c <= n; ++c ) h[c] = 0;
  for( int r = 1; r <= n; ++r ) {
    for( int c = 1; c <= n; ++c ) {
      if( table[r][c] ) ++h[c];
      else h[c] = 0;
    }

    stack<int> stk;
    stk.push( 0 );
    int area = 0;

    for( int c = 1; c <= n; ++c ) {
      while( stk.top() && h[stk.top()] >= h[c] ) {
        int a = stk.top();
        stk.pop();
        int b = stk.top();
        area -= ( c-b-1 ) * ( h[a] - max( h[c], h[b] ) );
      }

      stk.push( c );
      area += h[c];
      ans[r][c] = max( area-1, 0 ) % mod;
    }
  }
}

int main( void ) {
  scanf( "%d", &n );
  for( int i = 0; i < n; ++i ) {
    scanf( "%s", grid[i] );
    for( int j = 0; j < n; ++j )
      table[i+1][j+1] = ( grid[i][j] == 'C' );
  }

  solve();
  copy( ans, ul );
  copy( ans, UL );
  init( UL );

  flip_ver( table );
  solve();
  copy( ans, UR );
  init( UR );
  flip_ver( table );

  flip_hor( table );
  solve();
  copy( ans, dl );
  copy( ans, DL );
  init( DL );

  flip_ver( table );
  solve();
  copy( ans, DR );
  init( DR );

  flip_ver( UR );
  flip_hor( dl );
  flip_hor( DL );
  flip_ver( DR );
  flip_hor( DR );

  int ans = 0;
  for( int i = 1; i <= n; ++i ) {
    ans += ( DL[1][i]-DL[1][i-1]+mod ) * DR[1][i+1];
    ans += ( UL[i][n]-UL[i-1][n]+mod ) * DL[i+1][n];
    ans %= mod;
    for( int j = 1; j <= n; ++j ) {
      ans -= ul[i][j] * DR[i+1][j+1];
      ans -= dl[i][j] * UR[i-1][j+1];
      ans = ( ans%mod + mod ) % mod;
    }
  }
  printf( "%d\n", ans );

  return 0;
}

