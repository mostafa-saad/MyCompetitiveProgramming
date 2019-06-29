/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Stacja (STA)                                              *
 *   Plik:     sta2.cpp                                                  *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie alternatywne.                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

#define MAX_N 1000001


int n;			// ilosc wierzcholkow grafu
vector<int> T[MAX_N];	// opis krawedzi grafu

char vis[MAX_N];		// flaga odwiedzania wierzcholka
int il[MAX_N];			// ilosc wierzcholkow w poddrzewie
long long sum_odl[MAX_N];	// suma odleglosci z poddrzewa
long long res;			// najwieksza dotychczasowa suma
int nr;				// numer najlepszego dotychczas wierzcholka


inline void dfs(int x) {
	vis[x]=1;

	for(int i=0; i<(int)T[x].size(); i++) if (!vis[T[x][i]]) {
		dfs(T[x][i]);
		il[x]+=il[T[x][i]];
		sum_odl[x]+=sum_odl[T[x][i]]+il[T[x][i]];
	}
	il[x]++;
}


inline void oblicz(int x, long long w) {
	vis[x]=1;

	if (w>res) res=w,nr=x;

	for(int i=0; i<(int)T[x].size(); i++) if (!vis[T[x][i]]) {
		oblicz(T[x][i],w+n-2*il[T[x][i]]);
	}
}


int main() {
	scanf("%d",&n);

	int a,b;
	for(int i=0; i<n-1; i++) {
		scanf("%d%d",&a,&b);
		a--,b--;
		T[a].push_back(b),T[b].push_back(a);
	}

	dfs(0);

	res=sum_odl[0],nr=0;
	for(int i=0; i<n; i++) vis[i]=0;
	oblicz(0,res);


	printf("%d\n",nr+1);
	return 0;
}
