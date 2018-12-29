/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przwer1.cpp                                               *
 *   Autor:    Marcin Pilipczuk                                          *
 *   Opis:     Rozwiazanie niepoprawnie liczace wartosci s() i p()       *
 *             O(nk+k^3                                                  *
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

const int MAX_X = 100;
const int MAX_N = 100*1000;
const int INF = 1000*1000;

struct krowa{
  int n;
  int pocz[MAX_X];
  int konc[MAX_X];
  int wcz[MAX_X][MAX_X];
  int po[MAX_X][MAX_X];
};

krowa a, b;
int tmp[MAX_N], tmp2[MAX_X];

void wczyt(krowa *k){
  REP(i, MAX_X) k->pocz[i] = INF, k->konc[i] = -INF;
  REP(i, k->n){ scanf("%d", &tmp[i]); tmp[i]--; }
  REP(i, MAX_X) tmp2[i] = -INF;
  REP(i, k->n){
    int x = tmp[i];
    if (k->pocz[x] == INF){
      k->pocz[x] = i;
      REP(j, MAX_X)
        k->wcz[x][j] = tmp2[j];
    }
    tmp2[x] = i;
  }
  REP(i, MAX_X) tmp2[i] = INF;
  FORD(i, k->n-1, 0){
    int x = tmp[i];
    if (k->konc[x] == -INF){
      k->konc[x] = i;
      REP(j, MAX_X)
        k->po[x][j] = tmp2[j];
    }
    tmp2[x] = i;
  }
}

inline bool obejmuje1(krowa *a, int i, int j, int k){
  return a->wcz[i][j] < a->wcz[i][k];
}

inline bool obejmuje2(krowa *a, int i, int j, int k){
  return a->po[i][j] > a->po[i][k];
}

bool porownaj(krowa *a, krowa *b){
  REP(i, MAX_X)
    if ((a->pocz[i] == INF) ^ (b->pocz[i] == INF))
      return false;
  REP(i, MAX_X) if (a->pocz[i] != INF)
    REP(j, MAX_X) if (i != j && a->pocz[j] != INF){
      if ((a->wcz[j][i] != -INF) ^ (b->wcz[j][i] != -INF))
        return false;
      if ((a->po[j][i] != INF) ^ (b->po[j][i] != INF))
        return false;
    }
  REP(i, MAX_X) if (a->pocz[i] != INF)
    REP(j, MAX_X) if (i != j && a->pocz[j] != INF)
      REP(k, MAX_X) if (k != j && k != i && a->pocz[k] != INF){
        if (obejmuje1(a, i, j, k) ^ obejmuje1(b, i, j, k))
          return false;
        if (obejmuje2(a, i, j, k) ^ obejmuje2(b, i, j, k))
          return false;
      }

    return true;
}

int main(){
  int testy;
  scanf("%d", &testy);
  while(testy--){
    scanf("%d%d", &a.n, &b.n);
    wczyt(&a);
    wczyt(&b);
    printf(porownaj(&a, &b) ? "1\n" : "0\n");
  }
	return 0;
}
