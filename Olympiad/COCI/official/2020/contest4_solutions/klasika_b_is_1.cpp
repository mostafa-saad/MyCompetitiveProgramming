#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 2e5 + 10;

struct Node {
  Node *zero, *one;
  Node () {
    zero = one = NULL;
  }
} root;

int q, n, t;
int rxor[MAXN];

void trie_add(Node *node, int bit, int val) {
  if (bit < 0) return;
  if (val & (1 << bit)) {
    if (node->one == NULL) node->one = new Node();
    trie_add(node->one, bit - 1, val);
  } else {
    if (node->zero == NULL) node->zero = new Node();
    trie_add(node->zero, bit - 1, val);
  }
}

int trie_get(Node *node, int bit, int val) {
  if (bit < 0) return 0;
  if ((val & (1 << bit)) == 0) { // want 1
    if (node->one == NULL)
      return trie_get(node->zero, bit - 1, val);
    else
      return (1 << bit) + trie_get(node->one, bit - 1, val);
  } else { // want 0
    if (node->zero == NULL)
      return trie_get(node->one, bit - 1, val);
    else
      return (1 << bit) + trie_get(node->zero, bit - 1, val);
  }
}

int main(void) {
  int n = 1;
  scanf("%d", &q);

  trie_add(&root, 30, 0);
  for (int i = 0; i < q; ++i) {
    char s[10];
    scanf("%s", s);
    if (s[0] == 'A') {
      int x, y;
      scanf("%d%d", &x, &y); --x;
      rxor[n] = y ^ rxor[x];
      trie_add(&root, 30, rxor[n]);
      ++n;
    } else {
      int a, b;
      scanf("%d%d", &a, &b); --a; --b;
      printf("%d\n", trie_get(&root, 30, rxor[a]));
    }
  }

  return 0;
}
