/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Inspekcja                                        *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Zaklada, ze tylko jeden wynik moze nie byc -1    *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1000000;

int n;

vector<int> kra[MAXN];

int poddrzewo[MAXN], p[MAXN], p2[MAXN];
long long suma;

int akt = -1;

int dfs2(int u,int gleb) {
	int res=0;
	for(int i=0; i<int(kra[u].size()); ++i) {
		if(kra[u][i]!=p2[u] && kra[u][i] != akt) {
			p2[kra[u][i]]=u;
			int cur=dfs2(kra[u][i], gleb+1);
			res = max(res, cur+1);
		}
	}
	suma += gleb;
	return res;
}

void dfs(int u) {
	poddrzewo[u] = 1;
	for(int i=0; i<int(kra[u].size()); ++i) {
		if(kra[u][i] != p[u]) {
			p[kra[u][i]] = u;
			dfs(kra[u][i]);
			poddrzewo[u] += poddrzewo[kra[u][i]];
		}
	}
}

int res[MAXN];		
		
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
	for(int u=0; u<n; ++u) {
		int mx = -1;
		for(int i=0; i<int(kra[u].size()); ++i) {
			if(kra[u][i]!=p[u]) {
				mx = max(mx, poddrzewo[kra[u][i]]);
			}
		}
		mx = max(mx, n-poddrzewo[u]);
		if(2*mx<=n) {
			akt = u;
			// tu wejdziemy co najwyzej dwa razy :)
			for(int v=0; v<n; ++v) p2[v] = -1;
			suma=0;
			int najgl=0;
			for(int i=0; i<int(kra[u].size()); ++i) {
				if(kra[u][i]!=p[u]) {
					int cur=dfs2(kra[u][i], 1);
					if(2*mx < n || poddrzewo[kra[u][i]]==mx) {
						najgl=max(najgl,cur+1);
					}
				}
			}
			if(p[u]!=-1) {
				int cur=dfs2(p[u], 1);
				if(2*mx < n || n-poddrzewo[u]==mx) {
					najgl=max(najgl,cur+1);
				}
			}
//			printf("suma = %lld\n",suma);
			printf("%lld\n", 2*suma - najgl);
			for(int v=u+1; v<n; ++v) printf("-1\n");
			break;
		} else printf("-1\n");
	}
	return 0;
}
