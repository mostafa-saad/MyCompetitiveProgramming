/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Odwiedziny                                         *
 *   Zlozonosc czasowa:    O(n*sqrt(n)*logn)                                  *
 *   Autor programu:       Marek Sommer                                       *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/


#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50000;
const int pierw = 230;
const int logar = 16;

int n;
int c[MAXN + 5];
vector<int> graf[MAXN + 5];
int pre[MAXN + 5]; int pre_licznik = 0;
int pos[MAXN + 5];
int g[MAXN + 5]; // głębokość wierzchołka
int skok[logar + 1][MAXN + 5];

int skocz_o(int w, int ile)
{
	for(int i = 0; ile; i++, ile /= 2)
		if(ile % 2 == 1)
			w = skok[i][w];
	return w;
}

bool przodek(int a, int b) // czy a jest przodkiem b?
{
	return pre[a] <= pre[b] && pre[b] <= pos[a];
}

int lca(int a, int b)
{
	if(przodek(a, b))
		return a;
	if(przodek(b, a))
		return b;
	for(int i = logar; i >= 0; i--)
		if(!przodek(skok[i][a], b))
			a = skok[i][a];
	return skok[0][a];
}

map<int, int> dp[MAXN + 5];

int get_dp(int w, int k)
{
	auto it = dp[w].find(k);
	if(it != dp[w].end())
		return it->second;
	const int gora = skocz_o(w, k);
	if(gora == w)
		return dp[w][k] = c[w];
	return dp[w][k] = c[w] + get_dp(gora, k);
}

int licz(int a, int b, int k)
{
	const int l = lca(a, b);
	int skocz_a = ((g[a] - g[l]) % k + k) % k;
	if(skocz_a == 0)
		skocz_a = k;
	int skocz_b = ((g[b] - g[l]) % k + k) % k;
	if(skocz_b == 0)
		skocz_b = k;
	return get_dp(a, k)
		+ get_dp(b, k)
		- get_dp(skocz_o(l, skocz_a), k)
		- get_dp(skocz_o(l, skocz_b), k)
		- (((g[l] % k == g[a] % k) && (g[l] % k == g[b] % k)) ? c[l] : 0);
}

void dfs(int w, int o)
{
	g[w] = g[o] + 1;
	pre[w] = ++pre_licznik;
	skok[0][w] = o;
	for(int i : graf[w])
		if(i != o)
			dfs(i, w);
	pos[w] = pre_licznik;
}

int t[MAXN + 5];

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", c + i);
	for(int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		graf[a].emplace_back(b);
		graf[b].emplace_back(a);
	}
	g[0] = -1;
	for(int i = 0; i <= logar; i++)
		skok[i][0] = 0;
	dfs(1, 0);
	pos[0] = pre_licznik;
	for(int i = 1; i <= logar; i++)
		for(int j = 1; j <= n; j++)
			skok[i][j] = skok[i - 1][skok[i - 1][j]];
	for(int i = 1; i <= n; i++)
		scanf("%d", t + i);
	for(int i = 1; i < n; i++)
	{
		int k;
		scanf("%d", &k);
		printf("%d\n", licz(t[i], t[i + 1], k));
	}
	return 0;
}
