/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kodowanie (KOD)                                           *
 *   Plik:     kodb3.cpp                                                 *
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

const int ile_losowan=5;
const int nmx=1500000;
string S[nmx];
bool syn[nmx];
int n,res;

bool odkoduj(string s)
{
	int l=s.length();
	string pref="";
	REP(i,l)
	{
		pref+=s[i];
		REP(j,n) if (pref==S[j]) {pref=""; break;}	
	}
	return pref=="";
}

int main()
{
	srand(42);
	static char tmp[3000001],tmp2[1500000];
	int z,h=0;
	scanf("%d%s",&z,tmp);
	REP(i,z)
		switch(tmp[i]){
			case 'X':
				tmp2[h]=0; S[n++]=tmp2;
				break;
			case '1':
				tmp2[h++]='1';
				break;
			case '0':
				tmp2[h++]='0';
				break;
			case 'B':
				h--;
				break;
		}
	REP(i,n)
	{
		syn[i]=1;
		REP(j,n) if (S[j].length()>1)
		{
			REP(k,ile_losowan)
			{
				int z=rand()%(S[j].length()-1)+1;
					if (!syn[i]) break;
					syn[i]&=odkoduj(S[j].substr(z)+S[i]);
			}
		}
		if (syn[i]) res++;
	}
	printf("%d\n",res);
	REP(i,n)if(syn[i])printf("%d\n",i+1);
	return 0;
}
