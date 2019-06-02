/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przwer3.cpp                                               *
 *   Autor:    Marcin Pilipczuk                                          *
 *   Opis:     Rozwiazanie niepoprawne O(nk^2 log k)                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <numeric>
#include <cmath>
#include <cassert>
using namespace std;

typedef vector <int > VI;
typedef vector < VI > VVI;
typedef long long LL;
typedef vector < LL > VLL;
typedef vector < double > VD;
typedef vector < string > VS;
typedef pair<int,int> PII;
typedef vector <PII> VPII;
typedef istringstream ISS;

#define ALL(x) x.begin(),x.end()
#define REP(i,n) for (int i=0; i<(n); ++i)
#define FOR(var,pocz,koniec) for (int var=(pocz); var<=(koniec); ++var)
#define FORD(var,pocz,koniec) for (int var=(pocz); var>=(koniec); --var)
#define FOREACH(it, X) for(__typeof((X).begin()) it = (X).begin(); it != (X).end(); ++it)
#define PB push_back
#define PF push_front
#define MP(a,b) make_pair(a,b)
#define ST first
#define ND second
#define SIZE(x) (int)x.size()

const int MAX_X = 105;
const int MAX_N = 100*1000 + 100;
const int INF = 1000*1000;

struct krowa{
  int n;
  int t[MAX_N];
  int nast[MAX_N];
  int popr[MAX_N];
  int pocz[MAX_X];
  int konc[MAX_X];
  int sorty[MAX_N];
  int pozsor[MAX_X + 1];
};

krowa a, b;

void wczyt(krowa *k){
  REP(i, MAX_X) k->pocz[i] = INF, k->konc[i] = -INF;
  REP(i, k->n) scanf("%d", &k->t[i]);
  REP(i, k->n){
    int x = k->t[i];
    k->popr[i] = k->konc[x];
    k->konc[x] = i;
  }
  k->t[k->n] = 0;
  FORD(i, k->n-1, 0){
    int x = k->t[i];
    k->nast[i] = k->pocz[x];
    k->pocz[x] = i;
  }
  REP(i, MAX_X) k->pozsor[i] = 0;
  REP(i, MAX_X){
    k->pozsor[i+1] = k->pozsor[i];
    for (int c = k->pocz[i]; c < INF; c = k->nast[c])
      k->sorty[k->pozsor[i+1]++] = c;
  }
}

unsigned char bylo[MAX_N][MAX_X];

#define BYLO_LA(n, x) (bylo[n][x] & 1u)
#define SBYLO_LA(n, x) bylo[n][x] |= 1u
#define BYLO_PA(n, x) (bylo[n][x] & 2u)
#define SBYLO_PA(n, x) bylo[n][x] |= 2u
#define BYLO_LB(n, x) (bylo[n][x] & 4u)
#define SBYLO_LB(n, x) bylo[n][x] |= 4u
#define BYLO_PB(n, x) (bylo[n][x] & 8u)
#define SBYLO_PB(n, x) bylo[n][x] |= 8u


int lkol_nast[MAX_X];
int lkol_popr[MAX_X];

inline void gen_lewo(krowa *k, int st, int ko, VI &kolory){
  for (int i = lkol_nast[0]; i != 0; i = lkol_nast[i]){
    int xs = k->pozsor[i];
    int xk = k->pozsor[i+1];
    if (xs == xk) continue;
    while (xs + 1 < xk){
      int xc = (xs + xk) / 2;
      if (k->sorty[xc] <= ko)
        xs = xc;
      else
        xk = xc;
    }
    if (k->sorty[xs] >= st)
      kolory.PB(k->sorty[xs]);
  }
  sort(ALL(kolory));
}

bool por_rek_prawo(int as, int ak, int bs, int bk, int nkol);
bool por_rek_lewo(int as, int ak, int bs, int bk, int nkol){
  if (nkol == 1) return true;
  if (BYLO_LA(as, a.t[ak+1]) || BYLO_LB(bs, b.t[bk+1]))
    return (BYLO_LA(as, a.t[ak+1]) && BYLO_LB(bs, b.t[bk+1]));
  SBYLO_LA(as, a.t[ak+1]);
  SBYLO_LB(bs, b.t[bk+1]);
  VI akolory, bkolory;
  gen_lewo(&a, as, ak, akolory);
  gen_lewo(&b, bs, bk, bkolory);
  int c = 0;
  REP(i, nkol){
    if (a.t[akolory[i]] != b.t[bkolory[i]]) return false;
    int kol = a.t[akolory[i]];
    lkol_nast[lkol_popr[kol]] = lkol_nast[kol];
    lkol_popr[lkol_nast[kol]] = lkol_popr[kol];
    c++;
    int nas = akolory[i] + 1;
    int nbs = bkolory[i] + 1;
    if (BYLO_LA(nas, a.t[ak+1]) || BYLO_LB(nbs, b.t[bk+1])){
      if (BYLO_LA(nas, a.t[ak+1]) && BYLO_LB(nbs, b.t[bk+1]))
        break;
      else
        return false;
    }
    if (!por_rek_prawo(nas, ak, nbs, bk, nkol - i - 1)) return false;
  }
  FORD(i, c-1, 0){
    int kol = a.t[akolory[i]];
    lkol_nast[lkol_popr[kol]] = kol;
    lkol_popr[lkol_nast[kol]] = kol;
  }
  return true;
}

inline void gen_prawo(krowa *k, int st, int ko, VI &kolory){
  for (int i = lkol_nast[0]; i != 0; i = lkol_nast[i]){
    int xs = k->pozsor[i];
    int xk = k->pozsor[i+1] - 1;
    if (xs > xk) continue;
    while (xs < xk){
      int xc = (xs + xk) / 2;
      if (k->sorty[xc] >= st)
        xk = xc;
      else
        xs = xc + 1;
    }
    if (k->sorty[xs] <= ko)
      kolory.PB(k->sorty[xs]);
  }
  sort(ALL(kolory));
  reverse(ALL(kolory));
}

bool por_rek_prawo(int as, int ak, int bs, int bk, int nkol){
  if (nkol == 1) return true;
  if (BYLO_PA(as, a.t[ak+1]) || BYLO_PB(bs, b.t[bk+1]))
    return (BYLO_PA(as, a.t[ak+1]) && BYLO_PB(bs, b.t[bk+1]));
  SBYLO_PA(as, a.t[ak+1]);
  SBYLO_PB(bs, b.t[bk+1]);
  VI akolory, bkolory;
  gen_prawo(&a, as, ak, akolory);
  gen_prawo(&b, bs, bk, bkolory);
  int c = 0;
  REP(i, nkol){
    if (a.t[akolory[i]] != b.t[bkolory[i]]) return false;
    int kol = a.t[akolory[i]];
    lkol_nast[lkol_popr[kol]] = lkol_nast[kol];
    lkol_popr[lkol_nast[kol]] = lkol_popr[kol];
    c++;
    int nak = akolory[i] - 1;
    int nbk = bkolory[i] - 1;
    if (BYLO_PA(as, a.t[nak+1]) || BYLO_PB(bs, b.t[nbk+1])){
      if (BYLO_PA(as, a.t[nak+1]) && BYLO_PB(bs, b.t[nbk+1]))
        break;
      else
        return false;
    }
    if (!por_rek_lewo(as, nak, bs, nbk, nkol - i - 1)) return false;
  }
  FORD(i, c-1, 0){
    int kol = a.t[akolory[i]];
    lkol_nast[lkol_popr[kol]] = kol;
    lkol_popr[lkol_nast[kol]] = kol;
  }
  return true;
}

bool porownaj(){
  int nkol = 0;
  lkol_nast[0] = lkol_popr[0] = 0;
  REP(i, MAX_X){
    if ((a.pocz[i] == INF) ^ (b.pocz[i] == INF))
      return false;
    if (a.pocz[i] != INF){
      nkol++;
      lkol_nast[i] = 0;
      lkol_popr[i] = lkol_popr[0];
      lkol_nast[lkol_popr[i]] = i;
      lkol_popr[0] = i;
    }
  }
  REP(i, max(a.n, b.n)+1) REP(j, MAX_X) bylo[i][j] = 0;
  return por_rek_lewo(0, a.n-1, 0, b.n-1, nkol) && por_rek_prawo(0, a.n-1, 0, b.n-1, nkol);
}

int main(){
  int testy;
  scanf("%d", &testy);
  while(testy--){
    scanf("%d%d", &a.n, &b.n);
    wczyt(&a);
    wczyt(&b);
    printf(porownaj() ? "1\n" : "0\n");
  }
	return 0;
}
