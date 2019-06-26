#include <algorithm>

#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <stack>

using namespace std;

#define TRACE(x) cout << #x << " = " << x << endl
#define REP(i, n) for (int i = 0; i < (n); ++i)

typedef long long llint;

const int MAXN = 1000100;

const llint inf = 1e18;

struct loga {
  llint L[MAXN];

  void add(int x, llint v) {
    for (++x; x < MAXN; x += x&-x)
      L[x] += v;
  }
  
  llint sum(int x) {
    llint r = 0;
    for (++x; x > 0; x -= x&-x)
      r += L[x];
    return r;
  }
} L, Lcnt;

vector<int> vx[MAXN];

int x[MAXN], y[MAXN];
int h[MAXN];

int lastX[MAXN]; // lastX[y]

llint lt[MAXN], gt[MAXN];
int ltCnt[MAXN], gtCnt[MAXN];

llint f[MAXN];
int reconX[MAXN], reconY[MAXN];

int main(void) {
  int n, w, n_s, mjera;
  scanf("%d %d %d", &n, &n_s, &mjera);
  int last_x = -1;
  REP(i, n/2) {
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    assert(x1 < x2);
    assert(y1 == y2);
    for (int j = x1; j < x2; ++j)
      h[j] = y2;
    last_x = x2;
  }
  w = last_x;

  REP(i, n_s) {
    scanf("%d %d", x+i, y+i);
    vx[x[i]].push_back(y[i]);
  }
  
  llint total = 0, total_cnt = 0;
  auto addColumn = [&mjera, &total, &total_cnt] (int h) {
    if (mjera == 1) L.add(h, 1), total++; else
      L.add(h, h), total += h;
    Lcnt.add(h, 1), total_cnt++;
  };

  memset(lastX, -1, sizeof(lastX));

  f[0] = 0;
  for (int y: vx[0])
    lastX[y] = 0;
  addColumn(h[0]);

  for (int x = 1; x <= w; ++x) {
    f[x] = inf;

    for (int y: vx[x]) {
      int lx = lastX[y];

      llint lt_now = L.sum(y-1) - lt[y];
      llint gt_now = total-L.sum(y) - gt[y];
      
      int lt_now_cnt = Lcnt.sum(y-1) - ltCnt[y];
      int gt_now_cnt = total_cnt-Lcnt.sum(y) - gtCnt[y];
      
      if (lx != -1) {
        llint cost;
        if (mjera == 1) cost = lt_now_cnt + gt_now_cnt; else
          cost = gt_now - lt_now + llint(y)*(lt_now_cnt - gt_now_cnt);
        if (f[lx] + cost < f[x]) {
          f[x] = f[lx] + cost;
          reconX[x] = lx, reconY[x] = y;
        }
      }
      
      lastX[y] = x;
      lt[y] += lt_now, ltCnt[y] += lt_now_cnt;
      gt[y] += gt_now, gtCnt[y] += gt_now_cnt;
    }

    addColumn(h[x]);
  }
  
  if (f[w] >= inf) printf("-1\n"); else {
    printf("%lld\n", f[w]);

    static stack<int> hx, hy;
    int x = w, ly = 0, cnt = 0;
    while (x > 0) {
      int y = reconY[x], nx = reconX[x];
      if (y != ly) {
        hx.push(x), hy.push(y);
        hx.push(nx), hy.push(y);
        cnt += 2;
      } else {
        hx.pop(), hx.push(nx);
      }
      x = nx, ly = y;
    }

    printf("%d\n", cnt);
    while (!hx.empty()) {
      printf("%d %d\n", hx.top(), hy.top());
      hx.pop(), hy.pop();
    }
  }
  return 0;
}
