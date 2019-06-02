/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kolej (KOL)                                               *
 *   Plik:     kolb7.cpp                                                 *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie niepoprawne.                                  *
 * Przerobmy sobie zadanie na klocki, ktore mozemy klasc na dwa stosy i  *
 * zdejmowac zawsze najmniejszy jeszcze istniejacy. Teraz jedynym        *
 * pytaniem na ktore musimy tu umiec odpowiadac to, co zrobic w momencie,*
 * kiedy klocek mozemy polozyc na oba stosy. No wiec ja sobie patrze     *
 * kiedy bede mogl zdjac ten klocek i sprawdzam jaki jest najwiekszy     *
 * klocek, ktory sie pojawi do tego momentu (nazwijmy go X). To moge     *
 * zrobic efektywnie na jakims drzewku statycznym. No i teraz tak:       *
 * 1) jezeli X w obecnym ukladzie moglibysmy polozyc tylko na jednym ze  *
 * stosow, to jezeli istnieje rozwiazanie to tam go polozymy, wiec obecny*
 * klocek musimy polozyc na tym drugim stosie                            *
 * 2) jezeli X w obecnym ukladzie moglibysmy polozyc na obu stosach to   *
 * obecny klocek kladziemy na tym, gdzie moglibysmy polozyc wiekszy (to  *
 * jest moze malo intuicyjne) w ten sposob dajac sobie wiecej "luzu" w   *
 * przyszlosci jak juz ten klocek zdejmiemy (bo zdejmiemy go nie  pozniej*
 * niz X)                                                                *
 *                                                                       *
 *************************************************************************/



// {{{
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <list>
#include <complex>
#include <stack>
#include <cmath>
#include <iostream>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <utility>
#include <bitset>
#include <assert.h>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VII;
typedef vector<string> VS;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> PI;
typedef pair<LD,LD> PD;

#define VAR(v,n) __typeof(n) v=(n)
#define REP(i,n) for(int i=0; i<(n); i++)
#define FOR(i,a,b) for(int i=(a); i<=(b); i++)
#define FORD(i,a,b) for(int i=(a); i>=(b); i--)
#define FORE(i,c) for(VAR(i,(c).begin()); i!=(c).end(); i++)
#define CLR(A,v) memset((A),v,sizeof((A)))

#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define ALL(x) x.begin(),x.end()
#define SIZE(x) ((int)(x).size())
// }}}

#define M 100005
#define Q 300001
#define inf 1000000000

int n;
int T[M];
int W[Q],h;
int koniec[M];
int res[M];
int A[2][M],a[2];


inline int przedzial(int x, int y) {
	x+=(1<<h),y+=(1<<h);
	int w=max(W[x],W[y]);
	while (x!=y) {
		if (x%2==0 && x+1<y) w=max(w,W[x+1]);
		if (y%2==1 && x<y-1) w=max(w,W[y-1]);
		x/=2,y/=2;
	}
	return w;
}


int main() {
	scanf("%d",&n);
	REP(i,n) scanf("%d",&T[i]),T[i]--;

	for(h=0; (1<<h)<n; h++);
	REP(i,n) W[i+(1<<h)]=T[i];
	FORD(i,(1<<h)-1,1) 
		W[i]=max(W[2*i],W[2*i+1]);

	REP(i,n) koniec[T[i]]=i;
	FOR(i,1,n-1) 
		koniec[i]=max(koniec[i-1],koniec[i]);

	A[0][0]=A[1][0]=inf;
	a[0]=a[1]=1;

	int najw=0;
	REP(i,n) {
		if (T[i]<A[0][a[0]-1] && T[i]<A[1][a[1]-1]) {
			int w=przedzial(i,koniec[T[i]]);
			if (w<A[0][a[0]-1] && w<A[1][a[1]-1]) {
				if (A[0][a[0]-1]>A[1][a[1]-1]) A[0][a[0]++]=T[i];
				else A[1][a[1]++]=T[i];
			} else {
				if (w<A[0][a[0]-1]) A[1][a[1]++]=T[i];
				else A[0][a[0]++]=T[i];
			}
		} else {
			if (T[i]<A[0][a[0]-1])
				A[0][a[0]++]=T[i];
			else if (T[i]<A[1][a[1]-1])
				A[1][a[1]++]=T[i];
			else {
//				printf("%d\n",i);
				printf("NIE\n");
				return 0;
			}
		}
		while (A[0][a[0]-1]==najw || A[1][a[1]-1]==najw) {
			if (A[0][a[0]-1]==najw) a[0]--,res[A[0][a[0]]]=1;
			else a[1]--,res[A[1][a[1]]]=2;
			najw++;
		}
	}
	

	printf("TAK\n");
	REP(i,n) printf("%d ",res[T[i]]);
	printf("\n");
	return 0;
}
