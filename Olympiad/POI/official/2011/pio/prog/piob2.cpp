/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Piorunochron                                     *
 *   Autor:             Juliusz Sompolski                                *
 *   Opis:              Rozwiazanie bledne                               *
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

int findL(int a, int b) { // BLAD - wyszukiwanie binarne po funkcji niemonotonicznej
	int l = 1, r = n + 1;
	while (l < r) {
		int c = (l + r) / 2;
		if (h[a] + sqt[abs(a - c)] >= h[b] + sqt[abs(b - c)])
			r = c;
		else
			l = c + 1;
	}
	return l;
}

bool got[sN + 1];

int s[sN + 1], l[sN + 1], ss;

int res[N + 1];


void find() {
	for (int i = 0; i <= sqt[n]; ++i)
		got[i] = false;
	ss = 0;
	l[0] = n + 1;
	for (int i = 1; i <= n; ++i) {
		if (h[i] >= hMax - sqt[n] && !got[hMax - h[i]]) {
			got[hMax - h[i]] = true;
			while (ss >= 1 && findL(s[ss], i) >= l[ss - 1])
				--ss;
			if (ss >= 1)
				l[ss] = findL(s[ss], i);
			if (l[ss] > 1) {
				++ss;
				s[ss] = i;
				l[ss] = 1;
			}
		}
	}
	int r = n;
	for (int i = 1; i <= ss; ++i) {
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
