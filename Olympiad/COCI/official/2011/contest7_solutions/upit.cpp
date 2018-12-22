#include <algorithm>
#include <functional>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <string>

using namespace std;

typedef long long llint;
const int MAXN = 200100;
const int MAXNODE = 524488;

int __L, __R;

llint __X;
llint Poc[MAXN];

struct tournament {
  struct node {
    llint sum;
    int alive;
    int monoton;
    llint poc_pov;
    llint inc_pov;

    node() { sum = 0; alive = 0; monoton = -1; poc_pov = inc_pov = 0; }

    void update(node &A, node &B) {
      alive = A.alive + B.alive;
      sum = A.sum + B.sum;
      monoton = -1; // oprezno sa ovime?
    }

    void postaviMonoton(int x) { // moraju se moci stackati
      monoton = x;
      sum = x*alive;
      poc_pov = inc_pov = 0;
    }
    void postaviPov(llint poc, llint inc) {
      poc_pov += poc;
      inc_pov += inc;
      sum += poc*alive + inc*(alive-1)*alive/2;
    }

    void spread(node &A, node &B) { // pazi da nisi u djetetu!
      if (monoton != -1) {
        A.postaviMonoton(monoton);
        B.postaviMonoton(monoton);
        monoton = -1;
      }

      if (inc_pov != 0) {
        A.postaviPov(poc_pov, inc_pov);
        B.postaviPov(poc_pov + inc_pov*A.alive, inc_pov);
        poc_pov = inc_pov = 0;
      }
    }
  } h[MAXNODE];

  // operacije nad tournamentom

  void ozivi(int x, int l, int r) {
    if (l == r) {
      h[x].alive = 1;
      return ;
    }
    int mid = (l+r)/2;
    ozivi(2*x, l, mid);
    ozivi(2*x+1, mid+1, r);
    h[x].update(h[2*x], h[2*x+1]);
  }

  int umrtvi(int x, int l, int r, int preskoci) { // input: __L -> vraca indeks lista
    int pravi_l = preskoci;
    int pravi_r = preskoci + h[x].alive - 1;

    if (pravi_r < __L || __L < pravi_l) return -1; // miss
    if (l == r) {
      h[x].alive = false;
      h[x].sum = 0;
      return x;
    }

    int mid = (l+r)/2;
    int ret = -1;
    ret = max(ret, umrtvi(2*x, l, mid, preskoci));
    if (ret == -1) {
      ret = max(ret, umrtvi(2*x+1, mid+1, r, preskoci+h[2*x].alive));
    }

    h[x].update(h[2*x], h[2*x+1]);
    return ret;
  }

  void init(int x, int l, int r, int preskok) {
    if (l == r) {
      if (h[x].alive == false) return ;
      h[x].sum = Poc[preskok]; 
      return ;
    }
    int mid = (l+r)/2;
    init(2*x, l, mid, preskok);
    init(2*x+1, mid+1, r, preskok+h[2*x].alive);
    h[x].update(h[2*x], h[2*x+1]);
  }

  // ----------- aktivna regija (treba i spreadati!) -> pazi od kuda! ----------

  void spreadDo(int L, int dijete) {
    if (L < 1) return ;
    spreadDo(L >> 1, dijete);
    if (L != dijete) h[L].spread(h[2*L], h[2*L+1]);
  }

  void updateDo(int L, int dijete) {
    if (L < 1) return ;
    if (L != dijete) h[L].update(h[2*L], h[2*L+1]);
    updateDo(L >> 1, dijete);
  }

  llint getSuma(int x, int l, int r, int preskoci) { // inputi __L, __R
    int pravi_l = preskoci;
    int pravi_r = pravi_l + h[x].alive - 1;

    if (pravi_r < __L || __R < pravi_l) return 0;
    if (__L <= pravi_l && pravi_r <= __R) return h[x].sum;

    h[x].spread(h[2*x], h[2*x+1]);
    int mid = (l+r)/2;

    llint ret = 0;
    ret += getSuma(2*x, l, mid, preskoci);
    ret += getSuma(2*x+1, mid+1, r, preskoci+h[2*x].alive);
    h[x].update(h[2*x], h[2*x+1]);
    return ret;
  }

  void postaviInterval(int x, int l, int r, int preskoci) { // input __L, __R, __X
    int pravi_l = preskoci;
    int pravi_r = pravi_l + h[x].alive - 1;

    if (pravi_r < __L || __R < pravi_l) return;
    if (__L <= pravi_l && pravi_r <= __R) {
      h[x].postaviMonoton(__X);
      return ;
    }

    h[x].spread(h[2*x], h[2*x+1]);
    int mid = (l+r)/2;
    postaviInterval(2*x, l, mid, preskoci);
    postaviInterval(2*x+1, mid+1, r, preskoci+h[2*x].alive);
    h[x].update(h[2*x], h[2*x+1]);
  }

  int linPovecanje(int x, int l, int r, int preskoci, int obradio) { // input __L, __R, __X
    int pravi_l = preskoci;
    int pravi_r = pravi_l + h[x].alive - 1;

    if (pravi_r < __L || __R < pravi_l) return 0;
    if (__L <= pravi_l && pravi_r <= __R) {
      h[x].postaviPov((obradio+1)*__X, __X);
      return h[x].alive;
    }
    h[x].spread(h[2*x], h[2*x+1]);
    int mid = (l+r)/2;
    int obr = 0;
    obr += linPovecanje(2*x, l, mid, preskoci, obradio);
    obr += linPovecanje(2*x+1, mid+1, r, preskoci+h[2*x].alive, obradio + obr);
    h[x].update(h[2*x], h[2*x+1]);
    return obr;
  }
} T;

struct query {
  int tip;
  int a, b;
  int x;
  
  int meta;

  void load() {
    scanf("%d", &tip);
    if (tip != 3) { scanf("%d %d", &a, &b); --a, --b; }
    else /*tip = 3*/ { scanf("%d", &a); --a; }

    if (tip != 4) { scanf("%d", &x); }
  }
} Q[MAXN];

int pocN, q; // pazi 
int brEl;

int main( void )
{
  scanf("%d %d", &pocN, &q);
  brEl = pocN;

  for (int i = 0; i < pocN; ++i) scanf("%lld", Poc+i);
  for (int i = 0; i < q; ++i) {
    Q[i].load();
    if (Q[i].tip == 3) ++brEl;
  }
  T.ozivi(1, 0, brEl-1);
  for (int i = q-1; i >= 0; --i) {
    if (Q[i].tip == 3) {
      __L = Q[i].a;
      Q[i].meta = T.umrtvi(1, 0, brEl-1, 0);
    }
  }
  T.init(1, 0, brEl-1, 0);

  for (int cnt = 0; cnt < q; ++cnt) {
    if (Q[cnt].tip == 1) {
      __L = Q[cnt].a;
      __R = Q[cnt].b;
      __X = Q[cnt].x;
      T.postaviInterval(1, 0, brEl-1, 0);
      
    } else if(Q[cnt].tip == 2) {
      __L = Q[cnt].a;
      __R = Q[cnt].b;
      __X = Q[cnt].x;
      T.linPovecanje(1, 0, brEl-1, 0, 0);
    
    } else if(Q[cnt].tip == 3) {
      int ind = Q[cnt].meta;
      T.spreadDo(ind, ind);
      T.h[ind].alive = 1;
      T.h[ind].sum = Q[cnt].x;
      T.updateDo(ind, ind);

    } else if(Q[cnt].tip == 4) {
      __L = Q[cnt].a;
      __R = Q[cnt].b;
      printf("%lld\n", T.getSuma(1, 0, brEl-1, 0));
    }
  }

  return (0-0);
}
