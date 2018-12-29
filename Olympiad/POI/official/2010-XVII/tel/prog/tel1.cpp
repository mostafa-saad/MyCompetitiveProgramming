/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Teleporty (TEL)                               *
 *   Plik:                 tel1.cpp                                      *
 *   Autor:                Mirosław Michalski                            *
 *   Opis:                 Rozwiązanie weryfikujące.                     *
 *   Zlozonosc czasowa:    O(n + m)                                      *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
 *   Kodowanie znaków:     UTF-8                                         *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>

const int MAXN=1000023;
const int INF = 1000000000;
using namespace std;
typedef vector<int> VI;
int main() {
	int n,m;
	VI t[MAXN];
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		x--; y--;
		t[x].push_back(y);
		t[y].push_back(x);
	}
	int w1=0,w2=0,w3=0,w4=0;
	int depth[MAXN][2]; for(int i=0;i<MAXN;i++) for(int j=0;j<2;j++) depth[i][j]=INF;
	queue<pair<int,int> > kolej;
	kolej.push(make_pair(0,0)); depth[0][0]=0;
	kolej.push(make_pair(1,1)); depth[1][1]=0;

		while (!kolej.empty()) {
			pair<int,int> w=kolej.front(); kolej.pop();
			int poz=w.first, kto=w.second;
			for(int i=0;i<(int)t[poz].size();i++) if (depth[t[poz][i]][kto]>depth[poz][kto]+1 && depth[poz][kto]<=1) {
				depth[t[poz][i]][kto]=depth[poz][kto]+1;
				kolej.push(make_pair(t[poz][i],kto));
			}
		}
	for(int i=0;i<n;i++) {
		if (depth[i][0]==1) w1++;
		if (depth[i][0]==2) w2++;
		if (depth[i][1]==1) w3++;
		if (depth[i][1]==2) w4++;
	}
	
	int wynik1=n*(n-1)/2-m-w1*w3-w1*w4-w2*w3-(n-w1-1)-(n-w3-1)-min(w1,w3)*(n-2-w1-w2-w3-w4)+1;
	swap(w1,w3);
	swap(w2,w4);
	int wynik2=n*(n-1)/2-m-w1*w3-w1*w4-w2*w3-(n-w1-1)-(n-w3-1)-min(w1,w3)*(n-2-w1-w2-w3-w4)+1;

	printf("%d\n",max(wynik1,wynik2));
	return 0;
}

