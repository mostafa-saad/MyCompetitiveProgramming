/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odwb5.cpp                                                  *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Rozwiazanie niepoprawne                                    *}
{*                                                                       *}
{*************************************************************************/
#define REP(I,N)       for(int I=0; I<(N); ++I)


#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

typedef multiset<int> tRozm;

const int MAXN = 100000;

int wagi[MAXN];

tRozm sRozm;

int nw, nk;

int main()
{
  scanf("%d %d", &nk, &nw);
  REP(i,nk) {
    int tmp;
    scanf("%d", &tmp);
    sRozm.insert(tmp);    
  }
  REP(i,nw) scanf("%d", wagi+i);

  sort(wagi, wagi+nw);

  int res=0;
  while( res < nw) {
    tRozm::iterator it = sRozm.lower_bound(wagi[res]);
    if( sRozm.end() != it ) {
      int r = *it;
      sRozm.erase(it);
      r -= wagi[res];
      if( r ) 
        sRozm.insert(r);
    } else {
      break;
    }
    ++res;
  }
  printf("%d\n", res);

  return 0;
}

