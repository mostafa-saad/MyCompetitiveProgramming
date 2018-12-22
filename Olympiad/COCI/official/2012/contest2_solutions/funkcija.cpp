#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 26;
const int MAXNUM = 100100;
const int MOD = 1000000007;

enum {ROOT, LEFT, RIGHT};
typedef long long llint;

struct node {
  int x, y, z;
  llint dp[MAXNUM];
  vector< node* > children;

  node() {}
  node(int _x, int _y, int _z) {
    x = _x, y = _y, z = _z;
    memset(dp, -1, sizeof dp);
  }

  llint solve(int from = 0) {
    llint &ret = dp[from];
    if (ret != -1) 
      return ret;
    ret = 0;
    
    if (z == ROOT) {
      for (int from = x; from <= y; ++from)
        ret = (ret + solve_for(from)) % MOD;
    }
    if (z == LEFT) {
      if (from > y)
        return ret;
      if (from < y)
        ret = solve(from + 1);
      ret = (ret + solve_for(from)) % MOD;
    }
    if (z == RIGHT) {
      if (from < x)
        return ret;
      if (from > x)
        ret = solve(from - 1);
      ret = (ret + solve_for(from)) % MOD;
    }

    return ret;
  }

  inline llint solve_for(int from) {
    llint ret = 1;
    for (vector< node* >::iterator it = children.begin(); it != children.end(); ++it)
      ret = (ret * (*it)->solve(from)) % MOD;
    return ret;
  }

} nodes[MAXN];

int main(void) {
  int n; 
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    char xi[10], yi[10];
    scanf("%s %s", xi, yi);
    int x = atoi(xi);
    int y = atoi(yi);
    int z;
    if (x && y) 
      z = ROOT;
    else if (y) {
      z = LEFT;
      nodes[xi[0] - 'a'].children.push_back(nodes + i);
    } else {
      z = RIGHT;
      nodes[yi[0] - 'a'].children.push_back(nodes + i);
    }
    nodes[i] = node(x, y, z);
  }

  llint ans = 1;
  for (int i = 0; i < n; ++i)
    if (nodes[i].z == ROOT)
      ans = (ans * nodes[i].solve()) % MOD; 

  printf("%lld\n", ans);
  return 0;
}
