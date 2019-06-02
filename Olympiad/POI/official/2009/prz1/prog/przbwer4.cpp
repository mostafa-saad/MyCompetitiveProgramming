/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przbwer4.cpp                                              *
 *   Autor:    Marcin Pilipczuk                                          *
 *   Opis:     Rozwiazanie niepoprawne.                                  *
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

char byloa[MAX_N][MAX_X];
char bylob[MAX_N][MAX_X];

int lkol_nast[MAX_X];
int lkol_popr[MAX_X];

inline int utnij_lewo(krowa *k, int st, int ko){
  int be = INF;
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
      if (k->sorty[xs] < be)
        be = k->sorty[xs];
  }
  return be;
}

inline int utnij_prawo(krowa *k, int st, int ko){
  int be = -INF;
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
      if (k->sorty[xs] > be)
        be = k->sorty[xs];
  }
  return be;
}


bool por_rek(int as, int ak, int bs, int bk, int nkol){
  if (nkol == 1) return true;
  if (byloa[as][a.t[ak+1]] || bylob[bs][b.t[bk+1]])
    return true; //(byloa[as][a.t[ak+1]] && bylob[bs][b.t[bk+1]]);
  int kol;
  byloa[as][a.t[ak+1]] = true;
  bylob[bs][b.t[bk+1]] = true;
  int nas = utnij_lewo(&a, as, ak);
  int nbs = utnij_lewo(&b, bs, bk);
  if (a.t[nas] != b.t[nbs]) return false;
  kol = a.t[nas];
  lkol_nast[lkol_popr[kol]] = lkol_nast[kol];
  lkol_popr[lkol_nast[kol]] = lkol_popr[kol];
  if (!por_rek(nas + 1, ak, nbs + 1, bk, nkol-1)) return false;
  lkol_nast[lkol_popr[kol]] = kol;
  lkol_popr[lkol_nast[kol]] = kol;
  int nak = utnij_prawo(&a, as, ak);
  int nbk = utnij_prawo(&b, bs, bk) ;
  if (a.t[nak] != b.t[nbk]) return false;
  kol = a.t[nak];
  lkol_nast[lkol_popr[kol]] = lkol_nast[kol];
  lkol_popr[lkol_nast[kol]] = lkol_popr[kol];
  if (!por_rek(as, nak - 1, bs, nbk - 1, nkol-1)) return false;
  lkol_nast[lkol_popr[kol]] = kol;
  lkol_popr[lkol_nast[kol]] = kol;
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
  REP(i, a.n+1) REP(j, MAX_X) byloa[i][j] = 0;
  REP(i, b.n+1) REP(j, MAX_X) bylob[i][j] = 0;
  return por_rek(0, a.n-1, 0, b.n-1, nkol);
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
