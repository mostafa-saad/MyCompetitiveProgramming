#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 2e5 + 10;

struct Query {
  bool print;
  int x, y;
  Query() {}
  Query(bool print, int x, int y) : print(print), x(x), y(y) {}
};

struct Node {
  set<int> ids;
  Node *zero, *one;
  Node () {
    zero = one = NULL;
  }
} root;

int q, n, t;
int l[MAXN], r[MAXN], rxor[MAXN];

vector<pair<int, int>> v[MAXN];
vector<Query> Q;

void dfs(int node, int dad, int xval) {
  l[node] = ++t;
  rxor[node] = xval;
  for (const auto &p : v[node]) {
    int nxt = p.first;
    int w = p.second;
    if (nxt == dad) continue;
    dfs(nxt, node, xval ^ w);
  }
  r[node] = t;
}

void trie_add(Node *node, int bit, int val, int id) {
  node->ids.insert(id);
  if (bit < 0) return;
  if (val & (1 << bit)) {
    if (node->one == NULL) node->one = new Node();
    trie_add(node->one, bit - 1, val, id);
  } else {
    if (node->zero == NULL) node->zero = new Node();
    trie_add(node->zero, bit - 1, val, id);
  }
}

int trie_get(Node *node, int bit, int val, int from, int to) {
  if (bit < 0) return 0;
  if ((val & (1 << bit)) == 0) { // want 1
    if (node->one == NULL ||
        node->one->ids.lower_bound(from) == node->one->ids.upper_bound(to))
      return trie_get(node->zero, bit - 1, val, from, to);
    else
      return (1 << bit) + trie_get(node->one, bit - 1, val, from, to);
  } else { // want 0
    if (node->zero == NULL ||
        node->zero->ids.lower_bound(from) == node->zero->ids.upper_bound(to))
      return trie_get(node->one, bit - 1, val, from, to);
    else
      return (1 << bit) + trie_get(node->zero, bit - 1, val, from, to);
  }
}

int main(void) {
  int n = 1;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    char s[10];
    scanf("%s", s);
    if (s[0] == 'A') {
      int x, y;
      scanf("%d%d", &x, &y); --x;
      Q.emplace_back(false, n, y);
      v[x].emplace_back(n, y);
      v[n].emplace_back(x, y);
      ++n;
    } else {
      int a, b;
      scanf("%d%d", &a, &b); --a; --b;
      Q.emplace_back(true, a, b);
    }
  }

  dfs(0, -1, 0);

  trie_add(&root, 30, 0, l[0]);
  int i = 1;
  for (const auto &qq : Q) {
    if (!qq.print)
      trie_add(&root, 30, rxor[qq.x], l[qq.x]);
    else
      printf("%d\n", trie_get(&root, 30, rxor[qq.x], l[qq.y], r[qq.y]));
    ++i;
  }

  return 0;
}
