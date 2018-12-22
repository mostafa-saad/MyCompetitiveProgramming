#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

vector<pair<int, int> > b[300000];
int tim[300000];
int mid;

bool podjela(int x) {
  for (int i = 0; i < (int)b[x].size(); ++i)
    if (b[x][i].second <= mid) {
      int s = b[x][i].first;
      if (tim[s] == tim[x]) return false;
      if (tim[s] == 0) {
        tim[s] = 3 - tim[x];
        if (!podjela(s)) return false;
      }
    }
  return true;
}

int main () {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    b[--x].push_back(make_pair(--y, i));
    b[y].push_back(make_pair(x, i));
  }
  int lo = 0, hi = m - 1;
  while (lo < hi) {
    memset(tim, 0, sizeof tim);
    mid = (lo + hi) / 2;
    bool uspjeh = true;
    for (int i = 0; i < n; ++i)
      if (tim[i] == 0) {
        tim[i] = 1;
        if (!podjela(i)) {
          uspjeh = false;
          break;
        }
      }
    if (uspjeh) lo = mid + 1;
    else hi = mid;
  }
  printf("%d\n", lo + 1);
  return 0;
}
