/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Klocki (KLO)                                              *
 *   Plik:     klob2.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie niepoprawne. Losowanie wnetrza przedzialu.    *
 *                                                                       *
 *************************************************************************/ 

#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;
    
#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define FOR(i,a,b) for(int _b=(b),i=(a); i<=_b; ++i)
#define FORD(i,a,b) for(int _b=(b),i=(a); i>=_b; --i)

#define LL long long

#define MAX 1001000

#define INF (1000LL*MAX*1000*1000)

#define T (50*1000*1000)

int n,m,d;
LL k;
LL H[MAX];
LL SH[MAX];
int pre[MAX],suf[MAX];
int pc,sc;

int oblicz(){
    
    SH[0]=0;
    REP(i,n) SH[i+1]=SH[i]+H[i]-k;
    int p=0,q=0,best=0;
    REP(t,d){
	int g = rand()%(n+1);
	REP(i,g+1)  if (SH[i]<=SH[g]) {p=i; break;}
	FORD(i,n,g) if (SH[i]>=SH[g]) {q=i; break;}
	if (q-p > best) best=q-p;
    }
    return best;
}

int main(){
    srand(time(0));
    scanf("%d %d",&n,&m);
    d = T/(n*m);
    REP(i,n) scanf("%lld",&H[i]);
    REP(i,m) {
	scanf("%lld",&k);
	if (i) printf(" ");
	printf("%d",oblicz());
    }
    printf("\n");
    return 0;
}
