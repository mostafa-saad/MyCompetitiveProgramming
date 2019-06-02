/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wiedzmak (WIE)                                            *
 *   Plik:     wieb2.cpp                                                 *
 *   Autor:    Miroslaw Michalski                                        *
 *   Opis:     Rozwiazanie bledne z kolejka priorytetowa z STL'a.        *
 *             Zaczyna z wierzcholka [1;0].                              *
 *                                                                       *
 *************************************************************************/

#include <vector>
#include <cstdio>
#include <queue>

#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
using namespace std;


const int INF=1000000000; // nieskonczonosc
const int MAXN=521; // maksymalna liczba miast
const int MAXS=8221; // 2^(maksymalna liczba mieczy)

vector< pair< int, pair<int,int> > >  v[MAXN];

int tab[MAXN][MAXS]; // tab[i][j], oznacza, ze da sie dojsc do pozycji i, majac miecze bin(j)
int maska_kowala[MAXN]; // maski bitowe mowiace jakie miecze sa przez kowala wykuwane


int main() {
	int n,m,p,k,il_mieczy,maska,x,pk;

	scanf("%d%d%d%d",&n,&m,&p,&k);
		
	REP(i,k) {
		scanf("%d%d",&pk,&il_mieczy);
		pk--;
		REP(j,il_mieczy) {
			scanf("%d",&x); x--;
			maska_kowala[pk]|=(1<<x);
		}
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
		v[po].push_back(make_pair(ko,make_pair(cz,maska)));
		v[ko].push_back(make_pair(po,make_pair(cz,maska)));
	}

	REP(i,MAXN) REP(j,MAXS) tab[i][j]=INF;
	tab[0][0]=0;
	priority_queue<pair<int,pair<int,int> > > kolej;

	kolej.push(make_pair(0,make_pair(0,0)));
	
	int miasto, nowa_maska,nowa_odleg,j;
	pair<int,int> w;
	while (!kolej.empty()) {
		w=kolej.top().second; kolej.pop();
		miasto=w.first; maska=w.second;

		REP(i,v[miasto].size())	if ( ((v[miasto][i].second.second) |maska)==maska) {
			j=v[miasto][i].first;
			nowa_maska=(maska_kowala[j]|maska);
			nowa_odleg=tab[miasto][maska]+v[miasto][i].second.first;

			if (nowa_odleg<tab[j][nowa_maska]) {
				tab[j][nowa_maska]=nowa_odleg;
				kolej.push(make_pair(nowa_odleg,make_pair(j,nowa_maska)));
			}
		}
	}

	int wynik=INF;
	REP(i,(1<<p)) if (tab[n-1][i]<wynik) wynik=tab[n-1][i];
	if (wynik==INF) wynik=-1;

	printf("%d\n",wynik);

	return 0;
}

