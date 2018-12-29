/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klo.cpp                                          *
 *   Autor:             Michal Pilipczuk                                 *
 *   Opis:              Rozwiazanie wzorcowe.                            *
 *   Zlozonosc czasowa: O(n * m)                                         *
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
int pre[MAX],suf[MAX];
int pc,sc;

int oblicz(){
    
    SH[0]=0;
    REP(i,n) SH[i+1]=SH[i]+H[i]-k;
    
    pc=sc=0;
    LL b = INF;
    REP(i,n+1) if (b>SH[i]){
	pre[pc++]=i;
	b=SH[i];
    }
    b = -INF;
    FORD(i,n,0) if (b<SH[i]){
	suf[sc++]=i;
	b=SH[i];
    }
    
    int c=sc-1;
    int best=0;
    REP(i,pc){
	while (c>=0 && SH[suf[c]]>=SH[pre[i]]) c--;
	if (c+1<sc && SH[suf[c+1]]>=SH[pre[i]] && best<suf[c+1]-pre[i])
	    best=suf[c+1]-pre[i];
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
