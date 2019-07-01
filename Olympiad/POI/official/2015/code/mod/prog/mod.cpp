/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Modernizacja autostrady                            *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Autor programu:       Kamil Debowski                                     *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/


#include<cstdio>
#include<algorithm>
#include<vector>
#include<assert.h>
using namespace std;
typedef pair<int, int> pii;
const int nax = 5e5 + 5;

vector<int> w[nax];
int n;

int ojc[nax],
	pod[nax], // najdluzsza sciezka w dol (innymi slowy: wysokosc poddrzewa)
	sre_pod[nax], // srednica poddrzewa
	nad[nax], // najdluzsza sciezka nie w dol
	sre_nad[nax]; // srednica drzewa po wywaleniu tego poddrzewa

void dfs(int a) {
	pod[a] = 0;
	sre_pod[a] = 0;
	int one = -nax, two = -nax;
	for(int i = 0; i < (int) w[a].size(); ++i) {
		int b = w[a][i];
		if(ojc[a] == b) continue;
		ojc[b] = a;
		dfs(b);
		sre_pod[a] = max(sre_pod[a], sre_pod[b]);
		if(pod[b] + 1 > pod[a]) pod[a] = pod[b] + 1;
		if(pod[b] > one) {
			two = one;
			one = pod[b];
		}
		else if(pod[b] > two) {
			two = pod[b];
		}
	}
	sre_pod[a] = max(sre_pod[a], max(pod[a], two + one + 2));
}

void dfs2(int a) {
	int t[3];
	for(int i = 0; i < 3; ++i) t[i] = -nax;
	int one = 0, two = 0;
	for(int i = 0; i < (int) w[a].size(); ++i) {
		int b = w[a][i];
		if(ojc[a] != b) {
			ojc[b] = a;
			for(int j = 0; j < 3; ++j) if(t[j] < pod[b]) {
				for(int k = 2; k > j; --k) t[k] = t[k-1];
				t[j] = pod[b];
				break;
			}
			if(sre_pod[b] > one) {
				two = one;
				one = sre_pod[b];
			}
			else if(sre_pod[b] > two) {
				two = sre_pod[b];
			}
		}
	}
	for(int i = 0; i < (int) w[a].size(); ++i) {
		int b = w[a][i];
		if(ojc[a] != b) {
			nad[b] = nad[a] + 1;
			if(t[0] == pod[b]) nad[b] = max(nad[b], t[1] + 2);
			else nad[b] = max(nad[b], t[0] + 2);
			
			sre_nad[b] = max(sre_nad[a], nad[a]);
			if(t[0] == pod[b]) sre_nad[b] = max(sre_nad[b], t[1] + t[2] + 2);
			else if(t[1] == pod[b]) sre_nad[b] = max(sre_nad[b], t[0] + t[2] + 2);
			else sre_nad[b] = max(sre_nad[b], t[0] + t[1] + 2);
			
			if(t[0] == pod[b]) sre_nad[b] = max(sre_nad[b], nad[a] + t[1] + 1);
			else sre_nad[b] = max(sre_nad[b], nad[a] + t[0] + 1);
			
			if(sre_pod[b] == one) sre_nad[b] = max(sre_nad[b], two);
			else sre_nad[b] = max(sre_nad[b], one);
		}
	}
	
	for(int i = 0; i < (int) w[a].size(); ++i) {
		int b = w[a][i];
		if(ojc[a] != b)
			dfs2(b);
	}
}

int ZAKAZ;
int h[nax], d[nax];
pii krance;
int srednica;

void dfs3(int a) {
	int one = a, two = a;
	for(int i = 0; i < (int) w[a].size(); ++i) {
		int b = w[a][i];
		if(ojc[a] != b && b != ZAKAZ) {
			ojc[b] = a;
			h[b] = h[a] + 1;
			dfs3(b);
			if(h[d[b]] > h[one]) {
				two = one;
				one = d[b];
			}
			else if(h[d[b]] > h[two]) {
				two = d[b];
			}
		}
	}
	d[a] = one;
	if(h[one] + h[two] - 2 * h[a] > srednica) {
		srednica = h[one] + h[two] - 2 * h[a];
		krance = make_pair(one, two);
	}
}

int srodek(pii p) {
	int a = p.first, b = p.second;
	if(h[a] < h[b]) swap(a, b);
	for(int i = 0; i < srednica / 2; ++i)
		a = ojc[a];
	return a;
}

void przetnij(pii wywal, bool czyDuzy) {
	for(int i = 1; i <= n; ++i) ojc[i] = h[i] = 0;
	ZAKAZ = wywal.first;
	srednica = -1;
	dfs3(wywal.second);
	int sr = srodek(krance);
	int skraj = krance.first;
	for(int i = 1; i <= n; ++i) ojc[i] = h[i] = 0;
	ZAKAZ = wywal.second;
	srednica = -1;
	dfs3(wywal.first);
	int sr2 = srodek(krance);
	int skraj2 = krance.first;
	if(czyDuzy) printf("%d %d\n", skraj, skraj2);
	else printf("%d %d\n", sr, sr2);
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		w[a].push_back(b);
		w[b].push_back(a);
	}
	dfs(1);
	sre_nad[1] = -nax;
	nad[1] = 0;
	dfs2(1);
	pii maly = make_pair(nax, 0), duzy = make_pair(-1, 0);
	for(int i = 2; i <= n; ++i) {
		int a = sre_pod[i];
		int b = sre_nad[i];
		if(a + b + 1 > duzy.first) duzy = make_pair(a + b + 1, i);
		int pom = max((a+1)/2 + (b+1)/2 + 1, max(a, b));
		if(pom < maly.first) maly = make_pair(pom, i);
	}
	assert(maly.second != 0);
	assert(duzy.second != 0);
	printf("%d ", maly.first);
	printf("%d %d ", maly.second, ojc[maly.second]);
	int ojciec_duzego = ojc[duzy.second];
	przetnij(make_pair(maly.second, ojc[maly.second]), false);
	printf("%d ", duzy.first);
	printf("%d %d ", duzy.second, ojciec_duzego);
	przetnij(make_pair(duzy.second, ojciec_duzego), true);
	return 0;
}
