#include <cstdio>

struct Node {
  Node *l, *r, *p;
  Node() : l(NULL), r(NULL), p(NULL) {}
  int state() {
    if(p && p->l == this) return -1;
    if(p && p->r == this) return 1;
    return 0;
  }
  void rotate() {
    Node *par = p;
    Node *mid;
    if(p->l == this) {
      mid = this->r; this->r = par;
      par->l = mid;
    } else {
      mid = this->l; this->l = par;
      par->r = mid;
    }
    if(mid) mid->p = par;
    this->p = par->p; par->p = this;
    if(this->p && this->p->l == par) this->p->l = this;
    if(this->p && this->p->r == par) this->p->r = this;
  }
  void splaySolid() {
    while(state()) {
      int st = state() * p->state();
      if(st == 0) {
        rotate();
      } else if(st == 1) {
        p->rotate();
        rotate();
      } else {
        rotate();
        rotate();
      }
    }
  }
  void splay() {
    for(Node *x = this; x; x = x->p) x->splaySolid();
    for(Node *x = this; x->p; x = x->p) x->p->l = x;
    splaySolid();
  }
  void linkTo(Node *x) {
    x->splay();
    splay();
    p = x;
  }
  void cut() {
    splay();
    r->p = NULL;
    r = NULL;
  }
  Node *lca(Node *x) {
    x->splay();
    splay();
    l = NULL;
    bool sameTree = false;
    Node *ret = x;
    for(; x; x=x->p) {
      if(x->p && !x->state()) ret = x->p;
      if(x == this) sameTree = true;
    }
    return sameTree ? ret : NULL;
  }
};

int main() {
  int N, Q; scanf("%d%d", &N, &Q);
  Node *nodes = new Node[N];
  for(int i = 0; i < Q; i++) {
    int T; scanf("%d", &T);
    if(T == 1) {
      int A, B; scanf("%d%d", &A, &B); A--; B--;
      nodes[A].linkTo(&nodes[B]);
    } else if(T == 2) {
      int A; scanf("%d", &A); A--;
      nodes[A].cut();
    } else {
      int A, B; scanf("%d%d", &A, &B); A--; B--;
      Node *c = nodes[A].lca(&nodes[B]);
      if(c) {
        printf("%d\n", (int)(c-nodes)+1);
      } else {
        printf("%d\n", -1);
      }
    }
  }
  return 0;
}
