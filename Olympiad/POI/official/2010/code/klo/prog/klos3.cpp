/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klos3.cpp                                        *
 *   Autor:             Michal Pilipczuk                                 *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Algorytm skaczacy po maksimach.                  *
 *   Zlozonosc czasowa: O(m * n^2)                                       *
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
int pnt[MAX];

int oblicz(){
    SH[0]=0;
    REP(i,n) SH[i+1]=SH[i]+H[i]-k;
    int best=0;
    int d=-1;
    LL mn=INF,mx=-INF;
    FORD(i,n,0){
	pnt[i]=d;
	if (SH[i]>mx){
	    mx=SH[i];
	    d=i;
	}
    }
    REP(i,n+1){
	if (mn>SH[i]){
	    mn=SH[i];
	    d=i;
	    while (pnt[d]>=0 && SH[pnt[d]]>=mn) d=pnt[d];
	    if (d-i > best) best = d-i;
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
