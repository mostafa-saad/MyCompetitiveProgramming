/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Wykres                                           *
 *   Autor:             Filip Wolski                                     *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Zaklada, ze jednym z punktow na obwodzie kola    *
 *                      musi byc jeden z 4 punktow skrajnych pod         *
 *                      wzgledem odcietej lub rzednej                    *
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
#define EPS 1e-6

using namespace std;

typedef long long LL;
typedef long double LD;

struct wsp_t {
	int x, y;
	wsp_t(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

struct fwsp_t {
	LD x, y;
};

inline LL sqr(int x) { return (LL)x*(LL)x; }

inline LL get_ilwek(const wsp_t &o, const wsp_t &p) {
	return (LL)o.x * (LL)p.y - (LL)o.y * (LL)p.x;
}

inline LL get_ilskal(const wsp_t &o, const wsp_t &p) {
	return (LL)o.x * (LL)p.x + (LL)o.y * (LL)p.y;
}

inline wsp_t wek(const wsp_t &o, const wsp_t &p) {
	return wsp_t(p.x-o.x, p.y-o.y);
}

inline LL get_dist2(const wsp_t &o, const wsp_t &p) {
	return sqr(o.x-p.x) + sqr(o.y-p.y);
}

inline LD get_dist(const wsp_t &o, const wsp_t &p) {
	return sqrt((LD)get_dist2(o, p));
}

bool fits(const wsp_t &p, LD x, LD y, LD r) {
	x -= p.x; y -= p.y;
	LD dist2 = x*x + y*y;
	return sqrtl(dist2) <= r + EPS;
}

int cnt;
wsp_t wsp[MXN];

bool recompute_with_point(wsp_t *pt, int pc, int kn, LD &x, LD &y, LD r) {
	++cnt;

	LD xx = pt->x, yy = pt->y;
	bool fnd = false;
	for (int i = pc; i <= kn; ++i) {
		if (pt->x != wsp[i].x || pt->y != wsp[i].y) {
			if (!fnd || !fits(wsp[i], xx, yy, r)) {
				xx = (pt->x + wsp[i].x) / 2.;
				yy = (pt->y + wsp[i].y) / 2.;
				LD dx = (wsp[i].y - pt->y) / 2.;
				LD dy = (pt->x - wsp[i].x) / 2.;
				LD d = sqrtl(dx * dx + dy * dy);
				if (d > r) return false;
				LD h = sqrtl(r*r - d*d);
				xx += dx * h / d;
				yy += dy * h / d;
				fnd = true;
			}
		}
	}

	if (fnd) {
		for (int i = pc; i <= kn; ++i) {
			if (!fits(wsp[i], xx, yy, r)) {
				return false;
			}
		}
	}

	x = xx; y = yy;
	return true;
}

bool can_hold(int pc, int kn, LD r, fwsp_t &mid) {
	wsp_t *up = &wsp[pc], *down = &wsp[pc], *left = &wsp[pc], *right = &wsp[pc];
	for (int i = pc+1; i <= kn; ++i) {
		if (wsp[i].x < left->x) left = &wsp[i];
		if (wsp[i].x > right->x) right = &wsp[i];
		if (wsp[i].y < down->y) down = &wsp[i];
		if (wsp[i].y > up->y) up = &wsp[i];
	}

	LD x, y;
	if (recompute_with_point(up, pc, kn, x, y, r)) {
		mid.x = x; mid.y = y; return true;
	}
	if (recompute_with_point(down, pc, kn, x, y, r)) {
		mid.x = x; mid.y = y; return true;
	}
	if (recompute_with_point(left, pc, kn, x, y, r)) {
		mid.x = x; mid.y = y; return true;
	}
	if (recompute_with_point(right, pc, kn, x, y, r)) {
		mid.x = x; mid.y = y; return true;
	}
	return false;
}

int n;

void check(int &pos, LD r, fwsp_t &mid) {
	int count = 1;
	mid.x = wsp[pos].x;
	mid.y = wsp[pos].y;
	while (pos + count < n && can_hold(pos, pos + count, r, mid)) {
		count *= 2;
	}
	int pc = pos + count / 2;
	int kn = min(pos + count, n);
	while (pc + 1 < kn) {
		int sr = (pc + kn) / 2;
		if (can_hold(pos, sr, r, mid)) {
			pc = sr;
		} else {
			kn = sr;
		}
	}
	pos = kn;
}

fwsp_t mid[MXM], midsol[MXM];
int m, s, ssol;

int main() {
	LD rmin = RMIN;
	LD rmax = RMAX;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &wsp[i].x, &wsp[i].y);
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
