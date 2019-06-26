#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define MAXN 200005

int di[] = { 0, +1, -1 };

int N;
int x[MAXN];
int y[MAXN];
int d[MAXN];

int solx[MAXN];
int soly[MAXN];

struct event {
  int x, y1, y2;
  int id, type;
  event(int X, int Y1, int Y2, int T, int I, vector< int > &c) {
    y1 = lower_bound(c.begin(), c.end(), Y1) - c.begin();
    y2 = lower_bound(c.begin(), c.end(), Y2) - c.begin();
    x = X;
    id = I; type = T;
  }
  friend bool operator<(const event &a, const event &b) {
    if (a.x == b.x) return a.type < b.type;
    return a.x < b.x;
  }
};

vector< int > cx, cy;
vector< event > ex, ey;

const int off = 1 << 21;
int lo, hi;

int t[off << 1];
int m[off << 1];
int tx[2][off << 1];

void update(int l, int r, int d, int n) {
  if (l >= hi || r <= lo) return;
  if (l >= lo && r <= hi) {
    m[n] += d;
    return;
  }

  int L = 2 * n;
  int R = 2 * n + 1;

  update(l, (l + r) / 2, d, L);
  update((l + r) / 2, r, d, R);

  t[n] = t[L] + t[R];
  tx[0][n] = max(m[L] ? -1 : tx[0][L], m[R] ? -1 : tx[0][R]);
  tx[1][n] = max(m[L] ? -1 : tx[1][L], m[R] ? -1 : tx[1][R]);
}

int query(int l, int r, int n, int b) {
  if (m[n]) return -1;
  if (l >= hi || r <= lo) return -1;
  if (l >= lo && r <= hi) return m[n] ? -1 : tx[b][n];
  return max(query(l, (l + r) / 2, 2 * n, b),
             query((l + r) / 2, r, 2 * n + 1, b));
}

void add(int l, int r) { lo = l; hi = r + 1; update(0, off, +1, 1); }
void rem(int l, int r) { lo = l; hi = r + 1; update(0, off, -1, 1); }
int get(int l, int r, int b) { lo = l; hi = r + 1; return query(0, off, 1, b); }

void sweep(vector< event > &e, bool ix) {
  memset(t, 0, sizeof t);
  memset(m, 0, sizeof m);
  memset(tx, -1, sizeof tx);

  for (int i = 0; i < (ix ? cy.size() : cx.size()); ++i) {
    int it = off + i;
    int b = (((ix ? cy[i] : cx[i]) % 2) + 2) % 2;
    tx[b][it] = i;
    for (it /= 2; it; it /= 2)
      if (tx[b][it] == -1)
	tx[b][it] = i;
  }

  sort(e.begin(), e.end());

  for (int i = 0, j, k; i < e.size(); i = j) {
    for (j = i; j < e.size() && e[j].x == e[i].x; ++j);
    for (k = i; k < j && e[k].type == 0; ++k);

    for (int l = i; l < k; ++l) 
      rem(e[l].y1 + 1, e[l].y2 - 1);

    for (int l = i; l < j; ++l) {
      int y = get(e[l].y1, e[l].y2, ((e[l].x % 2) + 2) % 2);
      if (y == -1)  continue;

      if (ix) {
	solx[e[l].id] = e[l].x;
	soly[e[l].id] = cy[y];
      } else {
	solx[e[l].id] = cx[y];
	soly[e[l].id] = e[l].x;
      }
    }

    for (int l = k; l < j; ++l) 
      add(e[l].y1 + 1, e[l].y2 - 1);
  }
}

int main(void)
{
  scanf("%d", &N);

  for (int i = 0; i < N; ++i) 
    scanf("%d%d%d", x + i, y + i, d + i);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < 3; ++k) {
	cx.push_back(x[i] + y[i] + di[j] * d[i] + di[k]);
	cy.push_back(x[i] - y[i] + di[j] * d[i] + di[k]);
      }
    }
  }

  sort(cx.begin(), cx.end());
  sort(cy.begin(), cy.end());
  cx.resize(unique(cx.begin(), cx.end()) - cx.begin());
  cy.resize(unique(cy.begin(), cy.end()) - cy.begin());

  for (int i = 0; i < N; ++i) {
    int X = x[i] + y[i];
    int Y = x[i] - y[i];
    ex.push_back(event(X - d[i], Y - d[i], Y + d[i], 1, i, cy));
    ex.push_back(event(X + d[i], Y - d[i], Y + d[i], 0, i, cy));
    ey.push_back(event(Y - d[i], X - d[i], X + d[i], 1, i, cx));
    ey.push_back(event(Y + d[i], X - d[i], X + d[i], 0, i, cx));
  }

  sweep(ex, 1);
  sweep(ey, 0);

  for (int i = 0; i < N; ++i) 
    printf("%d %d\n", (solx[i] + soly[i]) / 2, (solx[i] - soly[i]) / 2);

  return 0;
}
