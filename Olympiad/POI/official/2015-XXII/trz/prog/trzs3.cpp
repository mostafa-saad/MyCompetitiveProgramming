/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Trzy wieze                                         *
 *   Zlozonosc czasowa:    O(n^2)                                             *
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

int main()
{
	scanf("%d%s", &n, nap + 1);
	for(int i = 1; i <= n; i++)
	{
		sum[numer_literki(nap[i])][i]++;
		for(int j = 0; j < 3; j++)
			sum[j][i] += sum[j][i - 1];
	}
	int wyn = 0;

	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j++)
			if(ok(i, j))
				wyn = max(wyn, j - i + 1);

	printf("%d\n", wyn);
	return 0;
}
