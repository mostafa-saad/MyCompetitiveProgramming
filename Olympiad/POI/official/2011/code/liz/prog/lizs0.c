/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * n * m)                                     *
 *          pamieciowa: O(n)                                             *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#define MAX_N 1000000

int n, m; /* ilosc segmentow, ilosc rozwazanych cen */
int j, i, l; /* iteratory */
int k, sum;
char s[MAX_N + 1]; /* opis lizaka */

int main() {
	scanf("%d %d", &n, &m);
	scanf("%s", s);
	
	for (j = 0; j < m; ++j) {
		scanf("%d", &k);
		i = 0;
		while ((k != 0) && (i < n)) {
			sum = 0;
			l = i;
			while ((k != 0) && (l < n)) {
				if (s[l] == 'T')
					sum += 2;
				else
					sum += 1;
				if (sum == k)
					k = 0;
				++l;
			}
			++i;
		}

		if (k != 0)
			printf("NIE\n");
		else
			printf("%d %d\n", i, l);
	}

	return 0;
}
