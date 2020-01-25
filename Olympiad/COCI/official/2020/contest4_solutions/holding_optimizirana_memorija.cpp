#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double lf;
typedef long double Lf;
typedef pair <int,int> pii;
typedef pair <ll, ll> pll;

#define TRACE(x) cerr << #x << "  " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)
#define all(x) (x).begin(), (x).end()
#define _ << " " <<

#define fi first
#define sec second
#define mp make_pair
#define pb push_back

const int MAXN = 110;
const int MAXK = MAXN * MAXN;
const int inf = (1 << 17);

int n, p[MAXN], L, R, K;
int dpL[MAXN][MAXK], dpR[MAXN][MAXK];

vector <int> dp[3][MAXK];

void compute(int t) {
  int left = L;
  int right = R;
  if (t) {
    left = n - R - 1;
    right = n - L - 1;
    reverse(p, p + n);
  }

  REP(i, 3) REP(j, MAXK) dp[i][j].clear();

  REP(k, K + 1) {
    dp[0][k].pb(-inf);
    FOR(i, 1, n) {
      if (i == left) dp[0][k].pb(0);
      else dp[0][k].pb(-inf);
    }
  }

  REP(k, K + 1) {
    REP(i, n) {
      if (i == left || i == left - 1) dp[1][k].pb(0);
      else dp[1][k].pb(-inf);
    }
  }

  FOR(len, 2, n + 1) {
    int x = len % 3;
    REP(k, K + 1) {
      dp[x][k].clear();
      REP(i, n - len + 1) {
        int j = i + len - 1;
        int curr = -inf;
        if (j > right || i >= left || j < left) {
          if (i == left && j >= left && j < right) curr = 0;
          if (j == left - 1 && i <= left) curr = 0;
          dp[x][k].pb(curr);
          continue;
        }
        curr = max(curr, dp[(x + 2) % 3][k][i + 1]);
        curr = max(curr, dp[(x + 2) % 3][k][i]);
        if (k - abs(i - j) >= 0) curr = max(curr, dp[(x + 1) % 3][k - abs(i - j)][i + 1] + p[j] - p[i]);
        dp[x][k].pb(curr);
        if (i == 0 && j >= left && j <= right) {
          if (t == 0) dpL[j][k] = curr;
          if (t == 1) dpR[n - j - 1][k] = curr;
        }
      }
    }
  }

  if (t) {
    reverse(p, p + n);
  }
}

int merge(int x) {
  int ret = 0;
  REP(k, K + 1) {
    int tmp = dpL[x][k];
    if (x + 1 <= R) tmp += dpR[x + 1][K - k];
    ret = max(ret, tmp);
  }
  return ret;
}

int main() {
  scanf("%d %d %d %d",&n,&L,&R,&K);
  L--; R--;
  REP(i, n) scanf("%d",&p[i]);

  REP(i, 2) compute(i);
  int sol = dpR[L][K];
  FOR(i, L, R + 1) sol = max(sol, merge(i));

  int sum = 0;
  FOR(i, L, R + 1) sum += p[i];
  printf("%d\n",sum - sol);
  return 0;
}

