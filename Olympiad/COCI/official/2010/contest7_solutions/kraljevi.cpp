#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define MAX 1005
#define pLL pair<long long, long long>
using namespace std;
typedef long long LL;
int a[MAX][MAX];
pair<LL, LL> dp[2][MAX][MAX], col[MAX];
int n, m;
pLL operator+(pLL a, pLL b) {
  a.first += b.first;
  a.second += b.second;
  return a;
}
pLL operator+=(pLL &a, pLL b) {
  a.first += b.first;
  a.second += b.second;
  return a;
}

pLL dynamic(int no_row_col) {
  LL ret[2] = {0, 0};
  for( int who = 0; who < 2; ++who ) {
    memset(col, 0, sizeof(col));
    for( int i = 0; i < n; ++i ) 
      for( int j = 0; j < m; ++j )
        dp[who][i][j] = make_pair(0, 0);
    for( int i = 0; i < n; ++i ) {
      pLL curr(0, 0);
      for( int j = 0; j < m; ++j ) {
        int full = (a[i][j] == who);
        curr.second += curr.first;
        col[j].second += col[j].first;

        dp[who][i][j] = curr + col[j] 
          + (i&&j ? dp[who][i-1][j-1] : make_pair(0LL,0LL));

        curr.first += full;
        col[j].first += full;
      
        if( full ) {
          if( !no_row_col ) ret[who] += dp[who][i][j].second; 
          else if( i && j )  ret[who] += dp[who][i-1][j-1].second;
        }
        dp[who][i][j].first += full;
        dp[who][i][j].second += dp[who][i][j].first;
      }
    }
  }
    
  return make_pair(ret[0], ret[1]);
}

void input() {
  static char buff[MAX+1];
  memset(a, -1, sizeof(a));
  scanf("%d%d", &n, &m);
  for( int i = 0; i < n; ++i) {
    scanf("%s", buff);
    for( int j = 0; j < m; ++j ) {
      if( buff[j] != '.' )
        a[i][j] = (buff[j] == 'M' ? 0 : 1);
    }
  }
}

pLL solve() {
  pLL dyn1 = dynamic(0);
  for( int i = 0; i < n/2; ++i ) {
    int tmp[MAX];
    memcpy(tmp, a[i], sizeof(tmp));
    memcpy(a[i], a[n-i-1], sizeof(tmp));
    memcpy(a[n-i-1], tmp, sizeof(tmp));
  }
  pLL dyn2 = dynamic(1); 
  return make_pair(dyn1.first+dyn2.first,
                   dyn1.second+dyn2.second);
}
int main() {
  input();
  pLL sol = solve();
  printf("%lld %lld\n", sol.first, sol.second); 

  return 0;
}
