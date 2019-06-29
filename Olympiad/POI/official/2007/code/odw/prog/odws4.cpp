/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odws4.cpp                                                  *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Rozwiazanie nieoptymalne                                   *}
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

typedef multiset<int> tWagi;
tWagi tmp;

int wagi[MAXN];
int rozm[MAXN];

int nw, nk;

bool daSie(int ile)
{
  for(int i=ile-1; i>=0; --i) {
    tWagi::iterator it = tmp.lower_bound(wagi[i]);
    if( tmp.end() == it ) {
      return false;
    } else {
      tmp.erase(it);
      int poj = *it;
      poj -= wagi[i];
      if( poj )
        tmp.insert(poj);
    }
  }
  return true;
}

int main()
{
  scanf("%d %d", &nk, &nw);
  REP(i,nk) scanf("%d", rozm+i);
  REP(i,nw) scanf("%d", wagi+i);

  sort(wagi, wagi+nw);
  sort(rozm, rozm+nk);

  int l=0, p = nw, res = 0;

  while(l <= p) {
    int med = (l+p)/2;
    tmp.clear();
    tmp.insert(rozm,rozm+nk);
    if( daSie(med) ) {
      l = med+1;
      res = med;
    } else {
      p = med -1;
    }
  }
  printf("%d\n",res);

  return 0;
}
