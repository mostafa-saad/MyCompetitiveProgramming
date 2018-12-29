/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Piorunochron                                     *
 *   Autor:             Juliusz Sompolski                                *
 *   Zlozonosc czasowa: O(n * sqrt(n) * lg(n))                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <cassert>

#define MAXIMUM(a,b) ((a)>(b)?(a):(b))

#define MAXN 500000
#define SQRTN 800

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

/** MAX[j] - drzewo przedzialowe; maksimum z tablicy H na przedziale [j*2^k, (j+1)*2^k) */
int MAX[4*MAXN];
int START;
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)

/** Oblicza tablice MAX na podstawie tablicy H */
void calc_MAX() {
	START = 1;
	while(START < N)
		START *= 2;
	START--;
	for(int i = 0; i < N; i++) {
		MAX[START+i] = H[i];
	}
	for(int i = START - 1; i >= 0; i--)
		MAX[i] = MAXIMUM(MAX[LEFT(i)], MAX[RIGHT(i)]);
}

/** Zwraca w czasie O(log(n)) maksimum z tablicy H na przedziale [a,b)
 */
int _get_max(int a, int b, int i, int _start, int _end) {
	if(b <= _start || a >= _end)
		return 0;
	if(a <= _start && b >= _end)
		return MAX[i];
	int m = (_start+_end)/2;
	int l = _get_max(a, b, LEFT(i), _start, m);
	int r = _get_max(a, b, RIGHT(i), m, _end);
	return MAXIMUM(l,r);
}
int get_max(int a, int b) {
	if(a < 0) a = 0;
	if(b >= N) b = N;
	return _get_max(a, b, 0, 0, START+1);
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
