/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: EST (Estetyczny Tekst)                         *
 *   Plik:                ests0.cpp                                      *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                        Programowanie dynamiczne O(n^3), dodatkowo     *
 *                        kazda tablica jest wyliczana osobno.           *
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
const int INF = 2000000000;
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

int mniejsze[2100][2100];
int wieksze[2100][2100];
int wynik[2100][2100];


int suma(int z1, int z2) {
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

  
  // Kazda tablice wyliczamy osobno
  FOR(od,1,n-1) 
    FOR(dod,od,n-1) {
      mniejsze[od][dod] = INF;
      wieksze[od][dod]  =INF;
      wynik[od][dod] = INF;
      if (suma(od,dod)<=m) {
        FOR(poprz,0,od-1) {
        
        if (suma(od,dod)<=suma(poprz,od-1)) {
          mniejsze[od][dod] = min(mniejsze[od][dod],mniejsze[poprz][od-1]);
          wieksze[od][dod] = min(wieksze[od][dod],mniejsze[poprz][od-1]-2*(suma(od,dod)));
          wynik[od][dod] = min(wynik[od][dod],mniejsze[poprz][od-1]-suma(od,dod));
        }
        if (suma(od,dod)>=suma(poprz,od-1)) {
          mniejsze[od][dod] = min(mniejsze[od][dod],wieksze[poprz][od-1]+2*suma(od,dod));
            wieksze[od][dod] = min(wieksze[od][dod],wieksze[poprz][od-1]);
          wynik[od][dod] = min(wynik[od][dod],wieksze[poprz][od-1]+suma(od,dod));
        }
        }
      }
    }
  int mini = INF;
  REP(i,n) mini = min(mini,wynik[i][n-1]);

  printf("%d\n",mini);

  return 0;
}
