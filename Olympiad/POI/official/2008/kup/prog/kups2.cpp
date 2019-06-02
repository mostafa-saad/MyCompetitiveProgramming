/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kupno gruntu (KUP)                                        *
 *   Plik:     kups2.cpp                                                 *
 *   Autor:    Jakub Pawlewicz                                           *
 *   Opis:     Rozwiazanie za wolne, zlozonosc O(n^4).                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

using namespace std;

typedef long long ll;

ll v[2001][2048];

ll get_s(int x1, int y1, int x2, int y2)
{
	return v[x2][y2] - v[x1 - 1][y2] - v[x2][y1 - 1] + v[x1 - 1][y1 - 1];
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
	for (int x = 1; x <= n; x++)
	for (int y = 2; y <= n; y++)
		v[x][y] += v[x][y - 1];
	for (int x1 = 1; x1 <= n; x1++)
	for (int x2 = x1; x2 <= n; x2++)
	for (int y1 = 1; y1 <= n; y1++)
	for (int y2 = y1; y2 <= n; y2++) {
		ll s = get_s(x1, y1, x2, y2);
		if (k <= s && s <= 2 * k) {
			printf("%d %d %d %d\n", x1, y1, x2, y2);
			return 0;
		}
	}
	printf("NIE\n");
	return 0;
}
