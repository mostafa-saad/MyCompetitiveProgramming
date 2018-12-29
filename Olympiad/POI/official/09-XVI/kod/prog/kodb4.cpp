/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kodowanie (KOD)                                           *
 *   Plik:     kodb4.cpp                                                 *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Heurystyka. Losuje napisy binarne i sprawdza czy          *
 *             kody sa synchronizujace dla tych napisow.                 *
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

const int nmx=1500010;
int S[2][nmx],n,m,P[nmx];
int T[nmx];
char C[3000010];
bool CH[nmx];
int sum;
VI N;
VI res;
// MakeTree {{{
void MakeTree()
{
	VI node;
	node.PB(0);
	CLR(S,-1);
	n=1; 
	REP(z,m)
		switch (C[z])
		{
			case 'X':
				sum=max(sum,(int)SIZE(node));
				N.PB(node.back());
			break;
			case 'B':
				node.pop_back();
			break;
			case '0':
				P[n]=node.back();
				S[0][node.back()]=n;
				node.PB(n++);
			break;
			case '1':
				P[n]=node.back();
				S[1][node.back()]=n;
				node.PB(n++);
			break;
		};
}
// }}}

int main()
{
	srand(42);;
	scanf("%d%s",&m,C);
	MakeTree();
	int los=300000000/(sum*SIZE(N));
	FORE(i,N)			// wyznaczenie punktow do kontroli
	{
		int x=*i;
		while (x){
			T[P[x]]=(S[0][P[x]]==x?0:1);
			x=P[x];
		}
		while (x!=*i)
		{
			int v=0,z=x;
	if(rand()%10<3){
	
			while (z!=*i)
				{
					v=S[T[z]][v];
					if (S[0][v]==-1) v=0;
					z=S[T[z]][z];	
				}
	}
			CH[v]=1;
			x=S[T[x]][x];
		}
	}	
	FORE(i,N)
	{
		int x=*i;
		while (x){
			T[P[x]]=(S[0][P[x]]==x?0:1);
			x=P[x];
		}
		int v;
		bool ok=1;
		REP(ls,los)
		{
			int j=rand()%n;
			if (!CH[j]) continue;
			v=j;
			if (S[0][v]==-1) v=0;
			x=0;
			while (x!=*i)
			{
				v=S[T[x]][v];
				x=S[T[x]][x];
				if (S[0][v]==-1) v=0;
			}
			if(v) 
			{
				ok=0;
				break;
			}
		}
		if (ok) res.PB(i-N.begin()+1);
	}
	printf("%d\n",(int)res.size());
	FORE(i,res) printf("%d\n",*i);

	return 0;
}
