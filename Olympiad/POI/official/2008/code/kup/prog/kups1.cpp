/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kupno gruntu (KUP)                                        *
 *   Plik:     kups1.cpp                                                 *
 *   Autor:    Jakub Pawlewicz                                           *
 *   Opis:     Rozwiazanie za wolne, zlozonosc O(n^3).                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

using namespace std;

typedef long long ll;

ll v[2001][2048];

ll get_sy(int x1, int x2, int y)
{
	return v[x2][y] - v[x1 - 1][y];
}

int main()
{
	int k, n;
	scanf("%d%d", &k, &n);
	for (int y = 0; y <= n; y++)
	for (int x = 0; x <= n; x++)
		if (x == 0 || y == 0)
			v[x][y] = 0;
		else
			scanf("%lld", &v[x][y]);
	for (int y = 1; y <= n; y++)
	for (int x = 2; x <= n; x++)
		v[x][y] += v[x - 1][y];
	for (int x1 = 1; x1 <= n; x1++)
	for (int x2 = x1; x2 <= n; x2++) {
		ll s = 0;
		int y1 = 1;
		for (int y2 = y1; y2 <= n; y2++) {
			s += get_sy(x1, x2, y2);
			while (s > 2 * k)
				s -= get_sy(x1, x2, y1++);
			if (k <= s) {
				printf("%d %d %d %d\n", x1, y1, x2, y2);
				return 0;
			}
		}
	}
	printf("NIE\n");
	return 0;
}
