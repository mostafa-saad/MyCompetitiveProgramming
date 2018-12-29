/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Piorunochron                                     *
 *   Autor:             Juliusz Sompolski                                *
 *   Zlozonosc czasowa: O(n * sqrt(n))                                   *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

#define MAXIMUM(a,b) ((a)>(b)?(a):(b))

#define MAXN 500000
#define SQRTN 1000

/** Liczba budynkow */
int N,sqrtN;
/** Wysokosci budynkow */
int H[MAXN];
/** Posortowane interesujace budynki */
int HMax;
vector<pair<int, int> > HSort;
bool cmp(const pair<int,int> &a, const pair<int,int> &b) {
	return a.first < b.first;
}

int srt[MAXN + 1];

/** Czy budynek o takiej wysokosci juz byl */
bool was[SQRTN];

int z = 0;

/* Liczenie odpowiedzi dla danego budynku */
int get_answer(int i) {
	int ret = 0;
	/* Maksymalny bonus do wysokosci piorunochronu dla tego budynku */
	int max_bonus = (int) MAXIMUM(ceil(sqrt(i)), ceil(sqrt(N-1-i)));
	/* Szuka najdluzszego piorunochronu od najwyzszego budynku */
	for(int j = HSort.size()-1; j >= 0; j--) {
		/* Dalsze budynki sa za niskie zeby zmienic odpowiedz. */
		if(HSort[j].first-H[i]+max_bonus <= ret)
			break;
		++z;
		int h = HSort[j].first-H[i] + srt[abs(HSort[j].second-i)];
		ret = MAXIMUM(ret, h);
	}
	return ret;
}

int main() {
	/* Wczytanie danych */
	assert(scanf("%d", &N));
	for(int i = 0; i < N; i++)
		assert(scanf("%d", &H[i]));
	/**
	 Preprocessing
	*/
	HMax = 0;
	for(int i = 0; i < N; i++)
		HMax = MAXIMUM(HMax, H[i]);
	sqrtN = (int) ceil(sqrt(N));
	for (int i = 0; i<= N; ++i)
		srt[i] = (int) ceil(sqrt(i));
	// od lewej do prawej.
	for(int i = 0; i < sqrtN; i++) was[i] = false;
	for(int i = 0; i < N; i++) {
		if(H[i] > HMax - sqrtN && was[HMax-H[i]] == false) {
			HSort.push_back(pair<int,int>(H[i],i));
			was[HMax-H[i]] = true;
		}
	}
	// od prawej do lewej.
	for(int i = 0; i < sqrtN; i++) was[i] = false;
	for(int i = N-1; i >= 0; i--) {
		if(H[i] > HMax - sqrtN && was[HMax-H[i]] == false) {
			HSort.push_back(pair<int,int>(H[i],i));
			was[HMax-H[i]] = true;
		}
	}
	
	sort(HSort.begin(), HSort.end(), cmp);
	/* Odpowiedzi */
	for(int i = 0; i < N; i++)
		printf("%d\n", get_answer(i));
}
