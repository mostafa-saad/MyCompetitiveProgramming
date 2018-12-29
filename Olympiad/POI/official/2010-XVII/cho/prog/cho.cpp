/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Chomiki (CHO)                                             *
 *   Plik:     cho.cpp                                                   *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie wzorcowe.                                     *
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

struct M{
	LL T[nmx][nmx];
	void operator*=(const M &b){
		static LL t[nmx][nmx];
		for(int i=0;i<n;++i)
		  for(int j=0;j<n;++j){
				LL w=inf;
				for(int k=0;k<n;k++)
					w=min(w,T[i][k]+b.T[k][j]);
				t[i][j]=w;
		  }	  
		for(int i=0;i<n;++i)
		  for(int j=0;j<n;++j) T[i][j]=t[i][j];
	}
};

M stn;
M res;

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
			stn.T[k][i]=L[i]-x;
		}

		stn.T[n][i]=L[i];
		stn.T[i][n]=inf;
	}
	stn.T[n][n]=inf;
	n++;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++) res.T[i][j]=inf;
	res.T[n-1][n-1]=0;
	for(int i=0;i<31;i++){
		if (m&(1<<i))
			res*=stn;
		stn*=stn;
	}	
	LL result=inf;
	for(int i=0;i<n-1;++i) result=min(result,res.T[n-1][i]);
  	printf("%lld\n",result);
	return 0;
}
