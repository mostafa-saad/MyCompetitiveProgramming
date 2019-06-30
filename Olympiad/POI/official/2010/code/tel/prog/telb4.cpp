/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Teleporty (TEL)                               *
 *   Plik:                 telb4.cpp                                     *
 *   Autor:                Mirosław Michalski                            *
 *   Opis:                 Rozwiazanie niepoprawne - losujące.           *
 *   Kodowanie znaków:     UTF-8                                         *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <cstdlib>
#include <iostream>

const int MAXN = 223;
const int INF = 1000000000;

const int MAX_MOVES = 500;
const int MAX_NOT_SUCC = 200;

using namespace std;

struct Tab{
	int n;
	int a[MAXN][MAXN];
};

void floyd(Tab& v) {
	for(int k=0;k<v.n;k++) {
		for(int i=0;i<v.n;i++) {
			for(int j=0;j<v.n;j++) {
				v.a[i][j]=(v.a[i][j]>v.a[i][k]+v.a[k][j])?(v.a[i][k]+v.a[k][j]):(v.a[i][j]);
			}
		}
	}
}



int main() {
	srand(123);
	Tab map;
	bool g[MAXN][MAXN],t[MAXN][MAXN];
	bool niet[MAXN][MAXN];
	for(int i=0;i<MAXN;i++) {
		for(int j=0;j<MAXN;j++) {
			map.a[i][j] = INF*(i!=j);
			t[i][j] = (i==j);
			g[i][j] = (i==j);
		}
	}

	int n,m,a,b;

	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		a--; b--;
		t[a][b] = true;
		t[b][a] = true;
		g[a][b]=true;
		g[b][a]=true;
		map.a[a][b] = 1;
		map.a[b][a] = 1;
	}
	map.n = n;
	floyd(map);

	int not_succ = 0;
	while (not_succ<MAX_NOT_SUCC) {
		for(int i=0;i<n;i++) for(int j=0;j<n;j++) map.a[i][j] = t[i][j]?1:INF;
		
		int moves = 0;
		bool found = false;
		int x,y;
		while (!found) {
			moves++;
			x=rand()%n;
			y=rand()%(x+1);
			found = (!t[x][y]) && (!niet[x][y]);
			if (moves > MAX_MOVES) found=true;
		}
		t[x][y]=true; t[y][x]=true;
		map.a[x][y]=1; map.a[y][x]=1;
		floyd(map);
		
		if (map.a[0][1]<5) {
			t[x][y]=false;
			t[y][x]=false;
			niet[x][y]=true;
			niet[y][x]=true;
			not_succ++;
		}
	}

	int wynik=0;
	for(int i=0;i<n;i++) {
		for(int j=i+1;j<n;j++) wynik+=(t[i][j]!=g[i][j]); 
	}

	cout << wynik << endl;

	return 0;
}

