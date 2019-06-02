/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Chomiki (CHO)                                             *
 *   Plik:     chob1.cpp                                                 *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie niepoprawne - uzywanie tylko jednego slowa.   *
 *                                                                       *
 *************************************************************************/ 

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;


typedef long long LL;
const int bmx=100003,nmx=203;
const LL inf=(LL)1e17;

int n,m;
int L[nmx],P[bmx];
char *S[nmx];
char buf[bmx];
LL T[nmx][nmx];

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
  	LL result=inf;
	for(int i=0;i<n;i++)
		result=min(result,L[i]+T[i][i]*(m-1));
	printf("%lld\n",result);
	return 0;
}
