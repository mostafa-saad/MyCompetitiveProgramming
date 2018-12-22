#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>

using namespace std;
typedef long long llint;

const int MAXN = 50005;
const int MAXK = 31;

int n, k;
int x[MAXN], y[MAXN], c[MAXN];

bool cmp (int i, int j) {
  if (x[i] != x[j]) return x[i] < x[j];
  return y[i] < y[j];
}

struct edge{
  int x, y;
  llint d;
  edge (int x, int y, llint d) : x(x), y(y), d(d) {}
};

bool operator < (const edge &A, const edge &B) {
  return A.d < B.d;
}

inline llint sqr (llint x) { return x*x; }
inline llint distx (int i, int j) { return sqr(x[i] - x[j]); }
inline llint disty (int i, int j) { return sqr(y[i] - y[j]); }
inline llint dist (int i, int j) { return distx(i, j) + disty(i, j); }

vector <edge> E;

struct cmp_set {
  bool operator () (const int i, const int j) {
    if (y[i] != y[j]) return y[i] < y[j];
    return i < j;
  }
};

struct cmp_nth {
  int x;
  cmp_nth (int x) : x(x) {}
  bool operator () (const int i, const int j) {
    return dist(x, i) < dist(x, j);
  }
};

int dad[MAXN];
vector <int> comp[MAXN];
bool value[MAXN][MAXK];

inline int fastmod (int x) { return x < 0 ? x + k : x; }

void update (int x, int v) {
  int tmp[MAXK];
  for (int i = 0; i < k; ++i)
    if (value[x][i] || v == i || value[x][fastmod(i - v)]) tmp[i] = 1;
    else tmp[i] = 0;

  for (int i = 0; i < k; ++i)
    value[x][i] = tmp[i];
}

void merge (int x, int y) {
  x = dad[x]; y = dad[y];
  if (comp[x].size() > comp[y].size()) swap(x, y);
  for (auto v: comp[x]) {
    dad[v] = y;
    comp[y].push_back(x);
    update(y, c[v]);
  }

  comp[x].clear();
}


int main (void){
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) scanf("%d%d%d", &x[i], &y[i], &c[i]);
  for (int i = 0; i < n; ++i) c[i] %= k;

  vector <int> V;
  for (int i = 0; i < n; ++i) V.push_back(i);

  sort(V.begin(), V.end(), cmp);

  llint best = 1LL << 60LL;
  int last = 0;
  set <int, cmp_set> S;
  for (int i = 0; i < V.size(); ++i) {
    int curr = V[i];
    while (distx(V[last], curr) > best) S.erase(V[last++]);

    int d = sqrt(best);
    y[n] = y[curr] - d;
    auto it = S.lower_bound(n);
    vector <int> close;
    while (it != S.end() && y[curr] + d >= y[*it]){
      llint dd = dist(*it, curr);
      if (dd <= best) {
	close.push_back(*it);
	E.push_back(edge(*it, curr, dd));
      }
      ++it;
    }
    
    if (close.size() >= k) {
      nth_element(close.begin(), close.begin() + k-1, close.begin(), cmp_nth(curr));
      best = dist(close[k - 1], curr);
    }

    S.insert(V[i]);
  }

  for (int i = 0; i < n; ++i) {
    comp[i].push_back(i);
    dad[i] = i;
    value[i][c[i]] = 1;
  }

  sort(E.begin(), E.end());
  for (int i = 0; i < E.size(); ++i) {
    edge e = E[i];
    if (dad[e.x] == dad[e.y]) continue;
    merge(e.x, e.y);
    if (value[dad[e.x]][0]) {
      printf("%.3lf\n", sqrt(e.d));
      return 0;
    }
  }

  return 0;
}
