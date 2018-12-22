#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define REP(i, n) for (int i=0; i<n; i++)
#define FOR(i, a, b) for (int i=a; i<b; i++)

typedef long long ll;
typedef pair<int, int> P;
#define X first
#define Y second

const int MAX = 405, MAXK = 20;

int n, k;
vector <int> V[MAX];
vector <int> Q[MAX];
int disc_list[MAX], fin_list[MAX];
int dub[MAX];
int vr;
char dp[MAX][1<<MAXK];

void dfs(int node, int prosli)
{
  if (node)
    dub[node] = dub[prosli] + 1;

  if (dub[node] == k - 1) {
    disc_list[node] = vr++;
    fin_list[node] = vr;
    return;
  }

  disc_list[node] = vr;

  for (auto it : V[node])
    if (it != prosli)
      dfs(it, node);

  fin_list[node] = vr;
}

int rijesi()
{
  dp[0][0] = 1;

  FOR(i, 1, n)
    Q[disc_list[i]].push_back(i);

  REP(i, vr) {
    REP(j, (1<<k)) {
      if (!dp[i][j])
        continue;

      for (auto it : Q[i])
        if (!(j >> dub[it] & 1))
          dp[fin_list[it]][j | (1<<dub[it])] = 1;
    }
  }

  REP(j, (1<<k))
    if (dp[vr][j])
      return 1;

  return 0;
}

int main()
{
  scanf("%d%d", &n, &k);

  if (k * k >= n) {
    printf("DA\n");
    return 0;
  }

  REP(i, n-1) {
    int a, b;
    scanf("%d%d", &a, &b); a--; b--;
    V[a].push_back(b);
    V[b].push_back(a);
  }

  dub[0] = -1;
  dfs(0, -1);
  
  printf("%s\n", rijesi() ? "DA" : "NE");

  return 0;
}

