/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klos6.cpp                                        *
 *   Autor:             Michal Pilipczuk                                 *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Wyszukiwanie binarne maksimow sufiksowych.       *
 *   Zlozonosc czasowa: O(m * n * log n)                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>

using namespace std;
    
#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define FOR(i,a,b) for(int _b=(b),i=(a); i<=_b; ++i)
#define FORD(i,a,b) for(int _b=(b),i=(a); i>=_b; --i)

#define LL long long

#define MAX 1001000
#define INF (1000LL*MAX*1000*1000)

int n,m;
LL k;
LL H[MAX];
LL SH[MAX];
int suf[MAX];

int oblicz(){
    SH[0]=0;
    REP(i,n) SH[i+1]=SH[i]+H[i]-k;
    int best=0;
    LL mx=-INF,mn=INF;
    int ps=0;
    FORD(i,n,0){
	if (SH[i]>mx){
	    mx=SH[i];
	    suf[ps++]=i;
	}
    }
    REP(i,n+1){
	if (mn>SH[i]){
	    mn=SH[i];
	    int lo=0,hi=ps-1;
	    while (lo<hi){
		int s=(lo+hi)>>1;
		if (SH[suf[s]]>=mn) hi=s; else lo=s+1;
	    }
	    if (lo<ps && SH[suf[lo]]>=mn && best<suf[lo]-i) best=suf[lo]-i;
	}
    }
    return best;
}

int main(){
    scanf("%d %d",&n,&m);
    REP(i,n) scanf("%lld",&H[i]);
    REP(i,m) {
	scanf("%lld",&k);
	if (i) printf(" ");
	printf("%d",oblicz());
    }
    printf("\n");
    return 0;
}
