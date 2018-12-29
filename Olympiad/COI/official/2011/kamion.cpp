#include <algorithm>
#include <cctype>
#include <cstdio>
#include <vector>

using namespace std;

#define MAXN 50
#define MAXK 50
#define MAXT 26
#define MOD 10007
#define ADD(a, b) a = (a + b) % MOD
#define FOR_EACH(it, cont) \
    for(vector<par>::iterator it = cont.begin(); it != cont.end(); ++it)

int N, E, K;
typedef pair<int, int> par;
vector<par> road[MAXN];
vector<par> load[MAXN][MAXT];
vector<par> drop[MAXN][MAXT];
vector<par> road_plus_load[MAXN];

int dp[MAXK+1][MAXN][MAXN][2];
int helper[MAXK+1][MAXN][MAXN];

int main(void) {
  char line[128];
  scanf("%d%d%d", &N, &E, &K); gets(line);
  for (int i = 0; i < E; ++i) {
    int A, B;
    char type;
    gets(line);
    int scanned = sscanf(line, "%d %d %c", &A, &B, &type); --A; --B;
    if (scanned == 2) {
      road[A].push_back(par(A, B));
      road_plus_load[A].push_back(par(A, B));
    } else if (isupper(type)) {
      load[A][type - 'A'].push_back(par(A, B));
      road_plus_load[A].push_back(par(A, B));
    } else {
      drop[B][type - 'a'].push_back(par(A, B));
    }
  }
  
  for (int i = 0; i < N; ++i)
    for (int flag = 0; flag < 2; ++flag) 
      dp[0][i][i][flag] = 1;
  
  int ret = 0;
  for (int k = 1; k <= K; ++k) {
    if (k >= 2)
      for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
          for (int t = 0; t < MAXT; ++t)
            FOR_EACH(it, load[i][t])
              FOR_EACH(jt, drop[j][t])
                ADD(helper[k][i][j], dp[k-2][it->second][jt->first][0]);
    
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        for (int flag = 0; flag < 2; ++flag) {
          vector<par> &roads = flag ? road_plus_load[i] : road[i];
          FOR_EACH(it, roads)
            ADD(dp[k][i][j][flag], dp[k-1][it->second][j][flag]);
          
          for (int t = 2; t <= k; ++t)
            for (int x = 0; x < N; ++x)
              ADD(dp[k][i][j][flag], helper[t][i][x] * dp[k-t][x][j][flag]);
        }
    
    ADD(ret, dp[k][0][N-1][1]);
  }
  printf("%d\n", ret);
  
  return 0;
}
