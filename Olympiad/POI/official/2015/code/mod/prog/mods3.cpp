/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Modernizacja autostrady                            *
 *   Zlozonosc czasowa:    O(n^5)                                             *
 *   Autor programu:       Kamil Debowski                                     *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                                                                            *
 *****************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
#include<vector>
using namespace std;
typedef pair<int, int> pii;

const int nax = 500123;

int n;
vector<pii > drogi;
vector<int> w[nax];
bool vis[nax];
int h[nax];

int liczSrednice() {
	for(int i = 1; i <= n; ++i) w[i].clear();
	int res = 0;
	for(int i = 0; i < n - 1; ++i) {
		int a = drogi[i].first, b = drogi[i].second;
		w[a].push_back(b);
		w[b].push_back(a);
	}
	for(int root = 1; root <= n; ++root) {
		for(int i = 1; i <= n; ++i) vis[i] = false;
		vector<int> kol;
		kol.push_back(root);
		vis[root] = true;
		h[root] = 0;
		for(int i = 0; i < (int) kol.size(); ++i) {
			int a = kol[i];
			res = max(res, h[a]);
			for(int j = 0; j < (int) w[a].size(); ++j) {
				int b = w[a][j];
				if(!vis[b]) {
					h[b] = h[a] + 1;
					vis[b] = true;
					kol.push_back(b);
				}
			}
		}
		if((int) kol.size() != n) return -1;
	}
	return res;
}
	
struct odp {
	int a;
	pii bylo;
	pii bedzie;
	odp(int _a) { a = _a; }
	odp(int _a, pii b, pii c) {
		a = _a;
		bylo = b;
		bedzie = c;
	}
	void wypisz() {
		printf("%d %d %d %d %d\n", a, bylo.first, bylo.second, bedzie.first, bedzie.second);
	}
};

int main() {
	odp maly = odp(nax);
	odp duzy = odp(-1);
	scanf("%d", &n);
	assert(n <= 100);
	for(int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		drogi.push_back(make_pair(a, b));
	}
	for(int i = 0; i < n - 1; ++i) {
		pii memo = drogi[i];
		for(int a = 1; a < n; ++a)
			for(int b = a + 1; b <= n; ++b) {
				drogi[i] = make_pair(a, b);
				int d = liczSrednice();
				if(d == -1) continue;
				if(d < maly.a) maly = odp(d, memo, drogi[i]);
				if(d > duzy.a) duzy = odp(d, memo, drogi[i]);
			}
		drogi[i] = memo;
	}
	maly.wypisz();
	duzy.wypisz();
	return 0;
}
