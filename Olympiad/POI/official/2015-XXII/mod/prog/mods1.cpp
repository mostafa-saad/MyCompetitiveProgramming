/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Modernizacja autostrady                            *
 *   Zlozonosc czasowa:    O(n^2)                                             *
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
int dal[nax];
int h[nax];
int ojc[nax];

int srednica;
pii krance;

void dfs(int a) {
	int one = a, two = a;
	dal[a] = a;
	for(int i = 0; i < (int) w[a].size(); ++i) {
		int b = w[a][i];
		if(ojc[a] != b) {
			ojc[b] = a;
			h[b] = h[a] + 1;
			dfs(b);
			if(h[dal[b]] > h[dal[a]])
				dal[a] = dal[b];
			if(h[one] < h[dal[b]]) {
				two = one;
				one = dal[b];
			}
			else if(h[two] < h[dal[b]]) {
				two = dal[b];
			}
		}
	}
	if(srednica < h[one] + h[two] - 2 * h[a]) {
		srednica = h[one] + h[two] - 2 * h[a];
		krance = make_pair(one, two);
	}
}

pair<int, pii > f(int root) {
	srednica = -1;
	h[root] = ojc[root] = 0;
	dfs(root);
	int a = krance.first, b = krance.second;
	if(h[a] < h[b]) swap(a, b);
	for(int i = 0; i < srednica / 2; ++i) a = ojc[a];
	return make_pair(srednica, make_pair(a, b));
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
		printf("%d %d %d %d %d", a, bylo.first, bylo.second, bedzie.first, bedzie.second);
	}
};

int main() {
	odp maly = odp(nax);
	odp duzy = odp(-1);
	scanf("%d", &n);
	assert(n <= 100 * 1000);
	for(int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		drogi.push_back(make_pair(a, b));
	}
	for(int wywal = 0; wywal < n - 1; ++wywal) {
		for(int i = 1; i <= n; ++i) w[i].clear();
		for(int i = 0; i < n - 1; ++i) if(i != wywal) {
			int a = drogi[i].first, b = drogi[i].second;
			w[a].push_back(b);
			w[b].push_back(a);
		}
		int a = drogi[wywal].first, b = drogi[wywal].second;
		pair<int, pii > p1 = f(a);
		pair<int, pii > p2 = f(b);
		int s1 = p1.first, s2 = p2.first;
		
		int pom = max(s1, max(s2, (s1+1)/2 + (s2+1)/2 + 1));
		if(pom < maly.a) maly = odp(pom, drogi[wywal], make_pair(p1.second.first, p2.second.first));
		
		if(s1 + s2 + 1 > duzy.a) duzy = odp(s1+s2+1, drogi[wywal], make_pair(p1.second.second, p2.second.second));
	}
	maly.wypisz();
	puts("");
	duzy.wypisz();
	return 0;
}
