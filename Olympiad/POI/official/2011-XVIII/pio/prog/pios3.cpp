/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Piorunochron                                     *
 *   Autor:             Juliusz Sompolski                                *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <cassert>
using namespace std;

#define MAXIMUM(a,b) ((a)>(b)?(a):(b))

#define MAXN 500000

/** Liczba budynkow */
int N;
/** Wysokosci budynkow */
int H[MAXN];
/** Posortowane wysokosci budynkow */
pair<int, int> HSort[MAXN];
bool cmp(const pair<int,int> &a, const pair<int,int> &b) {
	return a.first < b.first;
}

/* Liczenie odpowiedzi dla danego budynku */
int get_answer(int i) {
	int ret = 0;
	/* Maksymalny bonus do wysokosci piorunochronu dla tego budynku */
	int max_bonus = (int) MAXIMUM(ceil(sqrt(i)), ceil(sqrt(N-1-i)));
	/* Szuka najdluzszego piorunochronu od najwyzszego budynku */
	for(int j = N-1; j >= 0; j--) {
		/* Dalsze budynki sa za niskie zeby zmienic odpowiedz. */
		if(HSort[j].first-H[i]+max_bonus <= ret)
			break;
		int h = HSort[j].first-H[i] + (int) ceil(sqrt(abs(HSort[j].second-i)));
		ret = MAXIMUM(ret, h);
	}
	return ret;
}

int main() {
	/* Wczytanie danych */
	assert(scanf("%d", &N));
	for(int i = 0; i < N; i++)
		assert(scanf("%d", &H[i]));
	/* Preprocessing */
	for(int i = 0; i < N; i++) {
		HSort[i].first = H[i];
		HSort[i].second = i;
	}
	sort(HSort, HSort+N, cmp);
	/* Odpowiedzi */
	for(int i = 0; i < N; i++)
		printf("%d\n", get_answer(i));
}
