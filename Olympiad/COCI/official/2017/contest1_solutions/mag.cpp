// zadatak Mag, 1. kolo
// Domagoj Bradac

#include <bits/stdc++.h>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> P;
#define X first
#define Y second
#define TRACE(x) cerr << #x << " " << x << endl;

const int MAX = 1<<20;

bool manji(const P &a, const P &b)
{
  return (long long) a.X * b.Y < (long long) a.Y * b.X;
}

int p[MAX];
int dpup[MAX], dpdown[MAX];
vector <int> L[MAX], R[MAX];
int pozl[MAX], pozr[MAX];
vector <int> V[MAX];
P rje = P(1e9, 1);

void dfsdown(int node, int par)
{
  L[node].push_back(0);
  for (auto it : V[node]) {
    if (it != par) {
      dfsdown(it, node);
      pozl[it] = (int) L[node].size() - 1;
      L[node].push_back(max(L[node].back(), p[it] == 1 ? dpdown[it] + 1 : 0));
    }
  }
  
  R[node].push_back(0);
  for (int i=(int) V[node].size()-1; i>=0; i--) {
    int it = V[node][i];
    if (it != par) {
      pozr[it] = (int) R[node].size() - 1;
      R[node].push_back(max(R[node].back(), p[it] == 1 ? dpdown[it] + 1 : 0));
    }
  }

  dpdown[node] = L[node].back();
}

void dfsup(int node, int par)
{
  if (node) {
    dpup[node] = (p[par] == 1 ? (1 + max(dpup[par], max(L[par][pozl[node]], R[par][pozr[node]]))) : 0);
  }
  
  P a = P(p[node], 1);
  if (manji(a, rje))
    rje = a;
  int mx = dpup[node];
   
  for (auto it : V[node]) {
    if (it == par)
      continue;
    
    int val = (p[it] == 1 ? dpdown[it] + 1 : 0);
    P tmp = P(p[node], 1 + mx + val);
    if (manji(tmp, rje))
      rje = tmp;
    mx = max(mx, val);
    dfsup(it, node);
  }
}

int main()
{
  int n;
  scanf("%d", &n);

  for (int i=0; i<n-1; i++) {
    int a, b;
    scanf("%d%d", &a, &b); a--; b--;
    V[a].push_back(b);
    V[b].push_back(a);
  }

  for (int i=0; i<n; i++)
    scanf("%d", &p[i]);

  dfsdown(0, -1);
  dfsup(0, -1);

  int gc = __gcd(rje.X, rje.Y);
  // TRACE(rje.X); TRACE(rje.Y);
  printf("%d/%d\n", rje.X / gc, rje.Y / gc);

  return 0;
}
