#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

#define LOG(x) cerr << #x << " = " << (x) << "\n"

typedef long long llint;
typedef pair<int,int> pii;

const int MAXN = 710;
const int dx[] = { -1, 0, 0, 1 };
const int dy[] = { 0, -1, 1, 0 };

struct event { int y1, x1, y2, x2, k, l; };
struct change { 
  pii B, old_dad, A;
  int old_size;
};

bool cmp(const event &A, const event &B) {
  return (llint)A.l * B.k < (llint)B.l * A.k;
}

int n;
int l[MAXN][MAXN];
int k[MAXN][MAXN];
vector<event> events;

struct union_find {
  pii dad[MAXN][MAXN];
  int sz[MAXN][MAXN];
  vector<change> changes;

  union_find() { 
    for (int i = 0; i < MAXN; ++i)
      for (int j = 0; j < MAXN; ++j)
        dad[i][j] = {-1, -1}, sz[i][j] = 1;
  }

  pii find_dad(int y, int x, bool permanent=true) {
    if (dad[y][x].first == -1) return {y, x};
    pii new_dad = find_dad(dad[y][x].first, dad[y][x].second);
    if (permanent == false)
      changes.push_back({pii(y, x), dad[y][x], {-1, -1}, -1});
    return dad[y][x] = new_dad;
  }

  int merge_sets(int y1, int x1, int y2, int x2, bool permanent) {
    pii A = find_dad(y1, x1, permanent);
    pii B = find_dad(y2, x2, permanent);
    if (A == B) return sz[A.first][A.second];
    if (sz[A.first][A.second] < sz[B.first][B.second])
      swap(A, B);
    if (permanent == false)
      changes.push_back({B, dad[B.first][B.second], A, sz[A.first][A.second]});
    sz[A.first][A.second] += sz[B.first][B.second];
    dad[B.first][B.second] = A;
    return sz[A.first][A.second];
  }

  void restore() {
    reverse(changes.begin(), changes.end());
    for (const change &c : changes) {
      dad[c.B.first][c.B.second] = c.old_dad;
      if (c.A.first != -1)
        sz[c.A.first][c.A.second] = c.old_size;
    }
    changes.clear();
  }
} U;

void process_neighbours(int y1, int x1, int y2, int x2) {
  if (y2 < 0 || y2 >= n || x2 < 0 || x2 >= n) return;
  int k_diff = k[y2][x2] - k[y1][x1];
  int l_diff = l[y1][x1] - l[y2][x2];
  if (k_diff == 0) {
    if (l_diff == 0) U.merge_sets(y1, x1, y2, x2, true);
    return;
  }
  if (k_diff < 0) {
    l_diff = -l_diff;
    k_diff = -k_diff;
  }
  if (l_diff < 0) return;
  events.push_back({y1, x1, y2, x2, k_diff, l_diff});
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      scanf("%d", l[i]+j);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      scanf("%d", k[i]+j);

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      for (int d = 0; d < 2; ++d)
        process_neighbours(i, j, i+dy[d], j+dx[d]);

  int ans = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) { 
      U.find_dad(i, j);
      ans = max(ans, U.sz[i][j]);
    }

  sort(events.begin(), events.end(), cmp);
  for (int i = 0; i < (int)events.size(); ++i) {
    const event &e = events[i];
    ans = max(ans, U.merge_sets(e.y1, e.x1, e.y2, e.x2, false));
    if (i + 1 == (int)events.size() || cmp(e, events[i+1]))
      U.restore();
  }

  printf("%d\n", ans);
  return 0;
}
