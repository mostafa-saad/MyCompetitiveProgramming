/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kodowanie (KOD)                                           *
 *   Plik:     kodb2.cpp                                                 *
 *   Autor:    Marek Biskup                                              *
 *   Opis:     Rozwiazanie bledne.                                       *
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

const int nmx=1000000;
int n,l;
int S[2][nmx],L[nmx];
bool wazny[nmx],zly[nmx];
bool byl[nmx];

void ustawWazne(int x,int y){
	if (x)wazny[x]=1;
}

void ustawZly(int x,int y){
	if (x) zly[y]=1;
}


void dfs(int x,int y ,void(*f)(int,int) )
{
	static int X[nmx],Y[nmx],h;
	h=1,X[0]=x,Y[0]=y;
	while (h)
	{
		h--;
		x=X[h],y=Y[h];
		if (!S[0][x]) x=0;
		if (x==0 && byl[y]) continue;
		if (x==0) byl[y]=1;
		if (S[0][y]){
			REP(d,2){
				X[h]=S[d][x]; Y[h]=S[d][y];
				h++;
			}
		}
		else f(x,y);
	}
}

int main()
{
	static char buf[3000002]; 
	static int stack[nmx];
	int m,h=1,z;
	n=1;
	scanf("%d%s",&m,buf);
	REP(i,m)	switch(buf[i]){
		case 'B':
			h--;
			break;
		case 'X':
			L[l++]=stack[h-1];
			break;
		default:
			z=buf[i]-'0';
			S[z][stack[h-1]]=n;
			stack[h++]=n++;
			break;	
	}
	FOR(i,1,n-1) if (S[0][i]) dfs(0,i,ustawWazne);
	REP(i,n) byl[i]=0;
	FOR(i,1,n-1) if (wazny[i]) dfs(i,0,ustawZly);
	int wynik=0;
	REP(i,l) if(!zly[L[i]]) wynik++;
	printf("%d\n",wynik);
	REP(i,l) if(!zly[L[i]]) printf("%d\n",i+1);
	return 0;
}	
