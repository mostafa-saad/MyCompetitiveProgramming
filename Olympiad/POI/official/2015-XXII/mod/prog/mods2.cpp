/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Modernizacja autostrady                            *
 *   Zlozonosc czasowa:    O(n^4)                                             *
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
int pod[nax];

int R;
void dfs(int a) {
	vis[a] = true;
	int raz = -1, dwa = -1;
	pod[a] = 0;
	for(int i = 0; i < (int) w[a].size(); ++i) {
		int b = w[a][i];
		if(vis[b]) continue;
		dfs(b);
		pod[a] = max(pod[a], pod[b] + 1);
		if(pod[b] > raz) {
			dwa = raz;
			raz = pod[b];
		}
		else if(pod[b] > dwa) dwa = pod[b];
	}
	R = max(R, raz + dwa + 2);
}

int liczSrednice() {
	for(int i = 1; i <= n; ++i) w[i].clear();
	R = 0;
	for(int i = 0; i < n - 1; ++i) {
		int a = drogi[i].first, b = drogi[i].second;
		w[a].push_back(b);
		w[b].push_back(a);
	}
	for(int i = 1; i <= n; ++i) vis[i] = false;
	dfs(1);
	for(int i = 1; i <= n; ++i) if(!vis[i]) return -1;
	return max(R, pod[1]);
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
	assert(n <= 500);
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
