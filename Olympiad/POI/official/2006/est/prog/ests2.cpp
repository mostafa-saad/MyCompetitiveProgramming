/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: EST (Estetyczny Tekst)                         *
 *   Plik:                ests2.cpp                                      *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Obliczana jest tylko wynikowa tablica, a       *
 *                        pozostale na jej podstawie.                    *
 *                        Zlozonosc: O(n^3) (z usprawnieniami)           *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
#define VAR(a,b) typeof(b) a=(b)
#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)
#define FOREACH(it,c) for(VAR(it,(c).begin());it!=(c).end();++it)
#define ALL(f,w) ({ bool _ok=true; f _ok=_ok && (w); _ok; })
#define EXISTS(f,w) (!ALL(f,!(w)))
typedef long long LL;
const LL INF = 2000000000;
typedef vector<int> VI;
template<class T> inline int size(const T&c) { return c.size(); }
template<class T> inline vector<T> makeV(const T&x) { return vector<T>(1,x); }
template<class T> inline vector<T> makeV(const T&x,const T&y) {
    vector<T> v(2); v[0] = x; v[1] = y; return v;
}
template<class T> inline vector<T> makeV(const T&x,const T&y,const T&z) {
    vector<T> v(3); v[0] = x; v[1] = y; v[2]=z; return v;
}
template<class A,class B> inline bool contains(const A&a, const B&b) {
    return find(a.begin(),a.end(),b)!=a.end();
}

int tab[2100];

LL mniejsze[2100][2100];
LL wieksze[2100][2100];
LL wynik[2100][2100];


LL suma(int z1, int z2) {
  if (z1==0) return tab[z2];
  return (tab[z2]-tab[z1-1]);
}

int main(){
  int n,m;
  scanf("%d %d",&m,&n);
  REP(i,n) {
    scanf("%d",&tab[i]);
    tab[i]++;
    if (i!=0) tab[i]+=tab[i-1];
  }
  m++;

  FOR(dod,0,n-1) {
    mniejsze[0][dod] = INF;
    wieksze[0][dod] = INF;
    wynik[0][dod] = INF;
    if (suma(0,dod)<=m) {
      mniejsze[0][dod] = suma(0,dod);
      wieksze[0][dod] = -suma(0,dod);
      wynik[0][dod] = 0;
    }
  }
  FOR(dod,1,n-1) {
    FOR(od,1,dod) {
      wynik[od][dod] = INF;
      if (suma(od,dod)<=m) {
        
        FOR(poprz,0,od-1) 
        if (suma(poprz,od-1)<=m) {
          if (suma(od,dod)<=suma(poprz,od-1)) {
            wynik[od][dod] = min(wynik[od][dod],mniejsze[poprz][od-1]-suma(od,dod));
          }
          if (suma(od,dod)>=suma(poprz,od-1)) {
            wynik[od][dod] = min(wynik[od][dod],wieksze[poprz][od-1]+suma(od,dod));
          }
        }

      }
    }
    FOR(od,1,dod) {
      mniejsze[od][dod] = min(INF,wynik[od][dod]+suma(od,dod));
      mniejsze[od][dod] = min(mniejsze[od][dod],mniejsze[od-1][dod]);
    }
    FORD(od,dod,1) {
      wieksze[od][dod] = min(INF,wynik[od][dod]-suma(od,dod));
      if (od!=dod)
        wieksze[od][dod] = min(wieksze[od][dod],wieksze[od+1][dod]);
    }
  }

  LL mini = INF;
  REP(i,n) mini = min(mini,wynik[i][n-1]);

  printf("%lld\n",mini);

  return 0;
}
