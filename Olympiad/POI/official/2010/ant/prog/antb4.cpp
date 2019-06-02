/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Antysymetria (ANT)                               *
 *   Plik:              antb4.cpp                                        *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie niepoprawne.                         *
 *                      Rozwiazanie sprytnie haszuje, dzieki czemu       *
 *                      porownanie czy dwa podciagi sa sobie rowne, jest *
 *                      b. szybkie. Uzywa dosc malej liczby pierwszej.   *
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

const long long MOD = 1000033;
using namespace std;

char s[MAXN];
int hash_p[MAXN],hash_k[MAXN],dwa[MAXN];

int main() {
int n;
scanf("%d",&n);
scanf("%s",s);

long long wynik=0;
dwa[0]=1; FOR(i,1,n) dwa[i]=(dwa[i-1]*2)%MOD;

// Liczenie hasha od poczatku oraz liczenie ilosci jedynek
    hash_p[0]=0;
    if (s[0]=='1') hash_p[1]=1; else  hash_p[1]=0;
    FOR(i,1,n-1) if (s[i]=='1') hash_p[i+1]=(hash_p[i]+dwa[i])%MOD; else hash_p[i+1]=hash_p[i];
// Liczenie hasha od konca
    if (s[n-1]=='0') hash_k[n-1]=1; else hash_k[n-1]=0;
    FORD(i,n-2,0) if (s[i]=='0') hash_k[i]=(hash_k[i+1]+dwa[n-i-1])%MOD; else hash_k[i]=hash_k[i+1];
        
        
int pocz,kon,max_radius,value_right,value_left,sr,toadd;

FOR(i,0,n-2) if (s[i]!=s[i+1]) {
    max_radius=min(i+1,n-1-i);
    pocz=i+1;
    kon=i+max_radius;
	while (pocz<kon) {
	    sr=kon+(pocz-kon+1)/2; 
	    value_right=hash_k[i+1]-hash_k[sr+1]; value_right+=MOD; value_right%=MOD;
	    value_left=hash_p[i+1]-hash_p[i-(sr-i)+1]; value_left+=MOD; value_left%=MOD;
	    toadd=-(n-1-sr)+(i-(sr-i)+1);
	    if (toadd>0) value_right=(LL(value_right)*LL(dwa[toadd]))%MOD;
	    if (toadd<0) value_left=(LL(value_left)*LL(dwa[toadd*(-1)]))%MOD;
	    if (value_right==value_left) pocz=sr; else kon=sr-1;
	    }
    wynik+=kon-i;
    }    

printf("%lld\n",wynik);
return 0;
}
