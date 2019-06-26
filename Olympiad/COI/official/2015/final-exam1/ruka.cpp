#include <cstdio>
#include <cstring>
#include <cassert>

#include <algorithm>
#include <iostream>
#include <deque>
#include <map>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;

const int MAX = 100100;

int N, Q;
int dx[MAX], dy[MAX];

struct Loga {
  map<int, int> F;

  void update(int x, int w) {
    for (x += 2e8; x < 4e8; x += x&-x) F[x] += w;
  }

  int query(int x) {
    int ret = 0;
    for (x += 2e8; x > 0; x -= x&-x) ret += F[x];
    return ret;
  }
};

struct Trans {
  int add = 0;
  Loga L;
  deque<int> D;

  void push(int x) {
    L.update(x - add, 1);
    D.push_front(x - add);
  }
  
  void pop() {
    L.update(D.front(), -1);
    D.pop_front();
  }
  
  void update(int w) { add += w; }
  int count() { return L.query(-add); }
};

Trans Lx, Hx;
Trans Ly, Hy;

void push(int &px, int &py, int i) {
  Lx.push(min(px, px + dx[i]));
  Hx.push(max(px, px + dx[i]));
    
  Ly.push(min(py, py + dy[i]));
  Hy.push(max(py, py + dy[i]));
}

void pop() {
  Lx.pop(); Hx.pop();
  Ly.pop(); Hy.pop();
}

void update(int nx, int ny, int i) {
  Lx.update(nx - dx[i]);
  Hx.update(nx - dx[i]);

  Ly.update(ny - dy[i]);
  Hy.update(ny - dy[i]);
}

int segment(int px, int py, int i) {
  int ret = 0;
  if (min(px, px + dx[i]) < 0 && max(px, px + dx[i]) > 0) ++ret;
  if (min(py, py + dy[i]) < 0 && max(py, py + dy[i]) > 0) ++ret;
  return ret;
}

int main() {
  scanf("%d", &N);

  int px = 1, py = 1;
  REP(i, N) {
    scanf("%d%d", dx+i, dy+i);
    px += dx[i];
    py += dy[i];
  }

  for (int i = N-1; i >= 0; --i) {
    px -= dx[i];
    py -= dy[i];
    if (i) push(px, py, i);
  }

  int i = 0;
  int before = segment(px, py, i);

  scanf("%d", &Q);
  while (Q--) {
    char c; scanf(" %c", &c);
    
    if (c == 'B' && i > 0) {
      push(px, py, i);
      before -= segment(px, py, i--);
      px -= dx[i];
      py -= dy[i];
    }

    if (c == 'F' && i+1 < N) {
      pop();
      px += dx[i];
      py += dy[i];
      before += segment(px, py, ++i);
    }

    if (c == 'C') {
      int nx, ny; scanf("%d%d", &nx, &ny);
      update(nx, ny, i);
      before -= segment(px, py, i);
      dx[i] = nx;
      dy[i] = ny;
      before += segment(px, py, i);
    }

    if (c == 'Q') {
      int ans = before;
      ans += Lx.count() - Hx.count();
      ans += Ly.count() - Hy.count();
      printf("%d\n", ans);
    }
  }
  
  return 0;
}
