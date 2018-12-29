/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Wykres                                           *
 *   Autor:             Filip Wolski                                     *
 *   Opis:              Rozwiazanie powolne                              *
 *                      kolo pokrywajace liniowo,                        *
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

void LineCrossPoint(const wsp_t &p1, const wsp_t &p2, const wsp_t &l1, const wsp_t &l2, LD &x, LD &y){
	LD t = (p1.x - p2.x) * (l1.y - l2.y) - (p1.y - p2.y) * (l1.x - l2.x);
	LD s = (l2.x - p2.x) * (l1.y - l2.y) - (l2.y - p2.y) * (l1.x - l2.x);
	assert(fabs(t) > EPS);
	x = (s/t) * p1.x + (1-s/t) * p2.x;
	y = (s/t) * p1.y + (1-s/t) * p2.y;
}

void ThreePointCircle(const wsp_t &p1, const wsp_t &p2, const wsp_t &p3, LD &x, LD &y, LD &r) {
	LineCrossPoint(
			wsp_t((p1.x+p2.x)/2.0, (p1.y+p2.y)/2.0),
			wsp_t((p1.x+p2.x)/2.0+p2.y-p1.y, (p1.y+p2.y)/2.0+p1.x-p2.x),
			wsp_t((p1.x+p3.x)/2.0, (p1.y+p3.y)/2.0),
			wsp_t((p1.x+p3.x)/2.0+p3.y-p1.y, (p1.y+p3.y)/2.0+p1.x-p3.x), x, y);
	r = sqrt(sqr(p1.x-x) + sqr(p1.y-y));
}

bool fits(const wsp_t *p, LD x, LD y, LD r) {
	x -= p->x; y -= p->y;
	LD dist2 = x*x + y*y;
	return sqrtl(dist2) <= r + EPS;
}

wsp_t *tmp[MXN];

void recompute_with_2points(int i, int j, LD &x, LD &y, LD &r) {
	x = (tmp[i]->x + tmp[j]->x) / 2.0;
	y = (tmp[i]->y + tmp[j]->y) / 2.0;
	r = sqrt(sqr(tmp[i]->x-tmp[j]->x) + sqr(tmp[i]->y-tmp[j]->y)) / 2.0;
	for (int k = 0; k < j; ++k) {
		if (!fits(tmp[k], x, y, r)) {
			ThreePointCircle(*tmp[i], *tmp[j], *tmp[k], x, y, r);
		}
	}
}

void random_permutate(int n) {
	for (int i = 1; i < n; ++i) {
		swap(tmp[i], tmp[rand() % (i+1)]);
	}
}

int recomputations = 0;

void recompute_with_point(int i, LD &x, LD &y, LD &r) {
	++recomputations;
	random_permutate(i);
	x = (tmp[i]->x + tmp[0]->x) / 2.;
	y = (tmp[i]->y + tmp[0]->y) / 2.;
	r = sqrt(sqr(tmp[i]->x-tmp[0]->x) + sqr(tmp[i]->y-tmp[0]->y)) / 2.;
	for (int j = 1; j < i; ++j) {
		if (!fits(tmp[j], x, y, r)) {
			recompute_with_2points(i, j, x, y, r);
		}
	}
}

void minimal_enclosing_disc(int n, LD &x, LD &y, LD &r) {
	random_permutate(n);
	x = (tmp[1]->x + tmp[0]->x) / 2.;
	y = (tmp[1]->y + tmp[0]->y) / 2.;
	r = sqrt(sqr(tmp[1]->x-tmp[0]->x) + sqr(tmp[1]->y-tmp[0]->y)) / 2.;
	for (int i = 2; i < n; ++i) {
		if (!fits(tmp[i], x, y, r)) {
			recompute_with_point(i, x, y, r);
		}
	}
}

wsp_t wsp[MXN];

bool can_hold(int pc, int kn, LD r, wsp_t &mid) {
	if (pc == kn) {
		mid = wsp[pc];
		return true;
	}
	LD x, y, rr;
	for (int i = pc; i <= kn; ++i) {
		tmp[i-pc] = &wsp[i];
	}
	minimal_enclosing_disc(kn-pc+1, x, y, rr);
	if (rr < r + EPS) {
		mid.x = x; mid.y = y;
		return true;
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
int bincount = 0;

int main() {
	LD rmin = RMIN;
	LD rmax = RMAX;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%Lf%Lf", &wsp[i].x, &wsp[i].y);
	}
	ssol = -1;
	while (rmin + EPS < rmax) {
		++bincount;
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
//	printf("recomputations = %d, bincount = %d\n", recomputations, bincount);
	for (int i = 0; i < ssol; ++i) {
		printf("%.8Lf %.8Lf\n", midsol[i].x, midsol[i].y);
	}
	return 0;
}
