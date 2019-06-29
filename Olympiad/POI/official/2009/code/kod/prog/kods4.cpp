/************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kodowanie (KOD)                                           *
 *   Plik:     kods5.pas                                                 *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie wolne O(n*L). Nie korzysta z faktu, ze        *
 *             kody maja wspolne prefiksy.                               *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);++I)
#define FORD(I,A,B) for(int I=(A);I>=(B);--I)
#define REP(I,N) for(int I=0;I<(N);++I)

const int nmx=1500000;
int n,l,wh,lok;
int S[2][nmx],P[nmx],L[nmx],W[nmx];
bool wazny[nmx],synch[nmx];

int go(int v,int leaf,int lim=nmx){
	static int Q[nmx];
	int qh=0;
	int w=L[leaf];
	while(P[w] != -1 && lim>0){
		lim--;
		Q[qh++]=(S[0][P[w]]==w)?0:1;
		w=P[w];
	}
	if (lim) lok=0;
	while(qh--){
		if(S[0][v]==0) v=0;
		v=S[Q[qh]][v];
	}
	return v;
}

int main()
{
	static char buf[3000002]; 
	static int stos[nmx];
	int m,h=1,z;
	n=1;
	P[0]=-1;
	scanf("%d%s",&m,buf);
	REP(i,m)	switch(buf[i]){
		case 'B':
			h--;
			break;
		case 'X':
			L[l++]=stos[h-1];
			break;
		default:
			z=buf[i]-'0';
			S[z][stos[h-1]]=n;
			P[n]=stos[h-1];
			stos[h++]=n++;
			break;	
	}
	REP(j,l){
		int t;
		int l=1;
		lok=1;
		for(;;){
			t=go(0,j,l);
			if(!lok) break;
			l++;
			if(!wazny[t]){
				wazny[t]=1;
				W[wh++]=t;		
			}
		}
	}
	for(int i=0;i<wh;++i){
		REP(j,l){
			int t=go(W[i],j);
			if(!wazny[t]){
				wazny[t]=1;
				W[wh++]=t;		
			}
		}
	}
	REP(i,l) synch[L[i]]=1;
	REP(i,n) if (wazny[i]) {
		REP(j,l){
			int t=go(i,j);
			if (S[0][t]) synch[L[j]]=0;
		}
	}
	int wynik=0;
	REP(i,l) if(synch[L[i]]) wynik++;
	printf("%d\n",wynik);
	REP(i,l) if(synch[L[i]]) printf("%d\n",i+1);
	return 0;
}	
