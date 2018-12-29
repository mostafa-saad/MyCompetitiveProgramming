/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Inspekcja                                        *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe - sprytniejsze              *
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

// Zmienna oznaczajaca aktualnie dfsowany wierzcholek (funkcja dfs2), potrzebna po to,
// by nie wchodzic do niego (dfs2 idzie jedynie po poddrzewach, nie odwiedza samego
//korzenia, bo i po co).
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
	// Budujemy graf.
	for(int i=0; i<n-1; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		--u;
		--v;
		kra[u].push_back(v);
		kra[v].push_back(u);
	}
	// Dfs liczacy jedynie wielkosci poddrzew.
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
		if(2*mx<=n) { // Jezeli istnieje przechadzka...
			akt = u;
			// Tu wejdziemy co najwyzej dwa razy :)
			for(int v=0; v<n; ++v) p2[v] = -1;
			suma=0;
			int najgl=0;
			for(int i=0; i<int(kra[u].size()); ++i) { // Dla kazdego poddrzewa uruchamiamy dfs, ktory liczy odleglosci.
				if(kra[u][i]!=p[u]) {
					int cur=dfs2(kra[u][i], 1);
					if(2*mx < n || poddrzewo[kra[u][i]]==mx) {
            // (*) Uaktualniamy zmienna najgl jedynie wtedy, gdy mozemy skonczyc
            // w danym poddrzewie. (Odsylam do opracowania.)
						najgl=max(najgl,cur+1);
					}
				}
			}
			if(p[u]!=-1) {
				int cur=dfs2(p[u], 1);
				if(2*mx < n || n-poddrzewo[u]==mx) { // (*) 
					najgl=max(najgl,cur+1);
				}
			}
			printf("%lld\n", 2*suma - najgl); // Wynik zgodnie z opracowaniem.
		} else printf("-1\n");
	}
	return 0;
}
