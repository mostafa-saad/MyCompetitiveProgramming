#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <numeric>
#include <algorithm>
#include <bitset>
#include <complex>

using namespace std;

typedef unsigned uint;
typedef long long Int;
typedef vector<int> vint;
typedef pair<int,int> pint;
#define mp make_pair

template<class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cout << *i << " "; cout << endl; }
template<class T> void chmin(T &t, T f) { if (t > f) t = f; }
template<class T> void chmax(T &t, T f) { if (t < f) t = f; }
int in() { int x; scanf("%d", &x); return x; }

uint xrand() {
	static uint x = 314159265, y = 358979323, z = 846264338, w = 327950288;
	uint t = x ^ x << 11; x = y; y = z; z = w; return w = w ^ w >> 19 ^ t ^ t >> 8;
}

struct Tree {
	Tree *l, *r, *p;
	int size;
	pint val;
	int sum;
	pint opt;
	Tree(pint val) : l(0), r(0), p(0), val(val), sum(0) {
		update();
	}
	Tree *change(Tree *_l, Tree *_r) {
		l = _l;
		r = _r;
		if (l) l->p = this;
		if (r) r->p = this;
		update();
		return this;
	}
	void update() {
		size = (l ? l->size : 0) + 1 + (r ? r->size : 0);
		opt = val;
		if (l) chmin(opt, l->opt);
		if (r) chmin(opt, r->opt);
		opt.first += sum;
	}
	void propagate() {
		val.first += sum;
		if (l) l->add(sum);
		if (r) r->add(sum);
		sum = 0;
	}
	void add(int x) {
		sum += x;
		opt.first += x;
	}
	void print(int depth) {
		if (l) l->print(depth + 1);
		printf("%*s%p (%p, %p; %p; %d) (%d, %d; %d; %d, %d)\n", 
			depth * 2, "", this, l, r, p, size, val.first, val.second, sum, opt.first, opt.second);
		if (r) r->print(depth + 1);
	}
};

Tree *merge(Tree *a, Tree *b) {
	if (!a) return b;
	if (!b) return a;
	if ((int)(xrand() % (a->size + b->size)) < a->size) {
		a->propagate();
		a->change(a->l, merge(a->r, b));
		return a;
	} else {
		b->propagate();
		b->change(merge(a, b->l), b->r);
		return b;
	}
}

pair<Tree *,Tree *> split(Tree *a, int count) {
	if (!a) return mp(a, a);
	int sizeL = a->l ? a->l->size : 0;
	pair<Tree *,Tree *> res;
	a->propagate();
	a->p = 0;
	if (count <= sizeL) {
		res = split(a->l, count);
		if (res.first) res.first->p = 0;
		return mp(res.first, a->change(res.second, a->r));
	} else {
		res = split(a->r, count - sizeL - 1);
		if (res.second) res.second->p = 0;
		return mp(a->change(a->l, res.first), res.second);
	}
}

pair<Tree *,int> getPosition(Tree *a) {
	int count = (a->l ? a->l->size : 0);
	for (; a->p; a = a->p) {
		if (a->p->r == a) {
			count += (a->p->l ? a->p->l->size : 0) + 1;
		}
	}
	return mp(a, count);
}

Tree *getRightmost(Tree *a) {
	for (; a->r; a = a->r);
	return a;
}

const int INF = 1001001001;

pint rangeMin(Tree *a, int x, int y) {
	chmax(x, 0);
	chmin(y, a->size - 1);
	if (x == 0 && y == a->size - 1) {
		return a->opt;
	}
	pint ret(INF, -1);
	if (x <= y) {
		int sizeL = a->l ? a->l->size : 0;
		if (x <= sizeL && sizeL <= y) chmin(ret, a->val);
		if (a->l) chmin(ret, rangeMin(a->l, x, y));
		if (a->r) chmin(ret, rangeMin(a->r, x - sizeL - 1, y - sizeL - 1)); 
		ret.first += a->sum;
	}
	return ret;
}

const int LIM_N = 1000000;
const int LIM_Q = 1000000;

int N, Q;
int T[LIM_Q + 10];
int A[LIM_Q + 10], B[LIM_Q + 10];

int to[LIM_N + 10];

Tree *ptrL[LIM_N + 10], *ptrR[LIM_N + 10];

int main() {
	int q;
	int u;
	pair<Tree *,int> posA, posB;
	pair<Tree *,Tree *> spl0, spl1, spl2;
	
	//	Input
	N = in();
	Q = in();
	for (q = 0; q < Q; ++q) {
		T[q] = in();
		switch (T[q]) {
			case 1: {
				A[q] = in() - 1;
				B[q] = in() - 1;
			} break;
			case 2: {
				A[q] = in() - 1;
				B[q] = -1;
			} break;
			case 3: {
				A[q] = in() - 1;
				B[q] = in() - 1;
			} break;
			default: assert(0);
		}
	}
	
	//	Make nodes
	for (u = 0; u < N; ++u) {
		ptrL[u] = ptrR[u] = new Tree(mp(0, u));
	}
	
	memset(to, ~0, N << 2);
	for (q = 0; q < Q; ++q) {
		switch (T[q]) {
			case 1: {
				/*
					... B ...
					->
					... B A-A B ...
				*/
				posA = getPosition(ptrL[A[q]]);
				posB = getPosition(ptrL[B[q]]);
				pint val = rangeMin(posB.first, posB.second, posB.second);
				Tree *copy = new Tree(val);
				if (ptrR[B[q]] == ptrL[B[q]]) {
					ptrR[B[q]] = copy;
				}
				spl0 = split(posB.first, posB.second + 1);
				posA.first->add(val.first + 1);
				merge(merge(merge(spl0.first, posA.first), copy), spl0.second);
				to[A[q]] = B[q];
			} break;
			case 2: {
				/*
					... u A-A u ...
					->
					... u ...
				*/
				u = to[A[q]];
				posA = getPosition(ptrL[A[q]]);
				spl0 = split(posA.first, posA.second);
				spl1 = split(spl0.second, getPosition(ptrR[A[q]]).second + 1);
				spl2 = split(spl1.second, 1);
				if (ptrR[u] == spl2.first) {
					ptrR[u] = getRightmost(spl0.first);
				}
				delete spl2.first;
				merge(spl0.first, spl2.second);
				spl1.first->add(-spl1.first->opt.first);
				to[A[q]] = -1;
			} break;
			case 3: {
				posA = getPosition(ptrL[A[q]]);
				posB = getPosition(ptrL[B[q]]);
				if (posA.first != posB.first) {
					puts("-1");
				} else {
					int x = posA.second;
					int y = posB.second;
					if (x > y) {
						swap(x, y);
					}
					pint res = rangeMin(posA.first, x, y);
					printf("%d\n", res.second + 1);
				}
			} break;
			default: assert(0);
		}
	}
	
	return 0;
}
