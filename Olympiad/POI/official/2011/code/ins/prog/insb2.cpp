/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Inspekcja                                        *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Zaklada, ze trasa zawsze konczy sie w najdalszym *
 *                      wierzcholku od poczatku.                         *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1000000;

int n;

vector<int> kra[MAXN];

int poddrzewo[MAXN], najglebszy_dol[MAXN], najglebszy_gora[MAXN], p[MAXN];
long long suma[MAXN];

void dfs(int u) {
	poddrzewo[u] = 1;
	najglebszy_dol[u] = 0;
	for(int i=0; i<int(kra[u].size()); ++i) {
		if(kra[u][i] != p[u]) {
			p[kra[u][i]] = u;
			dfs(kra[u][i]);
			poddrzewo[u] += poddrzewo[kra[u][i]];
			najglebszy_dol[u] = max(najglebszy_dol[u], najglebszy_dol[kra[u][i]] + 1);
			suma[u] += suma[kra[u][i]] + poddrzewo[kra[u][i]];
		}
	}
}

void dfs2(int u) {
	int mx1 = -1, mx2 = -1;
	for(int i=0; i<int(kra[u].size()); ++i) {
		if(kra[u][i] != p[u]) {
			if(najglebszy_dol[kra[u][i]] > mx1) {
				mx2 = mx1;
				mx1 = najglebszy_dol[kra[u][i]];
			} else if(najglebszy_dol[kra[u][i]] > mx2) {
				mx2 = najglebszy_dol[kra[u][i]];
			}
		}
	}
	for(int i=0; i<int(kra[u].size()); ++i) {
		if(kra[u][i] != p[u]) {
			suma[kra[u][i]] = suma[u] - 2*poddrzewo[kra[u][i]] + n;
			int best = mx1;
			if(najglebszy_dol[kra[u][i]] == mx1) {
				best = mx2;
			}
			najglebszy_gora[kra[u][i]] = max(najglebszy_gora[u]+1, max(1, best+2));
			dfs2(kra[u][i]);
		}
	}
}

int l;
int wiel[MAXN], najgl[MAXN];

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
	p[0] = -1;
	dfs(0);
	dfs2(0);
	/* for(int u=0; u<n; ++u) {
		printf("poddrzewo[%d] = %d\n",u+1,poddrzewo[u]);
		printf("najglebszy_dol[%d] = %d\n",u+1,najglebszy_dol[u]);
		printf("najglebszy_gora[%d] = %d\n",u+1,najglebszy_gora[u]);
		printf("suma_odleglosci[%d] = %lld\n",u+1,suma[u]);
	} */
	for(int u=0; u<n; ++u) {
		l = 0;
		for(int i=0; i<int(kra[u].size()); ++i) {
			if(kra[u][i] != p[u]) {
				wiel[l] = poddrzewo[kra[u][i]];
				najgl[l] = najglebszy_dol[kra[u][i]];
				++l;
			} else {
				wiel[l] = n - poddrzewo[u];
				najgl[l] = najglebszy_gora[u] - 1;
				++l;
			}
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
				break;
			}
		}
		if(ok) {
			for(int i=0; i<l; ++i) {
				best = min(best, 2*suma[u] - najgl[i] - 1);
			}
		}
		printf("%lld\n",best);
	}
	return 0;
}
