/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *          pamieciowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe                             *
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
void oblicz_przedzialy(int sum) {
	wa[sum] = i + 1;
	wb[sum] = l + 1;

	while (sum > 2) {
		while ((sum > 2) && (s[i] == 'T')) {
			sum -= 2;
			wa[sum] = ++i + 1;
			wb[sum] = l + 1;
		}
		while ((sum > 2) && (s[l] == 'T')) {
			sum -= 2;
			wa[sum] = i + 1;
			wb[sum] = --l + 1;
		}
		
		if (sum > 2) {
			sum -= 2;
			wa[sum] = ++i + 1;
			wb[sum] = --l + 1;
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
	
	oblicz_przedzialy(sum);

	/* szukamy 'W' najblizszego krawedzi lizaka by wyznaczyc najwiekszy *
	 * fragment, ktorego cena ma inna parzystosc niz cena calego lizaka */
	i = 0;
	while ((i < n) && (s[i] == 'T'))
		++i;

	l = 0;
	while ((i < n - l) && (s[n - l - 1] == 'T'))
		++l;
	
	if (s[i] == 'T') /* brak smaku waniliowego */
		max[1] = 0;
	else {
		if (i < l) { /* 'W' blizej lewego konca */
			sum -= 2 * i + 1;
			max[sum % 2] = sum;
			i += 1;
			l = n - 1;
		} else { /* 'W' blizej prawego konca (lub rownie blisko) */
			sum -= 2 * l + 1;
			max[sum % 2] = sum; 	
			i = 0;
			l = n - l - 2;
		}

		oblicz_przedzialy(sum);
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
