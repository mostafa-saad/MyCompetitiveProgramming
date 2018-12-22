// Autor: Gustav Matula

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long llint;
const llint inf = 1000000000000000000LL;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

const int MAXN = 300005;

int N, A, B;

vector< int > T[MAXN];
int dad[MAXN];

void explore(int i) {
  for (int j : T[i]) {
    if (j == dad[i]) continue;
    dad[j] = i;
    explore(j);
  }
}

int dp[MAXN];

int solve(int i, int dad, int cx, int cy) {
  dp[i] = 0;

  vector< int > c;
  for (int j : T[i]) {
    if (j == dad) continue;
    if (i == cx && j == cy) continue;
    if (i == cy && j == cx) continue;
    solve(j, i, cx, cy);
    c.push_back(dp[j]);
  }

  sort(c.rbegin(), c.rend());

  REP(j, (int)c.size())
    dp[i] = max(dp[i], c[j] + j + 1);

  return dp[i];
}

int delta(int i) {
  return 
    solve(A, 0, i, dad[i]) -
    solve(B, 0, i, dad[i]);
}

int calc(int i) {
  return max(solve(A, 0, i, dad[i]),
	     solve(B, 0, i, dad[i]));
}

int main(void) 
{
  scanf("%d%d%d", &N, &A, &B);
  
  REP(i, N - 1) {
    int a, b;
    scanf("%d%d", &a, &b);
    T[a].push_back(b);
    T[b].push_back(a);
  }

  vector< int > dads;
  explore(A);
  for (int i = B; i != A; i = dad[i])
    dads.push_back(i);

  int lo = 0, hi = (int)dads.size();
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (delta(dads[mid]) > 0)
      lo = mid + 1;
    else
      hi = mid;
  }

  int sol = calc(dads[lo]);
  if (lo) sol = min(sol, calc(dads[lo - 1]));
  if (lo + 1 < (int)dads.size()) sol = min(sol, calc(dads[lo + 1]));

  int d = lo;
  d = min(d, (int)dads.size() - lo);
  d = min(d, abs((int)dads.size() / 2 - lo));

  TRACE(d);
  TRACE(lo _ dads.size());

  printf("%d\n", sol);

  return 0;
}
