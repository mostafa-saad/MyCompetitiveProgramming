/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Modernizacja autostrady                            *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Autor programu:       Marek Sommer                                       *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/


#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

const int infty = 1e9 + 5;

int najwieksze[3] = {-1, 0, 0};
int najmniejsze[3] = {infty, 0, 0};

void dodaj_wynik(int x, int a, int b)
{
	if(x < najmniejsze[0])
		najmniejsze[0] = x, najmniejsze[1] = a, najmniejsze[2] = b;
	if(x > najwieksze[0])
		najwieksze[0] = x, najwieksze[1] = a, najwieksze[2] = b;
}

int n;

vector<int> graf[500005];

int odl[500005];

int wyka = -1, wykb = -1;

int najdalszy(int w, int o = -1)
{
	if(wykb == w)
		swap(wyka, wykb);
	int naj = w;
	for(int i : graf[w])
	{
		if(i == o)
			continue;
		if(wyka == w && wykb == i)
			continue;
		odl[i] = odl[w] + 1;
		int dp = najdalszy(i, w);
		if(odl[dp] > odl[naj])
			naj = dp;
	}
	return naj;
}

int wys[500005];
int m; // długość najdłuższej ścieżki
int sciezka[500005];

bool szukajb(int w, int o, int b)
{
	sciezka[++m] = w;
	if(w == b)
		return true;
	for(int i : graf[w])
	{
		if(i == o)
			continue;
		if(szukajb(i, w, b))
			return true;
	}
	m--;
	return false;
}

void dawaj_najkrotsza(int d, int a, int b)
{
	printf("%d %d %d", d, a, b);
	wyka = a;
	wykb = b;
	a = najdalszy(a);
	const int na = najdalszy(a);
	const int lew = odl[na] - odl[a];
	b = najdalszy(b);
	const int nb = najdalszy(b);
	const int pra = odl[nb] - odl[b];
	assert(max(max(lew, pra), (lew + 1) / 2 + (pra + 1) / 2 + 1) == d);
	m = 0;
	szukajb(a, -1, na);
	int sa = sciezka[(m + 1) / 2];
	m = 0;
	szukajb(b, -1, nb);
	int sb = sciezka[(m + 1) / 2];
	printf(" %d %d\n", sa, sb);
}

void dawaj_najdluzsza(int d, int a, int b)
{
	printf("%d %d %d", d, a, b);
	wyka = a;
	wykb = b;
	a = najdalszy(a);
	const int na = najdalszy(a);
	const int lew = odl[na] - odl[a];
	b = najdalszy(b);
	const int nb = najdalszy(b);
	const int pra = odl[nb] - odl[b];
	assert(lew + 1 + pra == d);
	printf(" %d %d\n", a, b);
}

bool nasciezce[500005];

int wysokosc(int w, int o)
{
	int wyn = 0;
	for(int i : graf[w])
		if(i != o && !nasciezce[i])
			wyn = max(wyn, wysokosc(i, w) + 1);
	return wyn;
}

int pref[500005];
int suf[500005];

int dp[2][500005];
void dfs_licz_najdluzsza_sciezke(int w, int o)
{
	int najkki = 0, drugki = 0;
	for(int i : graf[w])
	{
		if(i == o)
			continue;
		dfs_licz_najdluzsza_sciezke(i, w);
		int kik = dp[0][i] + 1;
		dp[0][w] = max(dp[0][w], kik);
		dp[1][w] = max(dp[1][w], dp[1][i]);
		if(najkki < kik)
			swap(najkki, kik);
		if(drugki < kik)
			swap(drugki, kik);
	}
	dp[1][w] = max(dp[1][w], najkki + drugki);
}

void kandydaci()
{
	for(int i = 2; i <= m; i++)
	{
		const int & lew = pref[i - 1];
		const int & pra = suf[i];
		// do maksimum
		dodaj_wynik(lew + 1 + pra, sciezka[i - 1], sciezka[i]);
		// do minimum
		dodaj_wynik(max(max(lew, pra), (lew + 1) / 2 + 1 + (pra + 1) / 2), sciezka[i - 1], sciezka[i]);
	}
	// do maksimum
	for(int i = 1; i <= m; i++)
	{
		for(int j : graf[sciezka[i]])
		{
			if(nasciezce[j])
				continue;
			dfs_licz_najdluzsza_sciezke(j, sciezka[i]);
			dodaj_wynik(m + dp[1][j], sciezka[i], j);
		}
	}
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		graf[a].emplace_back(b);
		graf[b].emplace_back(a);
	}
	int a = najdalszy(1);
	int b = najdalszy(a);
	szukajb(a, -1, b);
	for(int i = 1; i <= m; i++)
		nasciezce[sciezka[i]] = true;
	for(int i = 1; i <= m; i++)
		wys[i] = wysokosc(sciezka[i], -1);
	for(int i = 1; i <= m; i++)
		pref[i] = max(pref[i - 1], wys[i] + i - 1);
	for(int i = m; i >= 1; i--)
		suf[i] = max(suf[i + 1], wys[i] + m - i);
	
	kandydaci();
	
	assert(najmniejsze[0] != -1);
	assert(najwieksze[0] != infty);

	dawaj_najkrotsza(najmniejsze[0], najmniejsze[1], najmniejsze[2]);
	dawaj_najdluzsza(najwieksze[0], najwieksze[1], najwieksze[2]);
	return 0;
}
