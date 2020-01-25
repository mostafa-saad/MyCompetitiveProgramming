#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 1010;

bool bio[MAXN][MAXN];

char grid[MAXN][MAXN];

int R, S, cnt;
int dr[] = {1, 0, -1, 0};
int ds[] = {0, 1, 0, -1};

vector<pair<int, int>> comp;

inline char other(char c) {
  if (c == 'T') return 'B';
  return 'T';
}

inline bool check(int r, int s) {
  return r >= 0 && r < R && s >= 0 && s < S && grid[r][s] == grid[0][0] &&
         !bio[r][s];
}

int floodfill() {
  queue<pair<int, int>> Q;
  vector<pair<int, int>> v;
  Q.push({0, 0});
  bio[0][0] = true;
  while (!Q.empty()) {
    auto curr = Q.front();
    Q.pop();
    v.push_back(curr);
    for (int i = 0; i < 4; ++i) {
      int r = curr.first + dr[i], s = curr.second + ds[i];
      if (check(r, s)) {
        bio[r][s] = true;
        Q.push({r, s});
      }
    }
  }
  char c = other(grid[0][0]);
  for (auto &p : v) {
    grid[p.first][p.second] = c;
    bio[p.first][p.second] = false;
  }
  return v.size();
}

int main(void) {
  scanf("%d%d", &R, &S);
  for (int i = 0; i < R; ++i) {
    scanf("%s", grid[i]);
    for (int j = 0; j < S; ++j)
      cnt += grid[i][j] != '*';
  }

  int sol = 1;
  while (floodfill() < cnt) ++sol;

  printf("%d\n", sol);
  return 0;
}
