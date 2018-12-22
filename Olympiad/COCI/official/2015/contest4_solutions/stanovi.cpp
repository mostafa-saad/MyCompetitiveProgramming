#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

typedef long long llint;

const llint inf = 1e18;
const int MaxN = 308;

int A, B, K;
llint dp[MaxN][MaxN][2][2][2][2];

llint sqr (int x) { return (llint)x * x; }
llint f (int a, int b) { return sqr(a * b - K); }

llint solve (int a, int b, int L, int R, int U, int D) {
  if (L && R && U && D) return inf;
  if (dp[a][b][L][R][U][D] != -1) return dp[a][b][L][R][U][D];
  if (a > b) return dp[a][b][L][R][U][D] = solve(b, a, U, D, R, L);
  if (L > R) return dp[a][b][L][R][U][D] = solve(a, b, R, L, U, D);
  if (U > D) return dp[a][b][L][R][U][D] = solve(a, b, L, R, D, U);
  
  llint ret = f(a, b);
  if (a >= 2 && solve(1, b, L, 1, U, D) + solve(a - 1, b, 1, R, U, D) < inf)
    for (int k = 1; k <= a - 1; ++k)
      ret = min(ret, solve(k, b, L, 1, U, D) + solve(a - k, b, 1, R, U, D));

  if (b >= 2 && solve(a, 1, L, R, 1, D) + solve(a, b - 1, L, R, U, 1) < inf)
    for (int k = 1; k <= b - 1; ++k)
      ret = min(ret, solve(a, k, L, R, 1, D) + solve(a, b - k, L, R, U, 1));

  return dp[a][b][L][R][U][D] = ret;
}

void rec (int a1, int b1, int a2, int b2, int L, int R, int U, int D) {
  if (L && R && U && D) {
    printf("aaaa");
    return;
  }
  int a = a2 - a1, b = b2 - b1;
  llint ret = solve(a, b, L, R, U, D);

  if (ret == f(a, b)) {
    printf("%d %d %d %d\n",a1,b1,a2,b2);
    return;
  }
  for (int k = 1; k <= a - 1; ++k)
    if (ret == solve(k, b, L, 1, U, D) + solve(a - k, b, 1, R, U, D)) {
      rec(a1, b1, a1 + k, b2, L, 1, U, D);
      rec(a1 + k, b1, a2, b2, 1, R, U, D);
      return;
    }
  for (int k = 1; k <= b - 1; ++k)
    if (ret == solve(a, k, L, R, 1, D) + solve(a, b - k, L, R, U, 1)) {
      rec(a1, b1, a2, b1 + k, L, R, 1, D);
      rec(a1, b1 + k, a2, b2, L, R, U, 1);
      return;
    }
}

int main (void) {
  memset(dp, -1, sizeof(dp));
  scanf("%d %d %d",&A,&B,&K);
 
  printf("%lld\n",solve(A,B,0,0,0,0));
  //printf("%d %d\n",A,B);
  //rec(0,0,A,B,0,0,0,0);
  return 0;
}
