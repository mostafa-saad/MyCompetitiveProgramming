#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#define rep(i,n) for (int i = 0; i < n; ++i)
using namespace std;
typedef vector<int> VI;
typedef vector<VI > VVI;

const int INF = 1001001001;
const int di[] = {-1,0,1,0}, dj[] = {0,-1,0,1}; //^<v>

int h, w;
VVI used, dv;
int dfs(int i, int j, int v) {
  if (used[i][j] == 1) return INF;
  if (used[i][j] == 2) return 0;
  int res = 2;
  used[i][j] = 1;
  rep(k,2) {
    int nv = v^(dv[i][j]*k);
    int ni = i + di[nv], nj = j + dj[nv];
    if (ni < 0 || nj < 0 || ni >= h || nj >= w) continue;
    int r = dfs(ni,nj,nv);
    if (r == INF) return INF;
    res += r;
  }
  used[i][j] = 2;
  return res;
}

int main() {
  cin >> h >> w;
  vector<string> s(h);
  rep(i,h) cin >> s[i];
  dv = VVI(h, VI(w));
  rep(i,h)rep(j,w) dv[i][j] = (s[i][j] == 'Z') ? 1 : 3;
  VVI ans(h, VI(w, INF));
  rep(j,w)for (int v = 0; v <= 2; v += 2) {
    used = VVI(h, VI(w));
    int sum = 0;
    rep(i,h) {
      int si = i;
      if (v == 2) si = h-1-i;
      int res = dfs(si,j,v);
      if (res == INF) break;
      sum += res;
      ans[si][j] = min(ans[si][j], sum);
    }
  }
  rep(i,h)rep(j,w) if (ans[i][j] == INF) ans[i][j] = -1;
  rep(i,h)rep(j,w) printf("%d%c", ans[i][j], (j == w-1) ? '\n' : ' ');
  return 0;
}

