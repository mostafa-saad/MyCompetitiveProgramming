/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *          pamieciowa: O(n)                                             *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Nie uwzglednia, ze segment waniliowy moze byc    *
 *                      blizej "prawego konca"                           *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#define MAX_N 1000000
#define MAX_K 2000000

int n, m;	/* ilosc segmentow lizaka i ilosc rozwazanych cen */
int wa[MAX_K + 1], wb[MAX_K + 1]; /* [wa[j], wb[j]] to przedzial o koszcie j */
int i, l, sum = 0;
int max[2];	/* najwieksza cena parzysta i nieparzysta */
char s[MAX_N + 1];	/* opis lizaka */

/* funkcja obliczajaca wa[x], wb[x] dla (x <= sum) i ((sum + x) mod 2 == 0) */
void oblicz_przedzialy() {
	int sum_tmp = sum;
	wa[sum] = i + 1;
	wb[sum] = l + 1;

	while (sum_tmp > 2) {
		while ((sum_tmp > 2) && (s[i] == 'T')) {
			sum_tmp -= 2;
			wa[sum_tmp] = ++i + 1;
			wb[sum_tmp] = l + 1;
		}
		while ((sum_tmp > 2) && (s[l] == 'T')) {
			sum_tmp -= 2;
			wa[sum_tmp] = i + 1;
			wb[sum_tmp] = --l + 1;
		}
		
		if (sum_tmp > 2) {
			sum_tmp -= 2;
			wa[sum_tmp] = ++i + 1;
			wb[sum_tmp] = --l + 1;
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	scanf("%s", s);

	for (l = 0; l < n; ++l)
		if (s[l] == 'T')
			sum += 2;
		else
			sum += 1;
	
	i = 0;
	l = n - 1;
	max[sum % 2] = sum;

	oblicz_przedzialy();
	/* szukamy pierwszego 'W' od poczatku lizaka */
	i = 0;
	while ((i < n) && (s[i] == 'T'))
		++i;
	
	if (i == n) /* brak waniliowego */
		max[1 - (sum % 2)] = 0;
	else {
		sum -= 2 * i + 1;
		max[sum % 2] = sum;
		i += 1;
		l = n - 1;
		oblicz_przedzialy();
	}

	/* odpowiadamy na zapytania korzystajac z tablic wa[] i wb[] */
	for (i = 0; i < m; ++i) {
		scanf("%d", &sum);

		if (max[sum % 2] < sum)
			printf("NIE\n");
		else
			printf("%d %d\n", wa[sum], wb[sum]);
	}

	return 0;
}
