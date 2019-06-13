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

const Int INF = 1001001001001001001LL;
const int LIM_N = 100000;

int K, M, D;
Int A;
int N;
int T[LIM_N + 10];
Int B[LIM_N + 10];

int xsLen;
int xs[LIM_N + 10];

int getPos(int x) {
	return lower_bound(xs, xs + xsLen, x) - xs;
}

int segN;
Int seg[LIM_N * 4 + 10];

void init(int n) {
	for (segN = 1; segN < n; segN <<= 1);
	int a;
	for (a = segN * 2; --a; ) seg[a] = -INF;
}
void update(int a, Int val) {
	for (a += segN; a; a >>= 1) {
		chmax(seg[a], val);
	}
}
Int rangeMax(int a, int b) {
	Int ret = -INF;
	for (a += segN, b += segN; a <= b; a >>= 1, b >>= 1) {
		if ( a & 1) { chmax(ret, seg[a]); ++a; }
		if (~b & 1) { chmax(ret, seg[b]); --b; }
	}
	return ret;
}

int main() {
	int i;
	
	K = in();
	M = in();
	D = in();
	A = in();
	N = in();
	for (i = 0; i < N; ++i) {
		T[i] = in();
		B[i] = in();
	}
	T[N] = M;
	B[N] = 0;
	
	xsLen = 0;
	xs[xsLen++] = K % D;
	xs[xsLen++] = M % D;
	for (i = 0; i < N; ++i) {
		xs[xsLen++] = T[i] % D;
	}
	sort(xs, xs + xsLen);
	xsLen = unique(xs, xs + xsLen) - xs;
	
	init(xsLen);
	update(getPos(K % D), 0);
	for (i = 0; i <= N; ++i) {
		int pos = getPos(T[i] % D);
		Int tmp = -INF;
		chmax(tmp, rangeMax(0, pos - 1) - A);
		chmax(tmp, rangeMax(pos, xsLen - 1));
		tmp += B[i];
		update(pos, tmp);
		if (i == N) {
			Int ans = tmp - (M / D - K / D) * A;
			printf("%lld\n", ans);
		}
	}
	
	return 0;
}

