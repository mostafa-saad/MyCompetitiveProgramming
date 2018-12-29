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

#define MAXIMUM(a,b) ((a)>(b)?(a):(b))

#define MAXN 500000

/** Liczba budynkow */
int N;
/** Wysokosci budynkow */
int H[MAXN];

/** Liczenie odpowiedzi dla danego budynku */
int get_answer(int i) {
	int ret = 0;
	for(int j = 0; j < N; j++) {
		int h = H[j]-H[i] + (int) ceil(sqrt(abs(j-i)));
		ret = MAXIMUM(ret, h);
	}
	return ret;
}

int main() {
	/* Wczytanie danych */
	scanf("%d", &N);
	for(int i = 0; i < N; i++)
		scanf("%d", &H[i]);
	/* Odpowiedzi */
	for(int i = 0; i < N; i++)
		printf("%d\n", get_answer(i));
}
