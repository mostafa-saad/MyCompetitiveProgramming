/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Wykres                                           *
 *   Autor:             Filip Wolski                                     *
 *   Opis:              Rozwiazanie powolne                              *
 *                      kolo pokrywajace O(n^4),                         *
 *                      zwykle wyszukiwanie binarne                      *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#define RMIN 0
#define RMAX 1420000

#define MXN 100000
#define MXM 100000
#define EPS 1e-7

using namespace std;

typedef long double LD;

struct wsp_t {
	LD x, y;
	wsp_t(LD _x = 0., LD _y = 0.) : x(_x), y(_y) { }
};

inline LD sqr(LD x) { return x*x; }

bool LineCrossPoint(wsp_t p1, wsp_t p2, wsp_t l1, wsp_t l2, LD &x, LD &y){
	LD t = (p1.x - p2.x) * (l1.y - l2.y) - (p1.y - p2.y) * (l1.x - l2.x);
	LD s = (l2.x - p2.x) * (l1.y - l2.y) - (l2.y - p2.y) * (l1.x - l2.x);
	if (fabs(t) < EPS) return false;
	x = (s/t) * p1.x + (1-s/t) * p2.x;
	y = (s/t) * p1.y + (1-s/t) * p2.y;
	return true;
}

bool ThreePointCircle(wsp_t p1, wsp_t p2, wsp_t p3, LD &x, LD &y) {
	if (!LineCrossPoint(
				wsp_t((p1.x+p2.x)/2.0,(p1.y+p2.y)/2.0),
				wsp_t((p1.x+p2.x)/2.0+p2.y-p1.y,(p1.y+p2.y)/2.0+p1.x-p2.x),
				wsp_t((p1.x+p3.x)/2.0,(p1.y+p3.y)/2.0),
				wsp_t((p1.x+p3.x)/2.0+p3.y-p1.y,(p1.y+p3.y)/2.0+p1.x-p3.x), x, y)) {
		return false;
	}
	return true;
}

wsp_t wsp[MXN];

bool check_fit(int pc, int kn, LD x, LD y, LD r) {
	for (int i = pc; i <= kn; ++i) {
		LD dist = sqrt(sqr(wsp[i].x - x) + sqr(wsp[i].y - y));
		if (dist > r + EPS) {
			return false;
		}
	}
	return true;
}

bool can_hold(int pc, int kn, LD r, wsp_t &mid) {
	if (pc == kn) {
		mid = wsp[pc];
		return true;
	}
	for (int i = pc; i <= kn; ++i) {
		for (int j = pc; j < i; ++j) {
			LD x = (wsp[i].x + wsp[j].x) / 2.;
			LD y = (wsp[i].y + wsp[j].y) / 2.;
			if (check_fit(pc, kn, x, y, r)) {
				mid.x = x; mid.y = y;
				return true;
			}
			for (int k = pc; k < j; ++k) {
				if (ThreePointCircle(wsp[i], wsp[j], wsp[k], x, y) && check_fit(pc, kn, x, y, r)) {
					mid.x = x; mid.y = y;
					return true;
				}
			}
		}
	}
	return false;
}

int n;

void check(int &pos, LD r, wsp_t &mid) {
	int pc = pos;
	int kn = n;
	mid.x = wsp[pos].x;
	mid.y = wsp[pos].y;
	while (pc + 1 < kn) {
		int sr = (pc+kn) / 2;
		if (can_hold(pos, sr, r, mid)) {
			pc = sr;
		} else {
			kn = sr;
		}
	}
	pos = kn;
}

wsp_t mid[MXM], midsol[MXM];
int m, s, ssol;

int main() {
	LD rmin = RMIN;
	LD rmax = RMAX;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%Lf%Lf", &wsp[i].x, &wsp[i].y);
	}
	ssol = -1;
	while (rmin + EPS < rmax) {
		LD r = (rmin + rmax) / 2.;
		int cnt = 0;
		for (s = 0; s < m && cnt < n; ++s) {
			check(cnt, r, mid[s]);
		}
		if (cnt == n) {
			ssol = s;
			copy(mid, mid+s, midsol);
			rmax = r;
		} else {
			rmin = r;
		}
	}
	assert(ssol != -1 && ssol <= m);
	printf("%.8Lf\n%d\n", rmax, ssol);
	for (int i = 0; i < ssol; ++i) {
		printf("%.8Lf %.8Lf\n", midsol[i].x, midsol[i].y);
	}
	return 0;
}
