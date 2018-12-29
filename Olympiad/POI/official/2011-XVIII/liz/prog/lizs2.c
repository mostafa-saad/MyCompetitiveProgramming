/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * n + m)                                     *
 *          pamieciowa: O(n)                                             *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#define MAX_N 1000000
#define MAX_K 2000000

int n, m; /* ilosc segmentow, ilosc rozwazanych cen */
int i, l, sum; /* iteratory i zmienna pomocnicza */
char s[MAX_N + 1]; /* opis lizaka */
int wa[MAX_K + 1], wb[MAX_K + 1];	/* [wa[j], wb[j]] to przedzial o koszcie j */

int main() {
	scanf("%d %d", &n, &m);
	scanf("%s", s);

	for (i = 0; i < n; ++i) {
		wa[2*i] = 0;
		wa[2*i + 1] = 0;
	}

	/* sprawdzamy wszystkie przedzialy i wypelniamy tablice wa[], wb[] */
	for (i = 0; i < n; ++i) {
		sum = 0;
		for (l = i; l < n; ++l) {
			if (s[l] == 'T')
				sum += 2;
			else
				sum += 1;

			wa[sum] = i + 1;
			wb[sum] = l + 1;
		}
	}

	/* odpowiadamy na zapytania korzystajac z tablic wa[] i wb[] */
	for (i = 0; i < m; ++i) {
		scanf("%d", &sum);
		if (wa[sum] == 0)
			printf("NIE\n");
		else
			printf("%d %d\n", wa[sum], wb[sum]);
	}

	return 0;
}
