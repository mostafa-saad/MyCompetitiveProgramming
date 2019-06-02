/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * m * lg(n))                                 *
 *          pamieciowa: O(n)                                             *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Rozwiazanie przez bisekcje, dla kazdej nieznanej *
 *                      kwoty wykonujemy wyszukiwanie binarne            *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#define MAX_N 1000000
#define MAX_K 2000000

int n, m;	/* ilosc segmentow lizaka i ilosc rozwazanych cen */
int sum[MAX_N + 1]; /* sum[i] cena fragmentu [1, i] */
int i, l, k;
int max[2];	/* najwieksza cena parzysta i nieparzysta */
int a, b, c; /* poczatek, koniec i srodek rozwazanego przedzialu */
int wa[MAX_K + 1], wb[MAX_K + 1]; /* przedzial wynikowy */
char s[MAX_N + 1];	/* opis lizaka */

int main() {
	scanf("%d %d", &n, &m);
	scanf("%s", s);

	sum[0] = 0;
	for (i = 0; i < n; ++i) {
		if (s[i] == 'W')
			sum[i + 1] = sum[i] + 1;
		else
			sum[i + 1] = sum[i] + 2;

		wa[2*i + 1] = -1;
		wa[2*i + 2] = -1;
	}
	
	for (i = 0; i < m ; ++i) {
		scanf ("%d", &k);
		l = 0;
		/* zaczynamy przeszukiwanie jezeli nie znamy przedzialu o koszcie k */
		while ((wa[k] == -1) && (sum[n] - sum[l] >= k)) {
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
				wa[k] = l + 1;
				wb[k] = a;
			}
			++l;
		}

		if (wa[k] == -1)
			wa[k] = 0;

		if (wa[k] != 0)
			printf("%d %d\n", wa[k], wb[k]);
		else
			printf("NIE\n");
	}

	return 0;
}
