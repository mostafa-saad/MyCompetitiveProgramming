/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Chomiki (CHO)                                             *
 *   Plik:     chob2.cpp                                                 *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie niepoprawne - poczatek a potem modulo.        *
 *                                                                       *
 *************************************************************************/ 

// Headers {{{
#include<iostream>
#include<assert.h>
#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<list>
#include<deque>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<utility>
#include<sstream>
#include<cstring>
#include<bitset>
#include<numeric>
using namespace std;


#define FOR(I,A,B) for(int I=(A);I<=(B);++I)
#define FORD(I,A,B) for(int I=(A);I>=(B);--I)
#define REP(I,N) for(int I=0;I<(N);++I)
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();++I)
#define CLR(A,v) memset((A),v,sizeof((A)))

#define SIZE(x) ((int)((x).size()))
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define FI first
#define SE second

typedef vector<int> VI;
typedef pair<int,int> PI;
typedef long long LL;
typedef vector<string> VS;
// }}}

const int bmx=100003,nmx=203;
const LL inf=(LL)1e17;

const int beglen = 1000;


int n,m;
int L[nmx],P[bmx];
char *S[nmx];
char buf[bmx];
LL T[nmx][nmx];
LL D[beglen][nmx];
int F[beglen][nmx];


int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i){
		scanf("%s",buf);
		S[i]=strdup(buf);
		L[i]=strlen(S[i]);
	}
	for(int i=0;i<n;i++){
		int x=0;
		for(int j=1;j<L[i];++j){
			while (x > 0 && S[i][x] != S[i][j])
				x=P[x-1];
			if(S[i][x]==S[i][j]) x++;
			P[j]=x;
		}
		for(int k=0;k<n;++k){
			int beg=0;
			if(k==i) beg=1;
			int x=0;
			for(int j=beg;j<L[k];++j){
				while (x > 0 && S[i][x] != S[k][j]) 
					x=P[x-1];
				if(S[i][x]==S[k][j]) x++;
			}
			T[k][i]=L[i]-x;
		}

		T[n][i]=L[i];
		T[i][n]=inf;
	}
	T[n][n]=inf;
	for(int i=0;i<n;i++) D[0][i]=L[i];
	for(int i=1;i<beglen;i++){
		for(int j=0;j<n;j++){
			D[i][j]=inf;
			for(int k=0;k<n;k++)
				if (D[i][j]  > D[i-1][k] + T[k][j]){
					D[i][j]=D[i-1][k]+T[k][j];
					F[i][j]=k;
				}	
		}
	}
	
  	LL result=inf;
	if ( beglen  > m ){
		for(int i=0;i<n;i++)
			result=min(result,D[m-1][i]);
	}
	else{
		for(int i=0;i<n;i++){
			assert(beglen > n);
			vector<int> t;
			int x=i;
			int v=beglen-1;
			int sum=0;
			for (int j=0;j<n;j++)
			{
				t.PB(D[v][x]-D[v-1][F[v][x]]);
				sum+=t.back();
				x=F[v][x];
				v--;
				if(x==i){
					reverse(ALL(t));
					int md=SIZE(t);
					LL res=D[beglen-1][i]+ ((m-beglen)/md) *	(LL)sum;
					REP(k,m%md) res+=t[k];
					result=min(result,res);
					break;
				}
			}
		}
	}
	printf("%lld\n",result);
	return 0;
}
