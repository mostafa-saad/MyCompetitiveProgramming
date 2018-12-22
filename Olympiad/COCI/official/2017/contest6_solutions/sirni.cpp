#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define REP(i, n) for (int i=0; i<n; i++)
#define FOR(i, a, b) for (int i=(a); i<(b); i++)

typedef long long ll;
typedef pair<int, int> P;
#define X first
#define Y second

const int MAXN = 1<<19, MAXM = 1e7 + 5;

vector <P> V[MAXM];
int najbliz[MAXM];
int p[MAXN];
int n;
int root[MAXN], rnk[MAXN];
int bio[MAXM], ozn[MAXM];

int find(int x)
{
  if (root[x] == -1) return x;
  return root[x] = find(root[x]);
}

void merge(int a, int b)
{
  a = find(a);
  b = find(b);
  assert(a != b);

  if (rnk[a] > rnk[b]) root[b] = a;
  else if (rnk[b] > rnk[a]) root[a] = b;
  else {
    rnk[a]++;
    root[b] = a;
  }
}

int main()
{
  scanf("%d", &n);
  memset(ozn, -1, sizeof ozn);
  REP(i, n) {
    scanf("%d", &p[i]);
    najbliz[p[i]] = p[i];
    if (ozn[p[i]] == -1)
      ozn[p[i]] = i;
  }

  for (int i=MAXM-2; i>=0; i--)
    if (!najbliz[i])
      najbliz[i] = najbliz[i+1];

  REP(i, n) {
    if (bio[p[i]]++) continue;
    if (najbliz[p[i]+1]) {
      if (2*p[i] >= MAXM || najbliz[2*p[i]] != najbliz[p[i]+1])
        V[najbliz[p[i]+1] - p[i]].push_back(P(i, ozn[najbliz[p[i]+1]]));
    }

    for (int j=2*p[i]; j<MAXM && najbliz[j]; j+=p[i])
      if (j + p[i] >= MAXM || najbliz[j+p[i]] != najbliz[j])
        V[najbliz[j]-j].push_back(P(i, ozn[najbliz[j]]));
  }

  memset(root, -1, sizeof root);
  ll rje = 0;
  REP(i, MAXM)
    REP(j, (int) V[i].size())
    if (find(V[i][j].X) != find(V[i][j].Y)) {
      merge(V[i][j].X, V[i][j].Y);
      rje += i;
    }

  REP(i, n) if (ozn[p[i]] == i) { assert(find(i) == find(0)); }

  printf("%lld\n", rje);

  return 0;
}
