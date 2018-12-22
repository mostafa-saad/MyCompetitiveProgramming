#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 16;
const int MAXL = 1 << 20;
const int inf = 1 << 30;

int n;
char str[MAXN][MAXL];
int cnt[MAXN][26];
int dp[1 << MAXN];

int calc_pref(int mask) {
  int len = 0;
  int tmp[26];
  fill(tmp, tmp+26, inf);
  for (int i = 0; i < n; ++i)
    if (mask&(1 << i))
      for (int j = 0; j < 26; ++j)
	tmp[j] = min(tmp[j], cnt[i][j]);

  for (int i = 0; i < 26; ++i)
    len += tmp[i];
  return len;
}


int solve(int mask) {
  int &ret = dp[mask];
  if (ret != -1) return ret;
  int pref = calc_pref(mask);
  if ((mask&-mask) == mask) return ret = pref;
  ret = inf;
  for (int i = (mask - 1) & mask; i > 0; i = (i - 1) & mask) {
    int curr = solve(i) + solve(mask ^ i) - pref;
    ret = min(ret, curr);
  }
  return ret;
}

int main (void){
  memset(dp, -1, sizeof dp);
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) 
    scanf("%s", str[i]);

  for (int i = 0; i < n; ++i)
    for (int j = 0; str[i][j]; ++j)
      cnt[i][str[i][j] - 'a']++;

  printf("%d\n", solve((1 << n)-1) + 1);

  return 0;
}
