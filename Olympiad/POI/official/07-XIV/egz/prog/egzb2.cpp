/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Egzamin na prawo jazdy (EGZ)                               *}
{*   Plik:    egzb2.cpp                                                  *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Rozwiazanie niepoprawne, starajace sie zachlannie znalezc  *}
{*            liczbe drog, ktore trzeba dobudowac (zamiast najdluzszego  *}
{*            podciagu)                                                  *}
{*                                                                       *}
{*************************************************************************/
#define REP(I,N)       for(int I=0; I<(N); ++I)

#include<cstdio>
#include<cstdlib>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

const int MAXN = 100000;
int n,m,p,k;

typedef vector< vector<int> > tDrogi;
tDrogi wschzach, zachwsch;

int lewo[MAXN], prawo[MAXN];

void oblicz(const tDrogi &drogi, int *wyn)
{
  int last = m, ile=0;
  wyn[0] = 0;
  REP(i,n-1) {
    int newlast = -1, maxd=-1;
    REP(j, (int)drogi[i].size()) {
      if( last>= drogi[i][j] ) newlast=max(newlast,drogi[i][j]);
      maxd = max(maxd,drogi[i][j]);
    }
    if( -1==newlast) {
      ile++;
      if( -1 == maxd ) {
        last = m;
      } else {
        last = maxd;
      }
    } else {
      last = newlast;
    }
    wyn[i+1] = ile;
  }
}

int main()
{
  scanf("%d %d %d %d", &n, &m, &p, &k);

  wschzach.resize(n);
  zachwsch.resize(n);
  REP(i,p) {
    int ni,mi,di;
    scanf("%d %d %d", &ni, &mi, &di);
    if( 1==di ) {
      wschzach[ni-1].push_back(mi);
    } else {
      zachwsch[n-1-ni].push_back(mi);
    }
  }
  oblicz(wschzach,lewo);
  
  oblicz(zachwsch,prawo);
  reverse(prawo, prawo+n);

  int res=0,  koniec=0;
  REP(i,n) {
    while( koniec+1 < n && prawo[i]+lewo[koniec+1]<=k ) ++koniec;
    koniec=max(i,koniec);
    if(prawo[i]+lewo[koniec]<=k)
      res = max(res, koniec-i+1);
  }
  REP(i,n) {
    if( 0==lewo[i] && 0==prawo[i]) {
      --res;
    }
  }
  printf("%d\n",res);

  return 0;
}

