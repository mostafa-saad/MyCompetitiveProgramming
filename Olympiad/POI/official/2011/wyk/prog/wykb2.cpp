/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Wykres                                           *
 *   Autor:             Filip Wolski                                     *
 *   Opis:              Rozwiazanie bledne                               *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#define RMIN 0
#define RMAX 1000000

#define MXN 100000
#define MXM 100000
#define EPS 1e-10

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

inline bool fits(const wsp_t *p, LD x, LD y, LD r) {
	x -= p->x; y -= p->y;
	LD dist2 = x*x + y*y;
	return dist2 <= (r+EPS) * (r+EPS);
}

wsp_t *tmp[MXN];

void random_permutate(int n) {
	for (int i = 1; i < n; ++i) {
		swap(tmp[i], tmp[rand() % (i+1)]);
	}
}

bool recompute_with_point(int i, LD &x, LD &y, LD r) {
	LD xx = tmp[i]->x, yy = tmp[i]->y;
	bool fnd = false;
	for (int j = 0; j < i; ++j) {
		if (tmp[i]->x != tmp[j]->x || tmp[i]->y != tmp[j]->y) {
			if (!fnd || !fits(tmp[j], xx, yy, r)) {
				xx = (tmp[i]->x + tmp[j]->x) / 2.;
				yy = (tmp[i]->y + tmp[j]->y) / 2.;
				LD dx = (tmp[j]->y - tmp[i]->y) / 2.;
				LD dy = (tmp[i]->x - tmp[j]->x) / 2.;
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
		for (int j = 0; j < i; ++j) {
			if (!fits(tmp[j], xx, yy, r)) {
				return false;
			}
		}
	}

	x = xx; y = yy;
	return true;
}

wsp_t wsp[MXN];

bool can_hold(int pc, int kn, LD r, fwsp_t &mid) {
	for (int i = pc; i <= kn; ++i) {
		tmp[i-pc] = &wsp[i];
	}
	random_permutate(kn-pc+1);
	LD x = tmp[0]->x, y = tmp[0]->y;
	for (int i = 1; i <= kn-pc; ++i) {
		if (!fits(tmp[i], x, y, r)) {
			if (!recompute_with_point(i, x, y, r)) {
				return false;
			}
		}
	}
	mid.x = x; mid.y = y;
	return true;
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
