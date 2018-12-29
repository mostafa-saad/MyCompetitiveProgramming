/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: EST (Estetyczny Tekst)                         *
 *   Plik:                estb0.cpp                                      *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwiazanie niepoprawne - zachlanne.           *
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
const LL INFi = 2000000000;
const LL INF = INFi*1000; 
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

LL tab[2100];


int main(){
  int n,m;
  scanf("%d %d",&m,&n);
  REP(i,n) {
    scanf("%d",&tab[i]);
    tab[i]++;
  }
  m++;
  LL wynik = 0;
  LL ile = 0;
  int ktora_linia = 0;
  int poprzednia_linia = 0;

  REP(i,n) {
    if (ile+tab[i]>m) {
      if (ktora_linia!=0) 
        wynik+=abs(ile-poprzednia_linia);
      ktora_linia++;
      poprzednia_linia = ile;
      ile = 0;
    }
    ile+=tab[i];
  }
  if (ile!=0) {
    if (ktora_linia!=0) 
      wynik+=abs(ile-poprzednia_linia);
    ktora_linia++;
    poprzednia_linia = ile;
  }

  printf("%lld\n",wynik);

  return 0;
}
