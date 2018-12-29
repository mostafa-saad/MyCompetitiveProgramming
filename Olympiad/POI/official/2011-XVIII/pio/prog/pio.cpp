/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Piorunochron                                     *
 *   Autor:             Jakub Pachocki                                   *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cmath>
#include <cassert>
#include <algorithm>

using namespace std;

const int N = (int) 5e5;
const int sN = 720;

double sqt[N + 1];

int h[N + 1], hMax;

int n;

int findL(int a, int b) {
	int l = b, r = n + 1;
	while (l < r) {
		int c = (l + r) / 2;
		if (h[a] + sqt[abs(a - c)] >= h[b] + sqt[abs(b - c)])
			l = c + 1;
		else
			r = c;
	}
	return l;
}

int s[sN + 1], l[sN + 1], ss;

int res[N + 1];

void find() {
	ss = 0;
  s[0] = 0;
  h[0] = -1e6;
	int prev = hMax - (int) ceil(sqt[n]) - 1;
	for (int i = 1; i <= n; ++i) {
		if (h[i] > prev) {
			prev = h[i];
			while (ss >= 1 && findL(s[ss], i) <= l[ss])
				--ss;
			l[ss + 1] = findL(s[ss], i);
			if (l[ss + 1] <= n)
				s[++ss] = i;
		}
	}
	int r = n;
	for (int i = ss; i >= 1; --i) {
		while (r >= l[i]) {
			res[r] = max(res[r], h[s[i]] - h[r] + (int) ceil(sqt[abs(s[i] - r)]));
			--r;
		}
	}
}

int main() {
	assert(scanf("%d", &n));
	hMax = 0;
	for (int i = 1; i <= n; ++i) {
		assert(scanf("%d", &h[i]));
		hMax = max(hMax, h[i]);
	}
	for (int i = 0; i <= n; ++i)
		sqt[i] = sqrt(i);
	find();
	reverse(h + 1, h + n + 1);
	reverse(res + 1, res + n + 1);
	find();
	reverse(res + 1, res + n + 1);
	for (int i = 1; i <= n; ++i)
		printf("%d\n", res[i]);
}
