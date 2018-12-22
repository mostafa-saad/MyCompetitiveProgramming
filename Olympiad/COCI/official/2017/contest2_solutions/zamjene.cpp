#include <cstdio>
#include <iostream>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;
using llint = long long;

const int MAXN = 1000010;

const int HASH = 1234577;
const int MOD = 1e9 + 7;

int n, q, p[MAXN], r[MAXN], father[MAXN], nodes[MAXN], tot_merges;
llint powb[MAXN], idx[MAXN], val[MAXN], sol;
map<llint, int> diff_nodes;
llint tot_pairs;

void add_nodes(int sgn, llint diff, int m) {
  if (diff != 0) {
    tot_pairs += sgn * m * diff_nodes[-diff];
    // printf("diff = %lld\n",diff);
    // printf("... %d\n",diff_nodes[-diff]);
  }
  diff_nodes[diff] += sgn * m;
}

int dad(int x) {
  if (x == father[x]) return x;
  return father[x] = dad(father[x]);
}

void merge(int u, int v) {
  u = dad(u);
  v = dad(v);
  if (u == v)
    return;
  ++tot_merges;

  add_nodes(-1, idx[u] - val[u], nodes[u]);
  add_nodes(-1, idx[v] - val[v], nodes[v]);
  
  father[v] = u;
  idx[u] += idx[v];
  val[u] += val[v];
  nodes[u] += nodes[v];

  add_nodes(1, idx[u] - val[u], nodes[u]);
}

void add(int sgn, int u, int pos, int value) {
  idx[u] += sgn * powb[pos];
  val[u] += sgn * powb[value];
  nodes[u] += sgn;
}

void init(void) {
  scanf("%d %d",&n,&q);
  
  powb[0] = 1;
  for (int i = 1; i < MAXN; ++i)
    powb[i] = powb[i - 1] * HASH;
  
  for (int i = 1; i <= n; ++i) {
    scanf("%d",&p[i]);
    r[i] = p[i];
    father[i] = i;
    nodes[i] = 1;
  }
  sort(r + 1, r + n + 1);
  
  for (int i = 1; i <= n; ++i) {
    idx[i] = powb[r[i]];
    val[i] = powb[p[i]];
    //printf("%d ---> %d %d\n",i,r[i],p[i]);
    //printf("====== %lld %lld\n",powb[r[i]],powb[p[i]]);
    add_nodes(1, idx[i] - val[i], nodes[i]);
  }
}

int main(void) {
  init();
  while (q-- > 0) {
    int t, a, b;
    scanf("%d",&t);
    if (t == 1) {
      scanf("%d %d",&a,&b);
      int u = dad(a), v = dad(b);
      if (u == v) {
	swap(p[a], p[b]);
	continue;
      }
      
      add_nodes(-1, idx[u] - val[u], nodes[u]);
      add_nodes(-1, idx[v] - val[v], nodes[v]);
      add(-1, dad(a), a, p[a]);
      add(-1, dad(b), b, p[b]);
      
      swap(p[a], p[b]);

      add(1, dad(a), a, p[a]);
      add(1, dad(b), b, p[b]);
      add_nodes(1, idx[u] - val[u], nodes[u]);
      add_nodes(1, idx[v] - val[v], nodes[v]);
    } else if (t == 2) {
      scanf("%d %d",&a,&b);
      merge(a, b);
    } else if (t == 3) {
      printf(diff_nodes[0] == n ? "DA\n" : "NE\n");
    } else {
      printf("%lld\n",tot_pairs);
    }
  }
  
  return 0;
}
