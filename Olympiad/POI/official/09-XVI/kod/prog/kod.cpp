/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kodowanie (KOD)                                           *
 *   Plik:     kod.cpp                                                   *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie wzorcowe O(L)                                 *
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
int n,l,wh;
int S[2][nmx],L[nmx],W[nmx];
bool wazny[nmx],synch[nmx];
bool byl[nmx];

void dfs1(int x,int y){
	if (!S[0][y]){
		if(!wazny[x]){
			wazny[x]=1;
			W[wh++]=x;
		}
	}
	else if (S[0][x]) {
		dfs1(S[0][x],S[0][y]);
		dfs1(S[1][x],S[1][y]);
	}
}

void dfs2(int x,int y){
	if (!S[0][y]){
		if(!wazny[x]){
			wazny[x]=1;
			W[wh++]=x;
		}
	}
	else{
		if (!S[0][x]){
			if (!byl[y]){
				byl[y]=1;
				dfs2(0,y);
			}
		}
		else{
			dfs2(S[0][x],S[0][y]);
			dfs2(S[1][x],S[1][y]);
		}
	}
}

void dfs3(int x,int y){
	if (!S[0][y]){
		if(S[0][x]) synch[y]=0;
	}
	else{
		if (!S[0][x]){
			if (!byl[y]){
				byl[y]=1;
				dfs3(0,y);
			}
		}
		else{
			dfs3(S[0][x],S[0][y]);
			dfs3(S[1][x],S[1][y]);
		}
	}
}



int main()
{
	static char buf[3000002]; 
	static int stos[nmx];
	int m,h=1,z;
	n=1;
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
			stos[h++]=n++;
			break;	
	}
	REP(i,n) dfs1(0,i);
	for(int i=0;i<wh;++i) dfs2(W[i],0);
	REP(i,n) byl[i]=0;
	REP(i,l) synch[L[i]]=1;
	REP(i,wh) dfs3(W[i],0);	
	int wynik=0;
	REP(i,l) if(synch[L[i]]) wynik++;
	printf("%d\n",wynik);
	REP(i,l) if(synch[L[i]]) printf("%d\n",i+1);
	return 0;
}	
