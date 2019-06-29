/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slonie (SLO)                                              *
 *   Plik:     slos1.cpp                                                 *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie nieefektywne O(n^2). Trzyma tablice jak na    *
 *             na wejsciu a nie jako permutacje.                         *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <algorithm>

#define REP(a,n) for (int a=0; a<(n); ++a)

using namespace std;

#define INF 1000000000

typedef long long LL;

///////////////////////////

#define MAXN 1000000

int wagi[MAXN];
int orig[MAXN]; // orig[i] = kto stal na pozycji i
int docel[MAXN]; // docel[i] = kto ma stac na pozycji i
bool vis[MAXN]; // slon i nalezy do juz zbadanego cyklu

int minw = INF; // minimalna waga

int main()
{
	int N;
	scanf("%d", &N);
	REP(a, N)
	{
		scanf("%d", &wagi[a]);
		minw = min(minw, wagi[a]);
	}
	REP(a, N)
	{
		scanf("%d", &orig[a]);
		--orig[a];
	}
	REP(a, N)
	{
		scanf("%d", &docel[a]);
		--docel[a];
	}
	LL wynik = 0;
	REP(pocz, N)
		if (!vis[pocz])
		{
			int minc = INF; // minimalna waga w cyklu
			LL suma = 0; // suma wag w cyklu
			int cur = pocz;
			int dl = 0; // dlugosc cyklu
			for (;;) 
			{
				minc = min(minc, wagi[cur]);
				suma += wagi[cur];
				REP(a, N) // przechodzenie do kolejnego elementu permutacji
					if (docel[a]==cur)
					{
						// nasz slon cur ma stac na pozycji a, patrzymy kto tam teraz jest
						cur = orig[a];
						break;
					}
				vis[cur] = true;
				++dl;
				if (cur==pocz)
					break;
			}
			wynik += min(suma+(dl-2)*(LL)minc, suma+minc+(dl+1)*(LL)minw);
		}
	printf("%Ld\n", wynik);
}
