/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kupno gruntu (KUP)                                        *
 *   Plik:     kups3.cpp                                                 *
 *   Autor:    Jakub Pawlewicz                                           *
 *   Opis:     Rozwiazanie za wolne, zlozonosc O(n^6).                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

using namespace std;

typedef long long ll;

int v[2000][2048];

int main()
{
	int k, n;
	scanf("%d%d", &k, &n);
	for (int y = 0; y < n; y++)
	for (int x = 0; x < n; x++)
		scanf("%d", &v[x][y]);
	for (int x1 = 0; x1 < n; x1++)
	for (int x2 = x1; x2 < n; x2++)
	for (int y1 = 0; y1 < n; y1++)
	for (int y2 = y1; y2 < n; y2++) {
		ll s = 0;
		for (int x = x1; x <= x2; x++)
		for (int y = y1; y <= y2; y++)
			s += v[x][y];
		if (k <= s && s <= 2 * k) {
			printf("%d %d %d %d\n", x1 + 1, y1 + 1, x2 + 1, y2 + 1);
			return 0;
		}
	}
	printf("NIE\n");
	return 0;
}
