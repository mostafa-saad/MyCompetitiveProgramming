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

const int MAX = 3000100;

struct node {
  int br, dp;
  vector <pair<char, node*> > V;
  node() {
    br = dp = 0;
    V.clear();
  }
} *root;

char s[MAX];
int rje = 0;

void insert()
{
  int len = (int) strlen(s);
  node *tmp = root;
  REP(i, len) {
    node *nov = 0;
    for (auto it : tmp->V)
      if (it.X == s[i]) {
        nov = it.Y;
        break;
      }

    if (!nov) {
      nov = new node;
      tmp->V.push_back({s[i], nov});
    }
    tmp = nov;
  }

  tmp->br = 1;
}

void dfs(node *p)
{
  P mx{0, 0};
  int ima = 0;

  for (auto it : p->V) {
    dfs(it.Y);
    ima += it.Y->br;
    mx = max(mx, P(mx.X, it.Y->dp));
    mx = max(mx, P(it.Y->dp, mx.X));

    p->dp = max(p->dp, it.Y->dp);
  }

  if (p->br) p->dp += 1 + max(0, ima-1);
  else p->dp = 0;

  rje = max(rje, mx.X + mx.Y + p->br + max(0, ima - 2));
}

int main()
{
  root = new node;

  int n;
  scanf("%d", &n);
  REP(i, n) {
    scanf("%s", s);
    reverse(s, s + strlen(s));
    insert();
  }

  dfs(root);
  printf("%d\n", rje);

  return 0;
}
