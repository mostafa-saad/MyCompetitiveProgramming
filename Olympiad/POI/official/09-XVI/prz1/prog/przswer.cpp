/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przs8.pas                                                 *
 *   Autor:    Marcin Pilipczuk                                          *
 *   Opis:     Rozwiazanie O(nk^2 log nk) z haszowaniem                  *
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

map<unsigned int, unsigned short> mapa;
unsigned short mapa_lastkol;

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

unsigned short bylo[MAX_N][MAX_X];

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

unsigned short licz_hash(krowa *k, int st, int ko, int nkol){
  if (nkol == 1)
    return k->t[st];
  if (bylo[st][k->t[ko+1]])
    return bylo[st][k->t[ko+1]];
  int kol;
  int nst = utnij_lewo(k, st, ko);
  kol = k->t[nst];
  lkol_nast[lkol_popr[kol]] = lkol_nast[kol];
  lkol_popr[lkol_nast[kol]] = lkol_popr[kol];
  unsigned lewy = (unsigned)licz_hash(k, nst + 1, ko, nkol - 1);
  lkol_nast[lkol_popr[kol]] = kol;
  lkol_popr[lkol_nast[kol]] = kol;
  int nko = utnij_prawo(k, st, ko);
  kol = k->t[nko];
  lkol_nast[lkol_popr[kol]] = lkol_nast[kol];
  lkol_popr[lkol_nast[kol]] = lkol_popr[kol];
  unsigned prawy = (unsigned)licz_hash(k, st, nko - 1, nkol - 1);
  lkol_nast[lkol_popr[kol]] = kol;
  lkol_popr[lkol_nast[kol]] = kol;
  unsigned razem = (prawy << 16) | lewy;
  unsigned short nowy;
  if (mapa.count(razem))
    nowy = mapa[razem];
  else{
    nowy = mapa[razem] = mapa_lastkol++;
    if (!mapa_lastkol)
      mapa_lastkol = MAX_X; // konflikty na poziomie kolorow sa ZLE
  }
  bylo[st][k->t[ko+1]] = nowy;
  return nowy;
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
  mapa_lastkol = MAX_X;
  REP(i, a.n+1) REP(j, MAX_X) bylo[i][j] = 0;
  unsigned short ah = licz_hash(&a, 0, a.n-1, nkol);
  REP(i, b.n+1) REP(j, MAX_X) bylo[i][j] = 0;
  unsigned short bh = licz_hash(&b, 0, b.n-1, nkol);
  return ah == bh;
}

int main(){
  int testy;
  scanf("%d", &testy);
  while(testy--){
    scanf("%d%d", &a.n, &b.n);
    mapa.clear();
    wczyt(&a);
    wczyt(&b);
    printf(porownaj() ? "1\n" : "0\n");
  }
	return 0;
}
