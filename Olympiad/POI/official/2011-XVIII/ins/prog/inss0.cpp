/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Inspekcja                                        *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1000000;

int n;

vector<int> kra[MAXN];

int poddrzewo[MAXN], najglebszy[MAXN], p[MAXN];
long long suma[MAXN];

int l;
int wiel[MAXN], najgl[MAXN];

void dfs(int u) {
	poddrzewo[u] = 1;
	najglebszy[u] = 0;
	for(int i=0; i<int(kra[u].size()); ++i) {
		if(kra[u][i] != p[u]) {
			p[kra[u][i]] = u;
			dfs(kra[u][i]);
			poddrzewo[u] += poddrzewo[kra[u][i]];
			najglebszy[u] = max(najglebszy[u], najglebszy[kra[u][i]] + 1);
			suma[u] += suma[kra[u][i]] + poddrzewo[kra[u][i]];
		}
	}
}

void odpowiedz(int u) {
	for(int i=0; i<n; ++i) {
		p[i] = -1;
		suma[i] = 0;
	}
	dfs(u);
	l = 0;
	for(int i=0; i<int(kra[u].size()); ++i) {
		wiel[l] = poddrzewo[kra[u][i]];
		najgl[l] = najglebszy[kra[u][i]];
		++l;
	}
	long long best = 2*suma[u];
	bool ok=true;
	for(int i=0; i<l; ++i) {
		if(2*wiel[i] > n) {
			best = -1;
			ok = false;
			break;
		}
		if(2*wiel[i] == n) {
			best = 2*suma[u] - najgl[i] - 1;
			ok = false;
			break;
		}
	}
	if(ok) {
		for(int i=0; i<l; ++i) {
			best = min(best, 2*suma[u] - najgl[i] - 1);
		}
	}
	printf("%lld\n", best);

}

int main() {
	scanf("%d", &n);
	for(int i=0; i<n-1; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		--u;
		--v;
		kra[u].push_back(v);
		kra[v].push_back(u);
	}
	for(int u=0; u<n; ++u) {
		odpowiedz(u);
	}
	return 0;
}
