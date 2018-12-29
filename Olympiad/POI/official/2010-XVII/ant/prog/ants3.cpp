/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Antysymetria (ANT)                               *
 *   Plik:              ants3.cpp                                        *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Rozwiazanie brutalne, dla dwoch roznych          *
 *                      elementow stojacych kolo siebie, stara sie       *
 * .                    znalezc promien najdluzeszego antypalindromu.    *
 *                      Rozwiazanie uzywa long longow.                   *
 *   Zlozonosc czasowa: O(m), gdzie m jest wynikiem                      *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <cstdio>

#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)

const int MAXN=500011;

using namespace std;

char s[MAXN];

int main() {
int n;
scanf("%d",&n);
scanf("%s",s);
long long wynik=0,r=0;

FOR(i,1,n-1) if (s[i]!=s[i-1]) {
    r=1;
    while (i-r-1>=0 && i+r<n && s[i-r-1]!=s[i+r]) r++; 
    wynik+=r;
    }

printf("%lld\n",wynik);
return 0;
}
. 