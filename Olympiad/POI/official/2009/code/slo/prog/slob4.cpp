/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slonie (SLO)                                              *
 *   Plik:     slob4.cpp                                                 *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie niepoprawne. Przestawia slonie na swoje       *
 *             miejsce poczawszy od najciezszego                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <utility>
#include <algorithm>

#define REP(a,n) for (int a=0; a<(n); ++a)

using namespace std;

#define INF 1000000000

typedef long long LL;

///////////////////////////

#define MAXN 1000000

int wagi[MAXN];
int gdzie_jest[MAXN]; // pozycja slonia i
int co_tu_jest[MAXN]; // nr slonia na pozycji i
int gdzie_ma_byc[MAXN]; // docelowa pozycja slonia i

pair<int, int> kolejnosc[MAXN]; // pary zawierajace wage i numer slonia, sortujemy ta tablice

int main()
{
	int N;
	scanf("%d", &N);
	REP(a, N)
	{
		scanf("%d", &wagi[a]);
		kolejnosc[a] = make_pair(wagi[a], a);
	}
	sort(kolejnosc, kolejnosc+N);
	REP(a, N)
	{
		scanf("%d", &co_tu_jest[a]);
		--co_tu_jest[a];
		gdzie_jest[co_tu_jest[a]] = a;
	}
	REP(a, N)
	{
		int nr;
		scanf("%d", &nr);
		--nr;
		gdzie_ma_byc[nr] = a;
	}
	LL wynik = 0;
	REP(a, N) 
	{
		int nr = kolejnosc[a].second; // nr slonia, ktorego chcemy ustawic na swojej pozycji
		if (gdzie_jest[nr]==gdzie_ma_byc[nr]) // juz jest na swojej pozycji
			continue;
		int nr2 = co_tu_jest[gdzie_ma_byc[nr]];
		swap(co_tu_jest[gdzie_jest[nr]], co_tu_jest[gdzie_ma_byc[nr]]);
		swap(gdzie_jest[nr], gdzie_jest[nr2]);
		wynik += wagi[nr]+wagi[nr2];
	}
	printf("%Ld\n", wynik);
}
