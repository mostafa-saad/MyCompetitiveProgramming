/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klob3.cpp                                        *
 *   Autor:             Michal Pilipczuk                                 *
 *   Opis:              Rozwiazanie niepoprawne.                         *
 *                      Symulacja zachlanna.                             *
 *   Zlozonosc czasowa: O(m * n^3)                                       *
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
LL HP[MAX];

int oblicz(){
    int s=0,p,q,r=0,best=0;
    LL z;
    REP(i,n) H[i]=HP[i];
    
    do {
	s=0;
	REP(i,n) if (H[i]>k){
	    for (p=i-1;p>=0;p--) if (H[p]<k) break;
	    for (q=i+1;q<n;q++)  if (H[q]<k) break;
	    if (p<0 && q>=n) continue;
	    s++;
	    if (q>=n) q=p; if (p<0) p=q;
	    if (H[p]!=H[q]) r=((H[p]<H[q])?q:p);
	    else if (i-p!=q-i) r=((i-p<q-i)?q:p);
	    else r=q;
	    z=((H[i]-k>k-H[r])?(k-H[r]):(H[i]-k));
	    H[i]-=z; H[r]+=z;
	}
    } while (s>0);
    
    s=0;
    REP(i,n){
	if (H[i]>=k) s++; else s=0;
	if (s>best) best=s;
    }
    
    do {
	s=0;
	REP(i,n) if (H[i]>k){
	    for (p=i-1;p>=0;p--) if (H[p]<k) break;
	    for (q=i+1;q<n;q++)  if (H[q]<k) break;
	    if (p<0 && q>=n) continue;
	    s++;
	    if (q>=n) q=p; if (p<0) p=q;
	    if (i-p!=q-i) r=((i-p<q-i)?q:p);
	    else if (H[p]!=H[q]) r=((H[p]<H[q])?q:p);
	    else r=q;
	    z=((H[i]-k>k-H[r])?(k-H[r]):(H[i]-k));
	    H[i]-=z; H[r]+=z;
	}
    } while (s>0);
    
    s=0;
    REP(i,n){
	if (H[i]>=k) s++; else s=0;
	if (s>best) best=s;
    }
    
    return best;
}

int main(){
    scanf("%d %d",&n,&m);
    REP(i,n) scanf("%lld",&HP[i]);
    REP(i,m) {
	scanf("%lld",&k);
	if (i) printf(" ");
	printf("%d",oblicz());
    }
    printf("\n");
    return 0;
}
