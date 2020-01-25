#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 1010;

const int dr[] = {1, 0, -1, 0};
const int ds[] = {0, 1, 0, -1};

char grid[MAXN][MAXN];

int R, S, comp_cnt;
int comp[MAXN][MAXN];

set<pair<int, int>> E;
vector<vector<int>> v;

inline bool inside(int r, int s) {
  return r >= 0 && r < R && s >= 0 && s < S;
}

inline bool check(int r, int s) {
  return r >= 0 && r < R && s >= 0 && s < S && comp[r][s] == -1;
}

void bfs(int r, int s, int curr_comp) {
  queue<pair<int, int>> Q;
  comp[r][s] = curr_comp;
  Q.push({r, s});
  while (!Q.empty()) {
    auto curr = Q.front(); Q.pop();
    for (int i = 0; i < 4; ++i) {
      int rr = curr.first + dr[i], ss = curr.second + ds[i];
      if (check(rr, ss) && grid[rr][ss] == grid[r][s]) {
        comp[rr][ss] = comp[r][s];
        Q.push({rr, ss});
      }
    }
  }
}

int main(void) {
  scanf("%d%d", &R, &S);
  for (int i = 0; i < R; ++i)
    scanf("%s", grid[i]);

  memset(comp, -1, sizeof comp);

  for (int i = 0; i < R; ++i)
    for (int j = 0; j < S; ++j)
      if (comp[i][j] == -1 && grid[i][j] != '*')
        bfs(i, j, comp_cnt++);

  v.resize(comp_cnt);
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < S; ++j) {
      if (comp[i][j] == -1) continue;
      for (int k = 0; k < 4; ++k) {
        int ii = i + dr[k], jj = j + ds[k];
        if (!inside(ii, jj) || comp[ii][jj] == -1 || comp[ii][jj] == comp[i][j])
          continue;
        if (E.find({comp[i][j], comp[ii][jj]}) == E.end()) {
          E.insert({comp[i][j], comp[ii][jj]});
          v[comp[i][j]].push_back(comp[ii][jj]);
        }
      }
    }
  }

  vector<bool> bio(comp_cnt, false);
  queue<pair<int, int>> Q;
  bio[0] = true;
  Q.push({0, 1});
  int sol = 0;
  while (!Q.empty()) {
    auto curr = Q.front(); Q.pop();
    sol = max(sol, curr.second);
    for (int nxt : v[curr.first]) {
      if (bio[nxt]) continue;
      bio[nxt] = true;
      Q.push({nxt, curr.second + 1});
    }
  }

  printf("%d\n", sol);
  return 0;
}
