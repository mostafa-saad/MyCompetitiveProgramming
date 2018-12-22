#include <cstdio>
#include <iostream>
#include <cstring>
#include <bitset>
#include <vector>

#define lo first
#define hi second

using namespace std;

using interval = pair<int, int>;

const int MAXN = 10010;
const int MAXK = 110;

int n, v[MAXN];
vector<int> e[MAXN];

vector<interval> s[MAXN];
vector<int> q[MAXK];
bitset<MAXK> flag[MAXN][MAXK];

void dfs(int x) {
  for (auto y : e[x]) 
    dfs(y);

  for (int i = 0; i < MAXK; ++i)
    q[i].clear();
  for (auto y : e[x]) {
    for (auto it : s[y])
      q[it.lo].push_back(it.hi);
  }
  
  for (int lo = MAXK - 1; lo >= 1; --lo) {
    if (lo == v[x]) {
      flag[x][lo] |= flag[x][lo + 1];
      flag[x][lo].set(lo);
    } else {
      for (auto hi : q[lo]) {
      	if (hi < v[x] || lo > v[x]) {
      	  flag[x][lo] |= flag[x][hi + 1];
      	  flag[x][lo].set(hi);
      	}
      }
    }

    for (int hi = MAXK - 1; hi >= lo; --hi)
      if (flag[x][lo].test(hi) && v[x] >= lo && v[x] <= hi) {
    	s[x].emplace_back(lo, hi);
      }
  }
}

void init(void) {
  scanf("%d",&n);
  for (int i = 0; i < n; ++i)
    scanf("%d",&v[i]);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    scanf("%d %d",&a,&b);
    --a;
    --b;
    e[a].push_back(b);
  }
}

void solve(void) {
  dfs(0);
  printf("%d\n",s[0].size());
}

int main(void) {
  init();
  solve();
  return 0;
}
