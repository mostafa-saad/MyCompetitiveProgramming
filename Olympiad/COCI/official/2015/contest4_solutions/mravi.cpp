#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAXN 100000
typedef long long llint;

struct pipe{
  int next, flow, square;
  pipe() {}
  pipe(int next, int flow, int square): next(next), flow(flow), square(square) {}
};

vector<pipe> tree[MAXN];
int K[MAXN];

bool calc(int node, int dad, double current){
  if (current < K[node]) return false;
  int d = tree[node].size();

  for (int i=0; i<d; i++){
    int next = tree[node][i].next; if (next == dad) continue;

    double new_current = (current*tree[node][i].flow)/100;
    if (tree[node][i].square && new_current >= 1) new_current *= new_current;

    if (!calc(next, node, new_current)) return false;
  }

  return true;
}

int main(void){
  int n; scanf ("%d", &n);
  for (int i=0; i<n-1; i++){
    int a, b, c, t; scanf ("%d%d%d%d", &a, &b, &c, &t); a--; b--;
    tree[a].push_back(pipe(b, c, t));
    tree[b].push_back(pipe(a, c, t));
  }
  for (int i=0; i<n; i++) scanf ("%d", &K[i]);

  double lo = 0, hi = 2e9;
  for (int i=0; i<100; i++){
    double mid = (lo + hi) / 2;
    if (calc(0, -1, mid)) hi = mid;
    else                  lo = mid;
  }
  printf ("%.4lf\n", lo);

  return 0;
}
