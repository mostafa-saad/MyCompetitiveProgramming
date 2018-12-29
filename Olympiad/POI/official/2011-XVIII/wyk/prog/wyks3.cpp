/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Wykres                                           *
 *   Autor:             Filip Wolski                                     *
 *   Opis:              Rozwiazanie powolne                              *
 *                      kolo pokrywajace kwadratowo,                     *
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
#define EPS 1e-8

using namespace std;

typedef long double LD;

struct wsp_t {
	LD x, y;
	wsp_t(LD _x = 0., LD _y = 0.) : x(_x), y(_y) { }
};

inline LD sqr(LD x) { return x*x; }

bool fits(const wsp_t &p, LD x, LD y, LD r) {
	x -= p.x; y -= p.y;
	LD dist2 = x*x + y*y;
	return sqrtl(dist2) <= r + EPS;
}

wsp_t wsp[MXN];

bool can_hold(int pc, int kn, LD r, wsp_t &mid) {
	if (pc == kn) {
		mid = wsp[pc];
		return true;
	}

	for (int i = pc; i <= kn; ++i) {
		bool fnd = false, ok = true;
		LD xx = wsp[i].x, yy = wsp[i].y;
		for (int j = pc; j <= kn && ok; ++j) {
			if (wsp[i].x != wsp[j].x || wsp[i].y != wsp[j].y) {
				if (!fnd || !fits(wsp[j], xx, yy, r)) {
					xx = (wsp[i].x + wsp[j].x) / 2.;
					yy = (wsp[i].y + wsp[j].y) / 2.;
					LD dx = (wsp[j].y - wsp[i].y) / 2.;
					LD dy = (wsp[i].x - wsp[j].x) / 2.;
					LD d = sqrtl(dx * dx + dy * dy);
					if (d > r) {
						ok = false;
					} else {
						LD h = sqrtl(r*r - d*d);
						xx += dx * h / d;
						yy += dy * h / d;
						fnd = true;
					}
				}
			}
		}

		if (fnd) {
			for (int j = pc; j <= kn && ok; ++j) {
				if (!fits(wsp[j], xx, yy, r)) {
					ok = false;
				}
			}
		}

		if (ok) {
			mid.x = xx; mid.y = yy;
			return true;
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
