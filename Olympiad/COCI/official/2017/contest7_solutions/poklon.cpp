#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR (i, 0, n)
#define _ << " _ " <<
#define TRACE(x) cerr << #x << " = " << x << endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
//#define debug
//#define TRACE(x)

using namespace std;

typedef long long llint;

const int MAXN = 2000010;

int n, w[MAXN], m, best[MAXN];
vector<int> e[MAXN];

void dfs(int x, int depth) {
  if (x >= n)
    best[depth] = max(best[depth], w[x]);
  else {
    dfs(e[x][0], depth + 1);
    dfs(e[x][1], depth + 1);
  }
}

int main(void) {
  memset(best, -1, sizeof(best));
  scanf("%d",&n);
  m = n;
  REP(i, n) {
    int a, b;
    scanf("%d %d",&a,&b);
    
    if (a > 0) 
      e[i].push_back(a - 1);
    else {
      w[m] = -a;
      e[i].push_back(m++);
    }

    if (b > 0)
      e[i].push_back(b - 1);
    else {
      w[m] = -b;
      e[i].push_back(m++);
    }
  }

  dfs(0, 0);
  
  int sol = -1, sol_depth = -1;
  REP(i, MAXN)
    if (best[i] != -1) {
      bool ok = false;
      if (sol == -1) {
	ok = true;
      } else {
	int q = (sol + best[i] - 1) / best[i];
	int pow2 = 1;
	REP(it, i - sol_depth) {
	  pow2 *= 2;
	  if (q <= pow2) {
	    ok = true;
	    break;
	  }
	}
      }
      
      if (ok) {
	sol = best[i];
	sol_depth = i;
      }
    }

  vector<int> ans;
  REP(i, sol_depth) ans.push_back(0);
  for (; sol > 0; sol /= 2) ans.push_back(sol & 1);

  reverse(ans.begin(), ans.end());
  REP(i, (int)ans.size()) printf("%d",ans[i]);
  printf("\n");
  
  return 0;
}
