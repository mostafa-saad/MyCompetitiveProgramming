/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odw6.cpp                                                   *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Rozwiazanie o zlozonosci zblizonej do rozwiazania          *}
{*            wzorcowego wyszukujacej liczby odwaznikow jakie mozna      *}
{*            zabrac przy pomocy wyszukiwania binarnego, jednak          *}
{*            sprawzdajacej czy sie da nie uzywajac multiseta            *}
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

int wagi[MAXN];
int rozm[MAXN];
int runda[MAXN];

int nw, nk;

bool daSie(int ile)
{
  int last=nk-1;
  for(int i=ile-1; i>=0; --i) {
    int r = 0;
    while( runda[last] < wagi[i] ) {
      last-=1;
      if( last < 0 ) last +=nk;
      if( r++ > nk ) return false;
    }
    runda[last] -= wagi[i];
  }
  return true;
}

int main()
{
  scanf("%d %d", &nk, &nw);
  REP(i,nk) scanf("%d", rozm+i);
  REP(i,nw) scanf("%d", wagi+i);

  sort(wagi, wagi+nw);

  int l=0, p = nw, res = 0;
  while(l <= p) {
    int med = (l+p)/2;
    REP(i,nk) runda[i] = rozm[i];
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
