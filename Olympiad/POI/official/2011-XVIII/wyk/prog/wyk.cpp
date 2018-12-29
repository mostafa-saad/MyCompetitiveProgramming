/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Wykres                                           *
 *   Autor:             Jakub Wojtaszczyk                                *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      (wieksza stala niz w wyk1.cpp)                   *
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

inline LD sqrl(LD x) {return x * x;}

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

inline LD get_square(const wsp_t &p) {
  return (LD) (sqr(p.x) + sqr(p.y));
}

void recompute_with_three (int k, int l, int m, LD &x, LD &y, LD &r) {
  LD mian = (LD) tmp[k]->x * (LD) tmp[l]->y - (LD) tmp[k]->y * (LD) tmp[l]->x +
            (LD) tmp[l]->x * (LD) tmp[m]->y - (LD) tmp[l]->y * (LD) tmp[m]->x +
            (LD) tmp[m]->x * (LD) tmp[k]->y - (LD) tmp[m]->y * (LD) tmp[k]->x;
  mian *= 2.;
  x = get_square(*tmp[k]) * (LD) (tmp[m]->y - tmp[l]->y) +
      get_square(*tmp[l]) * (LD) (tmp[k]->y - tmp[m]->y) + 
      get_square(*tmp[m]) * (LD) (tmp[l]->y - tmp[k]->y);
  y = get_square(*tmp[k]) * (LD) (tmp[m]->x - tmp[l]->x) +
      get_square(*tmp[l]) * (LD) (tmp[k]->x - tmp[m]->x) + 
      get_square(*tmp[m]) * (LD) (tmp[l]->x - tmp[k]->x);
  x /= -mian; y /= mian;
  r = sqrt(sqrl(x - (LD) tmp[k]->x) + sqrl(y - (LD) tmp[k]->y));
}

void recompute_with_two (int k, int l, LD &x, LD &y, LD &r) {
  random_permutate(k-1);
  x = (tmp[k]->x + tmp[l]->x) / 2.;
  y = (tmp[k]->y + tmp[l]->y) / 2.;
  r = get_dist(*tmp[k], *tmp[l]) / 2.;
  for (int i = 0; i < k; i++) {
    if (!fits(tmp[i], x, y, r)) {
      recompute_with_three(k, l, i, x, y, r);
    }
  }
}

void recompute_with_point (int k, LD &x, LD &y, LD &r) {
  random_permutate(k-1);
  x = tmp[k]->x; y = tmp[k]->y; r = 0.;
  for (int i = 0; i < k; i++) {
    if (!fits(tmp[i], x, y, r)) {
      recompute_with_two (i, k, x, y, r);
    }
  }
}

wsp_t wsp[MXN];

bool can_hold(int pc, int kn, LD r, fwsp_t &mid) {
	for (int i = pc; i <= kn; ++i) {
		tmp[i-pc] = &wsp[i];
	}
	random_permutate(kn-pc+1);
	LD x = tmp[0]->x, y = tmp[0]->y, cr = 0.;
	for (int i = 1; i <= kn-pc; ++i) {
		if (!fits(tmp[i], x, y, cr)) {
			recompute_with_point(i, x, y, cr);
// DBG
			if (cr > RMAX) {
			  for (int i = 0; i < kn-pc+1; i++) {
			    printf("%d %d\n", tmp[i]->x, tmp[i]->y);
			  }
			  printf("(%Lf %Lf) %Lf\n", x, y,cr);
			  exit(0);
			}
			if (cr > r) {
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
	assert(ssol != -1);
	assert(ssol <= m);
	printf("%.8Lf\n%d\n", rmax, ssol);
	for (int i = 0; i < ssol; ++i) {
		printf("%.8Lf %.8Lf\n", midsol[i].x, midsol[i].y);
	}
	return 0;
}
