/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kupno gruntu (KUP)                                        *
 *   Plik:     kup.cpp                                                   *
 *   Autor:    Jakub Pawlewicz                                           *
 *   Opis:     Rozwiazanie wzorcowe, zlozonosc O(n^2).                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <stack>
#include <vector>

using namespace std;

typedef long long ll;

ll v[2001][2048];

ll get_s(int x1, int y1, int x2, int y2)
{
	return v[x2][y2] - v[x1 - 1][y2] - v[x2][y1 - 1] + v[x1 - 1][y1 - 1];
}

void solve(int k, int x1, int y1, int x2, int y2)
{
	for (int y = y1; y <= y2; y++)
		for (int x = x1; x <= x2; x++) {
			ll s = get_s(x1, y, x, y);
			if (k <= s) {
				printf("%d %d %d %d\n", x1, y, x, y);
				return;
			}
		}
	for (int y = y1; y <= y2; y++) {
		ll s = get_s(x1, y1, x2, y);
		if (k <= s) {
			printf("%d %d %d %d\n", x1, y1, x2, y);
			return;
		}
	}
}

struct point {
	int x, y;
	point() { }
	point(int x, int y) : x(x), y(y) { }
};

int main()
{
	int k, n;
	scanf("%d%d", &k, &n);
	for (int x = 0; x <= n; x++)
		v[x][0] = 0;
	vector<int> y1(n + 1, 1);
	for (int y = 1; y <= n; y++) {
		ll sx = 0;
		stack<point> S;
		S.push(point(0, y + 1));
		for (int x = 0; x <= n; x++) {
			v[x][y] = sx + v[x][y - 1];
			int a;
			if (x < n)
				scanf("%d", &a);
			else
				a = 2 * k + 1;
			sx += a;
			if (a > 2 * k)
				y1[x] = y + 1;
			else if (a >= k) {
				printf("%d %d %d %d\n", x + 1, y, x + 1, y);
				return 0;
			}
			int x1 = x + 1;
			while (y1[x] > S.top().y) {
				x1 = S.top().x;
				int y0 = S.top().y;
				S.pop();
				ll s = get_s(x1, y0, x, y);
				if (k <= s) {
					solve(k, x1, y0, x, y);
					return 0;
				}
			}
			if (S.top().y > y1[x])
				S.push(point(x1, y1[x]));
		}
	}
	printf("NIE\n");
	return 0;
}
