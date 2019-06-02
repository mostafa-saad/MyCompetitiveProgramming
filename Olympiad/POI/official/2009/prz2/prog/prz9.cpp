/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     prz9.cpp                                                  *
 *   Autor:    Marcin Pilipczuk                                          *
 *   Opis:     Rozwiazanie wzorcowe O((A+d)*n^2+m*n))                    *
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

const int N = 405;
const int ALF = 'z'-'a' + 2;
const int BEZLIT = 'z'-'a' + 1;

int dist[N][N][ALF];
int skad[N][N][ALF];
int kolejka[N * N * ALF];
int pk, kk;

inline void dodkol(int a, int b, int st, int di, int sk){
  if (dist[a][b][st] == -1){
    dist[a][b][st] = di;
    skad[a][b][st] = sk;
    kolejka[kk++] = (a | (b << 9) | (st << 18));
  }
}

inline void popkol(int &a, int &b, int &st){
  int x = kolejka[pk++];
  a = x & 511;
  b = (x >> 9) & 511;
  st = x >> 18;
}

char lit[N][N];
int n;
vector<pair<char, int> > g[N], gv[N];
int gpoz[N][ALF];

char slowo[N * N + 1];

void generuj_slowo(int a, int b){
  int pocz = 0, konc = dist[a][b][BEZLIT] - 1;
  slowo[konc+1] = 0;
  while(pocz < konc){
    int c = skad[a][b][BEZLIT];
    int st = slowo[pocz++] = slowo[konc--] = lit[c][b];
    st -= 'a';
    b = c;
    a = skad[a][c][st];
  }
  if (pocz == konc)
    slowo[pocz] = lit[a][b];
}

int main(){
  int m;
  scanf("%d%d", &n, &m);
  REP(i, n) REP(j, n) REP(a, ALF) dist[i][j][a] = -1;
  REP(i, m){
    int a, b; char t[10];
    scanf("%d %d %s", &a, &b, t);
    --a; --b;
    lit[a][b] = t[0];
    g[a].PB(MP(t[0], b));
    gv[b].PB(MP(t[0], a));
  }
  REP(i, n){
    sort(ALL(g[i]));
    sort(ALL(gv[i]));
    int poz = -1;
    int mg = SIZE(g[i]);
    REP(j, mg)
      while (poz < g[i][j].ST - 'a')
        gpoz[i][++poz] = j;
    while (poz < BEZLIT)
      gpoz[i][++poz] = mg;
  }
  REP(i, n) dodkol(i, i, BEZLIT, 0, -1);
  REP(i, n) REP(j, n) if (lit[i][j])
    dodkol(i, j, BEZLIT, 1, -1);
  while(pk < kk){
    int a, b, st;
    popkol(a, b, st);
    int di = dist[a][b][st];
    if (st == BEZLIT){
      // idziemy wstecz z wierzcholka a kazda mozliwa literka
      FOREACH(it, gv[a])
        dodkol(it->ND, b, it->ST-'a', di + 1, a);
    } else {
      // idziemy wprzod z wierzcholka b literka dostepna
      FOR(i, gpoz[b][st], gpoz[b][st+1]-1)
        dodkol(a, g[b][i].ND, BEZLIT, di + 1, b);
    }
  }
  int d, la;
  scanf("%d%d", &d, &la); --la;
  REP(i, d-1){
    int x; scanf("%d", &x); --x;
    if (dist[la][x][BEZLIT] == -1)
      printf("-1\n");
    else{
      generuj_slowo(la, x);
      printf("%d %s\n", dist[la][x][BEZLIT], slowo);
    }
    la = x;
  }
  return 0;
}
