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

Int Abs(Int r) { return (r < 0) ? -r : r; }

const int LIM_N = 100000;

int N;
int A[LIM_N + 10];
Int B[LIM_N + 10], C[LIM_N + 10], D[LIM_N + 10];

int vis[LIM_N + 10];

int main() {
	int u, v, w;
	
	N = in();
	for (u = 0; u < N; ++u) {
		A[u] = in() - 1;
		B[u] = in();
		C[u] = in();
		D[u] = in();
	}
	
	Int ans = 0;
	for (u = 0; u < N; ++u) {
		ans += B[u] * max(C[A[u]], D[A[u]]);
	}
	
	memset(vis, ~0, N << 2);
	for (u = 0; u < N; ++u) {
		for (v = u; !~vis[v]; v = A[v]) {
			vis[v] = u;
		}
		if (vis[v] == u) {
			bool good = 1;
			for (w = v; ; ) {
				if (C[A[w]] < D[A[w]]) {
					good = !good;
				}
				if ((w = A[w]) == v) break;
			}
			if (!good) {
				Int tmp = INF;
				for (w = v; ; ) {
					chmin(tmp, B[w] * Abs(C[A[w]] - D[A[w]]));
					if ((w = A[w]) == v) break;
				}
				ans -= tmp;
			}
		}
	}
	
	printf("%lld\n", ans);
	
	return 0;
}

