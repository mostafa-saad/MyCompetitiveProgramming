/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * m * lg(n))                                 *
 *          pamieciowa: O(n)                                             *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Rozwiazanie przez bisekcje                       *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#define MAX_N 1000000

int n, m;	/* ilosc segmentow lizaka i ilosc rozwazanych cen */
int sum[MAX_N + 1]; /* sum[i] cena fragmentu [1, i] */
int i, l, k;
int max[2];	/* najwieksza cena parzysta i nieparzysta */
int a, b, c; /* poczatek, koniec i srodek rozwazanego przedzialu */
int wa, wb; /* przedzial wynikowy */
char s[MAX_N + 1];	/* opis lizaka */

int main() {
	scanf("%d %d", &n, &m);
	scanf("%s", s);

	sum[0] = 0;
	for (i = 0; i < n; ++i)
		if (s[i] == 'W')
			sum[i + 1] = sum[i] + 1;
		else
			sum[i + 1] = sum[i] + 2;
	
	for (i = 0; i < m ; ++i) {
		scanf ("%d", &k);
		wa = 0;
		if (k <= sum[n]) {
			l = 0;
			while ((wa == 0) && (l < n)) {
				/* przeszukiwanie binarne konca przedzialu dla poczatku l */
				a = l;
				b = n;
				while (a < b) {
					c = (a + b) / 2;
					if (sum[c] - sum[l] < k)
						a = c + 1;
					else if (sum[c] - sum[l] > k)
						b = c - 1;
					else {
						a = c;
						b = c;
					}
				}

				if (sum[a] - sum[l] == k) {
					wa = l + 1;
					wb = a;
				}
				++l;
			}
		}
		if (wa != 0)
			printf("%d %d\n", wa, wb);
		else
			printf("NIE\n");
	}

	return 0;
}
