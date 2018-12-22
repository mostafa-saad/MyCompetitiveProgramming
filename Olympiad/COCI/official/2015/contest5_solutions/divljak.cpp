#include <cstdio>
#include <map>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

const int MAXN = 1 << 17;
const int MAXLEN = 1 << 21;

int cookie;
struct imp_node{
  int chain;
  int depth;
  int size;
  vector <imp_node*> E;
  imp_node *dad;
  imp_node (){
    dad = 0;
    chain = -1;
    depth = 0;
    size = 0;
  }

  int chain_depth ();
};

struct chain{
  imp_node *root;
  int size;
  int last;
  int bio;

  vector <int> loga;

  chain (){
    size = bio = last = 0;
  }

  void init (){
    loga.resize(size + 1);
  } 

  void update (int x, int v){
    for (int i = x; i <= size; i += i&-i)
      loga[i] += v;
  }

  int query (int x){

    int ret = 0;
    while (x > 0){
      ret += loga[x];
      x -= x&-x;
    }

    return ret;
  }

  void update (int p){
    if (cookie != bio){
      bio = cookie;
      last = 0;
    }
    if (p > last){
      update(last+1, 1);
      update(p+1, -1);
      last = p;
    }
  }
};

vector <chain> hlc;

inline int imp_node::chain_depth (){
  return depth - hlc[chain].root->depth + 1;
}

struct aho_node{
  aho_node *fail;
  aho_node *rec;
  aho_node *edge[26];
  imp_node *some;
  bool done;

  aho_node (){
    memset(edge, 0, sizeof edge);
    done = 0;
    fail = rec = 0;
    some = 0;
  }

};

aho_node *root = 0;
imp_node *aux_root = 0;

int n, q;
string s;
aho_node *where[MAXN];

aho_node *insert (aho_node *&x, const char *p){
  if (x == NULL) x = new aho_node;
  if (*p == 0){
    x->done = 1;
    return x;
  }

  return insert(x->edge[*p -'a'], p+1);
}

void update_path (imp_node *x){

  while (x){
    hlc[x->chain].update(x->chain_depth());
    x = hlc[x->chain].root;
    x = x->dad;
  }

}

void update (const char *p){
  ++cookie;
  aho_node *curr = root;
  while (*p){
    while (curr != root && curr->edge[*p - 'a'] == 0) curr = curr->fail;
    if (curr->edge[*p - 'a']){
      curr = curr->edge[*p - 'a'];
      update_path(curr->some);
    }
    ++p;
  }
}

void build_tree (){

  aux_root = new imp_node;
  root->some = aux_root;
  root->fail = root->rec = root;

  queue <aho_node*> Q;
  for (int i = 0; i < 26; ++i)
    if (root->edge[i] != 0){
      aho_node *y = root->edge[i];
      y->fail = y->rec = root;
      aux_root->E.push_back(y->some = new imp_node);
      y->some->dad = aux_root;
      Q.push(y);
    }

  while (!Q.empty()){
    aho_node *curr = Q.front(); Q.pop();
    for (int i = 0; i < 26; ++i)
      if (curr->edge[i] != 0){

	aho_node *y = curr->edge[i];
	aho_node *z = curr->fail;

	while (z != root && z->edge[i] == 0) z = z->fail;
	if (z->edge[i] != 0) z = z->edge[i];

	y->fail = z;
	if (z->done) y->rec = z;
	else y->rec = z->rec;

	y->rec->some->E.push_back(y->some = new imp_node);

	y->some->dad = y->rec->some;
	Q.push(y);
      }
  }
}

int dfs (imp_node *x){
  x->size = 1;
  for (int i = 0; i < x->E.size(); ++i){
    x->E[i]->depth = x->depth + 1;
    x->size += dfs(x->E[i]);
  }

  return x->size;
}

int chain_idx = 0;
void dfs_hl (imp_node *x){
  x->chain = chain_idx; 
  ++hlc[chain_idx].size;

  int mx = -1;
  for (int i = 0; i < x->E.size(); ++i)
    if (mx == -1 || x->E[i]->size > x->E[mx]->size) mx = i;

  if (mx == -1) return;
  dfs_hl(x->E[mx]);

  for (int i = 0; i < x->E.size(); ++i)
    if (i != mx){
      hlc.push_back(chain());
      hlc[++chain_idx].root = x->E[i];
      dfs_hl(x->E[i]);
    }
}

void build_heavylight (){
  aux_root->depth = 0;
  dfs(aux_root);

  hlc.push_back(chain());
  hlc[0].root = aux_root;

  dfs_hl(aux_root);
  for (int i = 0; i < hlc.size(); ++i)
    hlc[i].init();
}

int main (void){

  ios_base::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i){
    cin >> s;
    where[i] = insert(root, s.c_str());
  }

  build_tree();
  build_heavylight();

  cin >> q;
  for (int i = 0; i < q; ++i){
    int tip;
    cin >> tip;
    if (tip == 1){
      string p;
      cin >> p;
      update(p.c_str());
    }

    if (tip == 2){
      int x;
      cin >> x; --x;
      aho_node *curr = where[x];
      imp_node *imp_curr = curr->some;
      int ans = hlc[imp_curr->chain].query(imp_curr->chain_depth());
      cout << ans << endl;
    }
  }

  return 0;
}
