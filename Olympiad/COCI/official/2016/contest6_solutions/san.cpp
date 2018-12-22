#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cassert>

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR (i, 0, (n))
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

using namespace std;

typedef long long llint;

const llint INF = 1e15;

vector<pair<llint, llint>> tmp, nums;

llint P[15];
int comb1[2][20];
int comb2[2][20];

llint f(llint x) {
  static char tmp[20];
  sprintf(tmp, "%lld", x);
  reverse(tmp, tmp+strlen(tmp));
  llint y;
  sscanf(tmp, "%lld", &y);
  return x+y;
}

void init(void) {
  P[0] = 1;
  FOR (i, 1, 15) P[i] = P[i-1] * 10;

  for (int a = 0; a <= 9; ++a) {
    ++comb1[0][a+a];
    if (a) ++comb1[1][a+a];
    for (int b = 0; b <= 9; ++b) {
      ++comb2[0][a+b];
      if (a) ++comb2[1][a+b];
    }
  }
}

void gen(int len, int pos, int c1, int c2, llint num, int w) {
  if (pos == len/2) {
    if (len % 2 == 0) {
      if (c1 == c2)
        tmp.push_back({num, w});
      return;
    }

    for (int d = 0; d <= 18; d += 2) {
      int nw = w * comb1[!pos][d];
      if (nw == 0) continue;

      llint nnum = num + P[pos] * ((d+c2) % 10);

      if (c1) {
        if (d+c2 <= 9) continue;
        tmp.push_back({nnum, nw}); 
      } else {
        if (d+c2 >= 10) continue;
        tmp.push_back({nnum, nw});
      }
    }
    return;
  }

  for (int d = 0; d <= 18; ++d) {
    int nw = w * comb2[!pos][d];
    if (nw == 0) continue;

    int nc2 = d+c2 >= 10;
    llint nnum = num + P[pos] * ((d+c2)%10) + P[len-pos-1] * (d%10),
          nnum_c = num + P[pos] * ((d+c2)%10) + P[len-pos-1] * ((d+1)%10);

    if (c1) {
      if (d < 9) continue;
      gen(len, pos+1, 1, nc2, nnum_c, nw);
      if (d >= 10) gen(len, pos+1, 0, nc2, nnum, nw);
    } else {
      if (d >= 10) continue;
      gen(len, pos+1, 0, nc2, nnum, nw);
      if (d < 9) gen(len, pos+1, 1, nc2, nnum_c, nw);
    }
  }
}

int main(void) {
  init();

  tmp.reserve(4e6);
  nums.reserve(4e6);

  for (int len = 1; len <= 10; ++len) {
    gen(len, 0, 0, 0, 0, 1);
    gen(len, 0, 1, 0, P[len], 1);
  }

  sort(tmp.begin(), tmp.end());

  for (auto p: tmp) {
    if (nums.empty() || p.first != nums.back().first)
      nums.push_back(p);
    else
      nums.back().second += p.second;
  }

  for (int i = 0; i < (int)nums.size(); ++i) {
    auto p = nums[i];
    llint t = f(p.first);
    auto it = lower_bound(nums.begin(), nums.end(), make_pair(t, -1ll));
    it->second += p.second;
    if (i > 0) nums[i].second += nums[i-1].second;
  }

  int q;
  scanf("%d", &q);
  REP (i, q) {
    llint l, r;
    scanf("%lld%lld", &l, &r);
    auto lo = lower_bound(nums.begin(), nums.end(), make_pair(l, -1ll)), 
         hi = upper_bound(nums.begin(), nums.end(), make_pair(r, INF));
    llint ans = 0;
    if (hi != nums.begin()) ans += (hi-1)->second;
    if (lo != nums.begin()) ans -= (lo-1)->second;
    printf("%lld\n", ans + (r-l+1));
  }

  return 0;
}
