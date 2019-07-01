/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Piorunochron                                     *
 *   Autor:             Juliusz Sompolski                                *
 *   Zlozonosc czasowa: O(n * sqrt(n))                                   *
 *          pamieciowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cassert>

#define MAXIMUM(a,b) ((a)>(b)?(a):(b))

#define MAXN 100000
#define LOGN 22
#define SQRTN 820

/** Liczba budynkow */
int N;
/** Wysokosci budynkow */
int H[MAXN];

/** Kwadraty liczb naturalnych */
int SQ[SQRTN];
/** Oblicza kwadraty liczb naturalnych */
void calc_SQ() {
	for(int i = 1; i < SQRTN; i++) {
		SQ[i] = i*i;
	}
}

/* Spamietywanie maksimow na przedzialach jako slownik podslow bazowych.
 */

/** MAX[k][j] - maksimum z tablicy H na przedziale [j, j+2^k) */
int MAX[LOGN][MAXN];

/** Oblicza tablice MAX na podstawie tablicy H */
void calc_MAX() {
	for(int i = 0; i < N; i++) {
		MAX[0][i] = H[i];
	}
	for(int k = 1, p = 1; 2*p <= N; k++, p*=2) {
		for(int j = 0; j < N; j++) {
			MAX[k][j] = MAX[k-1][j];
			if(j + p < N)
				MAX[k][j] = MAXIMUM(MAX[k][j], MAX[k-1][j+p]);
		}
	}
}

/** Zwraca w czasie O(1) maksimum z tablicy H na przedziale [a,b)
    * - tak naprawde to dziala w czasie log(log(b-a)), ale dla int jest to ogr przez stala.
	* wstawka assemblerowa mozna by to zrobic komenda bsr
 */
int get_max(int a, int b) {
	if(a < 0) a = 0;
	if(b >= N) b = N;
	int length = b-a, k = 31;
	if ((length & 0xFFFF0000) == 0) { k -= 16; length <<= 16; }
	if ((length & 0xFF000000) == 0) { k -= 8; length <<= 8; }
	if ((length & 0xF0000000) == 0) { k -= 4; length <<= 4; }
	if ((length & 0xC0000000) == 0) { k -= 2; length <<= 2; }
	if ((length & 0x80000000) == 0) { k -= 1; length <<= 1; }
	/* k - najwieksze k, ze 2^k <= (b-a) */
	
	return MAXIMUM(MAX[k][a], MAX[k][b-(1<<k)]);
}

/* Liczenie odpowiedzi dla danego budynku */
int get_answer(int i) {
	int ret = 0;
	/*
	 * k >= H[j] -H[i] + bonus
	 * bonus+1 - bonus do wysokosci piorunochrona, wynikajacy ze sqrt(|i-j|)
	 * maxH - max(H[j]) na przedziale o danym bonusie.
	 */
	// w prawo
	for(int bonus = 0; i + SQ[bonus] + 1 < N; bonus++) {
		int maxH = get_max(i+SQ[bonus]+1, i+SQ[bonus+1]+1);
		ret = MAXIMUM(ret, maxH-H[i]+bonus+1);
	}
	// w lewo
	for(int bonus = 0; i - SQ[bonus] - 1 >= 0; bonus++) {
		int maxH = get_max(i-SQ[bonus+1], i-SQ[bonus]);
		ret = MAXIMUM(ret, maxH-H[i]+bonus+1);
	}
	return ret;
}

int main() {
	/* Wczytanie danych */
	assert(scanf("%d", &N));
	for(int i = 0; i < N; i++)
		assert(scanf("%d", &H[i]));
	/* Preprocessing */
	calc_SQ();
	calc_MAX();
	/* Odpowiedzi */
	for(int i = 0; i < N; i++)
		printf("%d\n", get_answer(i));
}
