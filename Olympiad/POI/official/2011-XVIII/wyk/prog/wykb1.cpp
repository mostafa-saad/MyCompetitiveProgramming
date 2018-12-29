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
#include <list>

#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

#define MXN 100000
#define EPS 1e-6

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int,int> PII;

struct wsp_t {
	LD x, y;
	wsp_t(LD _x = 0., LD _y = 0.) : x(_x), y(_y) { }
};

bool operator<(const wsp_t &o, const wsp_t &p) {
	return false;
}

inline LD sqr(LD x) { return x*x; }

void LineCrossPoint(const wsp_t &p1, const wsp_t &p2, const wsp_t &l1, const wsp_t &l2, LD &x, LD &y) {
	LD t = (p1.x - p2.x) * (l1.y - l2.y) - (p1.y - p2.y) * (l1.x - l2.x);
	LD s = (l2.x - p2.x) * (l1.y - l2.y) - (l2.y - p2.y) * (l1.x - l2.x);
	assert(fabs(t) > EPS);
	x = (s/t) * p1.x + (1-s/t) * p2.x;
	y = (s/t) * p1.y + (1-s/t) * p2.y;
}

void ThreePointCircle(const wsp_t &p1, const wsp_t &p2, const wsp_t &p3, LD &x, LD &y, LD &r2) {
	LineCrossPoint(
			wsp_t((p1.x+p2.x)/2.0, (p1.y+p2.y)/2.0),
			wsp_t((p1.x+p2.x)/2.0+p2.y-p1.y, (p1.y+p2.y)/2.0+p1.x-p2.x),
			wsp_t((p1.x+p3.x)/2.0, (p1.y+p3.y)/2.0),
			wsp_t((p1.x+p3.x)/2.0+p3.y-p1.y, (p1.y+p3.y)/2.0+p1.x-p3.x), x, y);
	r2 = sqr(p1.x-x) + sqr(p1.y-y);
}

bool fits(const wsp_t &p, LD x, LD y, LD r2) {
	x -= p.x; y -= p.y;
	LD dist2 = x*x + y*y;
	return sqrtl(dist2) <= sqrtl(r2) + EPS;
}

wsp_t *tmp[MXN];

void recompute_with_2points(int i, int j, LD &x, LD &y, LD &r2) {
	x = (tmp[i]->x + tmp[j]->x) / 2.0;
	y = (tmp[i]->y + tmp[j]->y) / 2.0;
	r2 = (sqr(tmp[i]->x-tmp[j]->x) + sqr(tmp[i]->y-tmp[j]->y)) / 4.0;
	for (int k = 0; k < j; ++k) {
		if (!fits(*tmp[k], x, y, r2)) {
			ThreePointCircle(*tmp[i], *tmp[j], *tmp[k], x, y, r2);
		}
	}
}

void random_permutate(int n) {
	for (int i = 1; i < n; ++i) {
		swap(tmp[i], tmp[rand() % (i+1)]);
	}
}

void recompute_with_point(int i, LD &x, LD &y, LD &r2) {
	random_permutate(i);
	x = (tmp[i]->x + tmp[0]->x) / 2.;
	y = (tmp[i]->y + tmp[0]->y) / 2.;
	r2 = (sqr(tmp[i]->x-tmp[0]->x) + sqr(tmp[i]->y-tmp[0]->y)) / 4.;
	for (int j = 1; j < i; ++j) {
		if (!fits(*tmp[j], x, y, r2)) {
			recompute_with_2points(i, j, x, y, r2);
		}
	}
}

void minimal_enclosing_disc(int n, LD &x, LD &y, LD &r2) {
	random_permutate(n);
	x = (tmp[1]->x + tmp[0]->x) / 2.;
	y = (tmp[1]->y + tmp[0]->y) / 2.;
	r2 = (sqr(tmp[1]->x-tmp[0]->x) + sqr(tmp[1]->y-tmp[0]->y)) / 4.;
	for (int i = 2; i < n; ++i) {
		if (!fits(*tmp[i], x, y, r2)) {
			recompute_with_point(i, x, y, r2);
		}
	}
}

LL get_dist2(const wsp_t &o, const wsp_t &p) {
	return (LL)(o.x-p.x) * (LL)(o.x-p.x) + (LL)(o.y-p.y) * (LL)(o.y-p.y);
}

wsp_t wsp[MXN];

void min_hold(int pc, int kn, LD &r2, wsp_t &mid) {
	if (pc == kn) {
		mid = wsp[pc];
		r2 = 0;
		return;
	}
	for (int i = pc; i <= kn; ++i) {
		tmp[i-pc] = &wsp[i];
	}
	minimal_enclosing_disc(kn-pc+1, mid.x, mid.y, r2);
}

int n, m;
int oj[MXN];

int f(int x) {
	if (oj[x] < 0) return x;
	oj[x] = f(oj[x]);
	return oj[x];
}

void join(int i, int j) {
	if (oj[i] < oj[j]) {
		oj[j] = i;
	} else {
		oj[j] = min(oj[j], oj[i]-1);
		oj[i] = j;
	}
}

PII interval[MXN];
list< pair<LL,PII> > kol;

int main() {
	scanf("%d%d", &n, &m);

	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		wsp[i].x = x; wsp[i].y = y;
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			kol.push_back(make_pair(get_dist2(wsp[i], wsp[j]), make_pair(i, j)));
		}
	}

	kol.sort();

	for (int i = 0; i < n; ++i) {
		interval[i].first = interval[i].second = i;
		oj[i] = -1;
	}

	int joins = 0;
	for (list< pair<LL,PII> > :: iterator it = kol.begin(); it != kol.end() && m + joins < n; ++it) {
		int i = f(it->second.first);
		int j = f(it->second.second);
		if (i != j && (interval[i].first == interval[j].second+1 || interval[j].first == interval[i].second+1)) {
			PII inter = PII(min(interval[i].first, interval[j].first), max(interval[i].second, interval[j].second));
			interval[i] = interval[j] = inter;
			join(i, j);
			++joins;
		}
	}

	LD r = 0;
	list< pair<int,wsp_t> > res;
	for (int i = 0; i < n; ++i) {
		if (oj[i] < 0) {
			LD cur_r;
			wsp_t mid;
			min_hold(interval[i].first, interval[i].second, cur_r, mid);
			res.push_back(make_pair(interval[i].first, mid));
			r = max(r, cur_r);
		}
	}

	res.sort();
	printf("%.8Lf\n%d\n", sqrtl(r), m);
	FOREACH(it,res) {
		printf("%.8Lf %.8Lf\n", it->second.x, it->second.y);
	}
	return 0;
}
