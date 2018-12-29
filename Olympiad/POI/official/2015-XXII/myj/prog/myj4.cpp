/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Myjnie                                             *
 *   Zlozonosc czasowa:    O(n^3 * m)                                         *
 *   Zlozonosc pamieciowa: O(n^3 + n^2 * m)                                   *
 *   Autor programu:       Marek Sommer                                       *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/


#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const int MAX_VALUE = 500 * 1000;

int n, m;
vector< pair<int, pair<int, int> > > przedzialy;

int ile_przedzialow[55][55][55];

ll dp[55][55][4005];
int ruch[55][55][4005];

void wylicz(int a, int b, int id)
{
	ll & wyn = dp[a][b][id];
	int & r = ruch[a][b][id];
	wyn = dp[a][b][id + 1];
	r = -1;
	for(int i = a; i <= b; i++)
	{
		ll new_wyn = dp[a][i - 1][id] + dp[i + 1][b][id] + (ll) ile_przedzialow[a][b][i] * przedzialy[id].first;
		if(new_wyn > wyn)
		{
			wyn = new_wyn;
			r = i;
		}
	}
}

int tab[55];

void odzyskaj(int a, int b, int id)
{
	const int & r = ruch[a][b][id];
	if(r == -1)
		odzyskaj(a, b, id + 1);
	else if(r > 0)
	{
		tab[r] = przedzialy[id].first;
		odzyskaj(a, r - 1, id);
		odzyskaj(r + 1, b, id);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		przedzialy.emplace_back(c, make_pair(a, b));
	}
	sort(przedzialy.begin(), przedzialy.end());
	for(int k = m - 1; k >= 0; k--)
	{
		const int & a = przedzialy[k].second.first;
		const int & b = przedzialy[k].second.second;
		for(int p = 1; p <= a; p++)
			for(int k = b; k <= n; k++)
				for(int s = a; s <= b; s++)
					ile_przedzialow[p][k][s]++;
		for(int d = 1; d <= n; d++)
			for(int ost = d; ost <= n; ost++)
				wylicz(ost - d + 1, ost, k);
	}
	for(int i = 1; i <= n; i++)
		tab[i] = MAX_VALUE;
	odzyskaj(1, n, 0);
	printf("%lld\n", dp[1][n][0]);
	for(int i = 1; i <= n; i++)
	{
		if(i != 1)
			printf(" ");
		printf("%d", tab[i]);
	}
	printf("\n");
	return 0;
}
