/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wiedzmak (WIE)                                            *
 *   Plik:     wieb1.cpp                                                 *
 *   Autor:    Miroslaw Michalski                                        *
 *   Opis:     Rozwiazanie bledne. Szuka najkrotszej sciezki nie         *
 *             przejmujac sie potworami.                                 *
 *                                                                       *
 *************************************************************************/

#include <vector>
#include <cstdio>
#include <queue>

#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
using namespace std;


const int INF=1000000000; // nieskonczonosc
const int MAXN=521; // maksymalna liczba miast

vector< pair<int,int> >  v[MAXN];

int tab[MAXN]; // tab[i][j], oznacza, ze da sie dojsc do pozycji i, majac miecze bin(j)


int main() {
	int n,m,p,k,il_mieczy,maska,x,pk;

	scanf("%d%d%d%d",&n,&m,&p,&k);
		
	REP(i,k) {
		scanf("%d%d",&pk,&il_mieczy);
		REP(j,il_mieczy) scanf("%d",&x);
	}

	int po,ko,il,cz;
	REP(i,m) {
		scanf("%d%d%d%d",&po,&ko,&cz,&il);
		maska=0;
		REP(j,il) {
			scanf("%d",&x); x--;
			maska+=(1<<x);
		}
		po--; ko--;
		v[po].push_back(make_pair(ko,cz));
		v[ko].push_back(make_pair(po,cz));
	}

	REP(i,MAXN) tab[i]=INF;
	tab[0]=0;
	queue<int> kolej;

	kolej.push(0);

	int miasto,nowa_odleg,j;
	while (!kolej.empty()) {
		miasto=kolej.front(); kolej.pop();
		REP(i,v[miasto].size()) {
			j=v[miasto][i].first;
			nowa_odleg=tab[miasto]+v[miasto][i].second;
			if (nowa_odleg<tab[j]) {
				tab[j]=nowa_odleg;
				kolej.push(j);
			}
		}
	}

	int wynik=INF;
	wynik=tab[n-1];
	if (wynik==INF) wynik=-1;

	printf("%d\n",wynik);

	return 0;
}

