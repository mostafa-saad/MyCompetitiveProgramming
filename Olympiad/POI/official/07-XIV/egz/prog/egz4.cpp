/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Egzamin na prawo jazdy (EGZ)                               *}
{*   Plik:    egz4.cpp                                                   *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Implementacja innego rozwiazania poprawnego                *}
{*            zaproponowanego przez autora zadania                       *}
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

int tab[MAXN+1];
const int gora  = (sizeof(tab)/sizeof(int))-1;

void oblicz(const tDrogi &drogi, int *wyn)
{
  int poczatek = gora;
  memset(tab,0, sizeof(tab));

  tab[poczatek] = m;
  wyn[0] = 0;
  REP(i,n-1) {
    tab[--poczatek] = -1;
    REP(j, (int) drogi[i].size()) {
      int h = drogi[i][j];
      int pom = lower_bound(tab+poczatek, tab+gora+1, h)-tab-1;
      tab[pom] = h;
    }
    wyn[i+1] = lower_bound(tab+poczatek, tab+gora+1, 0)-tab-poczatek ;
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
  REP(i,n) {
    sort(wschzach[i].begin(), wschzach[i].end());
    sort(zachwsch[i].begin(), zachwsch[i].end());
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
