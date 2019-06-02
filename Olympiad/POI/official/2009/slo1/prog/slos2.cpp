/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slonie (SLO)                                              *
 *   Plik:     slo3.cpp                                                  *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie wykladnicze. Rozpatruje wszystkie zamiany     *
 *             poczawszy od najtanszych.                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

#define REP(a,n) for (int a=0; a<(n); ++a)

using namespace std;

#define INF 1000000000

typedef long long LL;
typedef vector<int> vi;

///////////////////////////

struct stan {
	LL koszt, szac;
	vi perm;
	stan(LL koszt, LL szac, const vi &perm) : koszt(koszt), szac(szac), perm(perm) {}
};
bool operator<(const stan &s1, const stan &s2)
{
	return s1.koszt+s1.szac>s2.koszt+s2.szac;
}


map<vi, LL> dodane;
priority_queue<stan> Q;

void wstaw(LL koszt, LL szac, const vi &perm)
// koszt to dotychczasowy koszt doprowadzenia do takiego stanu
// szac to szacowany z dolu koszt do zakonczenia sortowania 
//       (szacujemy przez sume wag sloni, ktore nie sa na swoich miejscach)
{
	if (szac==0)
	{
		printf("%Ld\n", koszt);
		exit(0);
	}
	LL &cur = dodane[perm];
	if (cur && cur<=koszt+szac) // juz byl i byl mniejszy
		return;
	cur = koszt+szac;
	Q.push(stan(koszt, szac, perm));
}

#define MAXN 1000000

int wagi[MAXN];
int orig[MAXN]; // orig[i] = kto stal na pozycji i
vi perm_pocz; // slon i ma wyladowac na pozycji slonia perm[i]

int main()
{
	int N;
	scanf("%d", &N);
	REP(a, N)
		scanf("%d", &wagi[a]);
	REP(a, N)
	{
		scanf("%d", &orig[a]);
		--orig[a];
	}
	perm_pocz.resize(N);
	REP(a, N)
	{
		int nr;
		scanf("%d", &nr);
		--nr;
		perm_pocz[nr] = orig[a];
	}
	LL szac = 0;
	REP(a, N)
		if (perm_pocz[a]!=a)
			szac += wagi[a];
	wstaw(0, szac, perm_pocz);
	for (;;)
	{
		stan stanp = Q.top();
		Q.pop();
		REP(a, N)
			REP(b, a)
			{
				LL koszt = stanp.koszt+wagi[a]+wagi[b];
				szac = stanp.szac;
				if (stanp.perm[a]!=a)
					szac -= wagi[a];
				if (stanp.perm[b]!=b)
					szac -= wagi[b];
				swap(stanp.perm[a], stanp.perm[b]);
				if (stanp.perm[a]!=a)
					szac += wagi[a];
				if (stanp.perm[b]!=b)
					szac += wagi[b];
				wstaw(koszt, szac, stanp.perm);
				swap(stanp.perm[a], stanp.perm[b]);
			}
	}
}
