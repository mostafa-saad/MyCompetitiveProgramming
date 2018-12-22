#include <algorithm>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <array>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define TRACE(x) cout << #x << " = " << (x) << endl

typedef long long llint;

const int MAXN = 302; // !!!
const int MAXLOG = 9+1; // !!!!
const int inf = 1e9;

typedef array< array<int, MAXN>, MAXN> Graf;

int n;
Graf powMat[MAXLOG];

void combine(Graf &res, const Graf& A, const Graf& B) {
  REP(a, n) REP(b, n) {
    int val = inf;
    REP(c, n) val = min(val, A[a][c] + B[c][b]);
    res[a][b] = val;
  }
}

int min_el(const Graf& g) {
  int mini = inf;
  REP(a, n) mini = min(mini, g[a][a]);
  return mini;
}

int main(void)
{
  static Graf graf;

  int e; scanf("%d %d", &n, &e);
  REP(i, n) REP(j, n) graf[i][j] = inf;
  REP(i, n) graf[i][i] = 0;

  REP(i, e) {
    int a, b, w1, w2; scanf("%d %d %d %d", &a, &b, &w1, &w2); --a, --b;
    graf[a][b] = min(graf[a][b], w1-w2);
  }

  powMat[0] = graf;
  assert(min_el(powMat[0]) >= 0);
  int p; for (p = 1; p < MAXLOG; ++p) {
    combine(powMat[p], powMat[p-1], powMat[p-1]);
    if (min_el(powMat[p]) < 0) { ++p; break; }
  }
  assert(min_el(powMat[p-1]) < 0);

  int min_steps = 0;
  static Graf tmpG; // no clear

  REP(a, n) REP(b, n) graf[a][b] = (a == b) ? 0 : +inf;
  for (int i_p = p-1; i_p >= 0; --i_p) {
    combine(tmpG, graf, powMat[i_p]);
    if (min_el(tmpG) >= 0) {
      min_steps += (1<<i_p);
      graf = tmpG;
    } else {
      // pass
    }
  }

  combine(tmpG, graf, powMat[0]); ++min_steps;
  int best_cycle = min_el(tmpG);
  assert(best_cycle < 0);
  printf("%d %d\n", min_steps, -best_cycle);

  return 0;
}
