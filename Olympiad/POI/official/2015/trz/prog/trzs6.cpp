/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Trzy wieze                                         *
 *   Zlozonosc czasowa:    O(n log n)                                         *
 *   Autor programu:       Marek Sommer                                       *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                                                                            *
 *****************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

int numer_literki(char c)
{
	if(c == 'S')
		return 0;
	if(c == 'B')
		return 1;
	return 2;
}

int n;
char nap[1000005];
int sum[3][1000005];

bool ok(int a, int b)
{
	int x[3];
	for(int i = 0; i < 3; i++)
		x[i] = sum[i][b] - sum[i][a - 1];
	if(x[0] && (x[0] == x[1] || x[0] == x[2]))
		return false;
	if(x[1] && x[1] == x[2])
		return false;
	return true;
}

/* Czy istnieje rozwiązanie o długości równej dokładnie d? */
bool czy_dlugosc(int d)
{
	for(int i = d; i <= n; i++)
		if(ok(i - d + 1, i))
			return true;
	return false;
}

/* Czy istnieje rozwiązanie >= x? */
bool sprawdz(int x)
{
	/* Odpowiedź jest taka sama jak odpowiedź na pytanie:
	 * Czy istnieje rozwiązanie >= x oraz <= (x + 5) */
	for(int i = min(x + 5, n); i >= x; i--)
		if(czy_dlugosc(i))
			return true;
	return false;
}

int main()
{
	scanf("%d%s", &n, nap + 1);
	for(int i = 1; i <= n; i++)
	{
		sum[numer_literki(nap[i])][i]++;
		for(int j = 0; j < 3; j++)
			sum[j][i] += sum[j][i - 1];
	}

	int a = 1, b = n, c;
	while(a < b)
	{
		c = (a + b + 1) / 2;
		if(sprawdz(c))
			a = c;
		else
			b = c - 1;
	}

	printf("%d\n", a);
	return 0;
}
