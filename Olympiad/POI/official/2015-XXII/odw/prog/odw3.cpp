/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Odwiedziny                                         *
 *   Zlozonosc czasowa:    O(n*t + q*t*logn), gdzie t = 255 (ponad sqrt(n))   *
 *   Autor programu:       Marek Sommer                                       *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50000;
const int pierw = 255;
const int logar = 16;

int n;
int c[MAXN + 5];
vector<int> graf[MAXN + 5];
int ojc[pierw + 1][MAXN + 5];
int pre[MAXN + 5]; int pre_licznik = 0;
int pos[MAXN + 5];
int g[MAXN + 5]; // głębokość wierzchołka
int skok[logar + 1][MAXN + 5];
int dp[pierw + 1][MAXN + 5];

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

int licz_mniej_niz_pierw(int a, int b, int k)
{
	int wyn = dp[k][a] + dp[k][b];
	int l = lca(a, b);
	int ra = g[a] % k;
	int rb = g[b] % k;
	for(int i = l; i; i = ojc[1][i])
	{
		if(g[i] % k == ra)
		{
			wyn -= dp[k][i];
			break;
		}
	}
	for(int i = l; i; i = ojc[1][i])
	{
		if(g[i] % k == rb)
		{
			wyn -= dp[k][i];
			break;
		}
	}
	if(g[l] % k == ra && ra == rb)
		wyn += c[l];
	return wyn;
}

int licz_wiecej_niz_pierw(int a, int b, int k)
{
	const int old_a = a;
	const int l = lca(a, b);
	int wyn = 0;
	while(!przodek(a, b))
	{
		wyn += c[a];
		a = skocz_o(a, k);
	}
	while(!przodek(b, old_a))
	{
		wyn += c[b];
		b = skocz_o(b, k);
	}
	if(a == b && a == l)
		wyn += c[a];
	return wyn;
}

void dfs(int w, int o)
{
	g[w] = g[o] + 1;
	pre[w] = ++pre_licznik;
	skok[0][w] = o;
	ojc[0][w] = w;
	for(int i = 1; i <= pierw; i++)
	{
		ojc[i][w] = ojc[i - 1][o];
		dp[i][w] = dp[i][ojc[i][w]] + c[w];
	}
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
	for(int i = 0; i <= pierw; i++)
	{
		ojc[i][0] = 0;
		dp[i][0] = 0;
	}
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
		printf("%d\n",
			(k <= pierw)
			? licz_mniej_niz_pierw(t[i], t[i + 1], k)
			: licz_wiecej_niz_pierw(t[i], t[i + 1], k)
		);
	}
	return 0;
}
