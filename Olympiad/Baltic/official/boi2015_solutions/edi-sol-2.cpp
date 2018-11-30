// Wojtek Nadara
#include <bits/stdc++.h>
using namespace std;
const int M = 1 << 19;
struct PersTree {
  PersTree* l;
  PersTree* r;
  int bl, br, val;
  PersTree (PersTree* l_, PersTree* r_, int bl_, int br_) : l(l_), r(r_), bl(bl_), br(br_), val(M) {}
  
  int Find(int lvl) {
    if (bl == br) {
      return bl;
    }
    int r_min = SafeMin(r);
    if (r_min < lvl) {
      return r->Find(lvl);
    }
    return l->Find(lvl);
  }
  
  PersTree* Add(int pos, int lvl) {
    PersTree* copy = new PersTree(l, r, bl, br);
    copy->val = min(val, lvl);
    if (SafeIn(pos, l)) {
      copy->l = l->Add(pos, lvl);
    }
    if (SafeIn(pos, r)) {
      copy->r = r->Add(pos, lvl);
    }
    return copy;
  }
  
  static int SafeMin(PersTree* p) {
    if (p == nullptr) {
      return M;
    }
    return p->val;
  }

  static bool SafeIn(int x, PersTree* p) {
    return p != nullptr && p->bl <= x && x <= p->br;
  }
};

PersTree* CreatePersTree(int l, int r) {
  if (l == r) {
    return new PersTree(nullptr, nullptr, l, r);
  }
  int m = (l + r) / 2;
  return new PersTree(CreatePersTree(l, m), CreatePersTree(m + 1, r), l, r);
}
  
int res[M];
PersTree* pers[M];
int main() {
  ios_base::sync_with_stdio(0);
  int n;
  cin>>n;
  pers[0] = CreatePersTree(1, n);
  for (int ii = 1; ii <= n; ii++) {
    int op;
    cin>>op;
    if (op > 0) {
      res[ii] = op;
      pers[ii] = pers[ii - 1]->Add(ii, 0);
    } else {
      int bef_to_undo = pers[ii - 1]->Find(-op) - 1;
      res[ii] = res[bef_to_undo];
      pers[ii] = pers[bef_to_undo]->Add(ii, -op);
    }
    cout<<res[ii]<<"\n";
  }
  
  return 0;
}