#include <cstdio>
#include <map>
#include <set>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1 << 17;
const int MAXQ = 1 << 17;
const int inf = 1 << 30;

typedef long long llint;

struct _hash{
  static const int base0 = 3137;
  static const int mod0 = 1000000007;
  static const int base1 = 53;
  static const int mod1 = 1610612741;

  int h0, h1;
  _hash () {
    h0 = h1 = 0;
  }

  void add_char (char c) {
    h0 = (h0 * (llint)base0 + c - 'a' + 1)%mod0;
    h1 = (h1 * (llint)base1 + c - 'a' + 1)%mod1;
  }
};

bool operator < (const _hash &A, const _hash &B) {
  if (A.h0 != B.h0) return A.h0 < B.h0;
  return A.h1 < B.h1;
}

map <_hash, vector <int>> M;

struct node{
  node *edge[26];
  int dt, ft;
  vector <_hash> hashes;
  node () {
    memset(edge, 0, sizeof edge);
  }
};

node *root;
void insert (node *&x, const char *s, _hash *h) {
  if (x == NULL) x = new node();
  x->hashes.push_back(*h);
  if (!*s) return;
  insert(x->edge[*s - 'a'], s+1, h+1);
}

int query (node *&x, const char *s, _hash &h) {
  if (x == NULL) return 0;
  if (!*s) return upper_bound(M[h].begin(), M[h].end(), x->ft) - lower_bound(M[h].begin(), M[h].end(), x->dt);
  return query(x->edge[*s - 'a'], s+1, h);
}

_hash h[MAXN];
set <_hash> S;
void build_hash (string s) {
  reverse(s.begin(), s.end());
  h[0] = _hash();
  for (int i = 0; i < (int)s.size(); ++i){
    h[i+1] = h[i];
    h[i+1].add_char(s[i]);
  }
  reverse(h, h + (int)s.size() + 1);
}

int time_;
void dfs (node *x) {
  if (x == NULL) return;
  x->dt = ++time_;

  for (auto h: x->hashes)
    if (S.count(h)) M[h].push_back(x->dt);

  for (int i = 0; i < 26; ++i)
    dfs(x->edge[i]);

  x->ft = ++time_;
}

int n, q;
string pref[MAXQ], suff[MAXQ];
int main (void) {
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; ++i) {
    string str;
    cin >> str;
    build_hash(str);
    insert(root, str.c_str(), h);
  }

  for (int i = 0; i < q; ++i) {
    string str;
    cin >> str;
    pref[i] = str.substr(0, str.find("*"));
    suff[i] = str.substr(str.find("*")+1);
    reverse(suff[i].begin(), suff[i].end());
    _hash h;
    for (auto c: suff[i])
      h.add_char(c);
    S.insert(h);
  }

  dfs(root);
  for (int i = 0; i < q; ++i) {
    _hash h;
    for (auto c: suff[i])
      h.add_char(c);
    printf("%d\n", query(root, pref[i].c_str(), h));
  }

  return 0;
}
