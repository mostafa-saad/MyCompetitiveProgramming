#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX = 2000001;
const int MAXCOORD = 1000000;
const int LSIZE = 2*MAXCOORD+3;
const int INF = 1<<29;

typedef pair<int, int> P;
typedef pair<P, P> Q;

int n;
int C[MAX][2];
int O[2][MAX];
int x[MAX];
int y[MAX];

struct cmp {
  int by;
  cmp(int _by) : by(_by) { }
  bool operator() (int a, int b) {
    return C[a][by] < C[b][by];
  }
};

inline int close(int a, int b, int K) {
  return abs(C[a][0]-C[b][0]) <= K && abs(C[a][1]-C[b][1]) <= K;
}

pair<int, int> solve(int K) {
  static int lo[2][MAX];
  static int hi[2][MAX];
  fill(lo[0], lo[0]+n, INF);
  fill(hi[0], hi[0]+n, -INF);
  fill(lo[1], lo[1]+n, INF);
  fill(hi[1], hi[1]+n, -INF);

  for (int k=0; k<=1; k++)
    for (int dir=-1; dir<=1; dir+=2) {
      int currlo = INF;
      int currhi = -INF;
      int first = dir==1?0:(n-1);
      for (int i=first, j=first; i >= 0 && i < n; i+=dir) {
        if (!close(O[k][i], O[k][first], K)) {
          lo[k][O[k][i]] = min(lo[k][O[k][i]], C[O[k][first]][k]);
          hi[k][O[k][i]] = max(hi[k][O[k][i]], C[O[k][first]][k]);
        }
        while (abs(C[O[k][j]][k]-C[O[k][i]][k]) > K) {
        currlo = min(currlo, C[O[k][j]][1-k]);
          currhi = max(currhi, C[O[k][j]][1-k]);
          j += dir;
        }
        lo[1-k][O[k][i]] = min(lo[1-k][O[k][i]], currlo);
        hi[1-k][O[k][i]] = max(hi[1-k][O[k][i]], currhi);
        if (j != first) {
          hi[k][O[k][i]] = max(hi[k][O[k][i]], C[O[k][j-dir]][k]);
          lo[k][O[k][i]] = min(lo[k][O[k][i]], C[O[k][j-dir]][k]);
        }
      }
    }

  vector<Q> events;
  for (int i=0; i<n; i++) {
    events.push_back(Q(P(C[i][0], 1), P(C[i][1], i)));

    int lox = hi[0][i]-K;
    int loy = max(0, hi[1][i]-K);
    int hix = lo[0][i]+K;
    int hiy = min(LSIZE-2, lo[1][i]+K);
    if (lox > hix || loy > hiy)
      continue ;

    events.push_back(Q(P(lox, 0), P(loy, 1)));
    events.push_back(Q(P(lox, 0), P(hiy+1, -1)));
    events.push_back(Q(P(hix, 2), P(loy, -1)));
    events.push_back(Q(P(hix, 2), P(hiy+1, 1)));
  }
  sort(events.begin(), events.end());
  
  static int l[LSIZE];
  memset(l, 0, sizeof l);
  for (int i=0; i<(int)events.size(); i++) {
    int type = events[i].first.second;
    int target = events[i].second.first+1;
    int delta = events[i].second.second;
    if (type == 1) {
      int c = 0;
      for (int j=target; j>0; j-=j&(-j))
        c += l[j];
      if (c > 0)
        return P(delta, -1);
      continue ;
    }
    for (int j=target; j<2*MAXCOORD+1; j+=j&(-j))
      l[j] += delta;
  }

  return P(-1, -1);
}

int find_other(int a, int K) {
  int lox = INF;
  int hix = -INF;
  int loy = INF;
  int hiy = -INF;
  for (int i=0; i<n; i++)
    if (!close(a, i, K)) {
      lox = min(lox, C[i][0]);
      hix = max(hix, C[i][0]);
      loy = min(loy, C[i][1]);
      hiy = max(hiy, C[i][1]);
    }
  for (int i=0; i<n; i++)
    if (C[i][0] >= hix-K && C[i][0] <= lox+K && C[i][1] >= hiy-K && C[i][1] <= loy+K)
      return i;
  return -1;
}

int dist(int a, int b) {
  return max(abs(x[a]-x[b]), abs(y[a]-y[b]));
}

void solve1() {
  scanf("%d", &n);
  for (int i=0; i<n; i++) {
    int X, Y;
    scanf("%d%d", &X, &Y);
    x[i] = X+Y;
    y[i] = X-Y;
  }
  int lx, hx, ly, hy;
  lx = hx = ly = hy = 0;
  for (int i=0; i<n; i++) {
    if (x[i] < x[lx])
      lx = i;
    if (x[i] > x[hx])
      hx = i;
    if (y[i] < y[ly])
      ly = i;
    if (y[i] > y[hy])
      hy = i;
  }
  int sol = 0;
  int best = max(dist(sol, hx), max(dist(sol, lx), max(dist(sol, hy), dist(sol, ly))));
  for (int i=1; i<n; i++) {
      int curr = max(dist(i, hx), max(dist(i, lx), max(dist(i, hy), dist(i, ly))));
      if (curr < best) {
	best = curr;
	sol = i;
      }
  }
  printf("%d\n%d\n", best, sol+1);
}

int main() {
  int k;
  scanf("%d", &k);
  if (k == 1) {
    solve1();
    return 0;
  }  
  scanf("%d", &n);
  for (int i=0; i<n; i++) {
    int X, Y;
    scanf("%d%d", &X, &Y);
    C[i][0] = X-Y;
    C[i][1] = X+Y;                             
  }

  for (int i=0; i<n; i++)
    O[0][i] = O[1][i] = i;
  sort(O[0], O[0]+n, cmp(0));
  sort(O[1], O[1]+n, cmp(1));

  pair<int, int> p;
  int lo = 0;
  int hi = INF;
  while (lo+1 < hi) {
    int mid = (lo+hi)/2;
    p = solve(mid);
    if (p.first == -1)
      lo = mid;
    else
      hi = mid;
  }
  p = solve(hi);
  p.second = find_other(p.first, hi);
  printf("%d\n%d %d\n", hi, p.first+1, p.second+1);
  return 0;
}
