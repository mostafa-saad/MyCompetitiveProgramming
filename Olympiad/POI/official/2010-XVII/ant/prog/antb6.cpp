/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Antysymetria (ANT)                               *
 *   Plik:              antb6.cpp                                        *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie niepoprawne.                         *
 *                      Rozwiazanie nie uzywa haszowania.                *
 *   Zlozonosc czasowa: O(n * log n)                                     *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <cstdio>
#include <algorithm>

#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)
const int MAXN=500011;
typedef long long LL;

const long long MOD = 100000007;

using namespace std;

char s[MAXN];
int hash_p[MAXN],hash_k[MAXN],il1[MAXN],dwa[MAXN];

int main() {
int n;
scanf("%d",&n);
scanf("%s",s);

long long wynik=0;

int pocz,kon,max_radius,sr;

FOR(i,0,n-2) if (s[i]!=s[i+1]) {
    max_radius=min(i+1,n-1-i);
    pocz=i+1;
    kon=i+max_radius;
	while (pocz<kon) {
	    sr=kon+(pocz-kon+1)/2; 
	    if (s[sr]!=s[2*i-sr-1]) pocz=sr; else kon=sr-1;
	    }
    wynik+=kon-i;
    }    

printf("%lld\n",wynik);
return 0;
}
