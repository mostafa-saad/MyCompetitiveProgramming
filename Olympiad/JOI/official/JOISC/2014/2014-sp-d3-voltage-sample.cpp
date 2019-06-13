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

const int LIM_N = 100000;
const int LIM_M = 200000;

int N, M;
int A[LIM_M + 10], B[LIM_M + 10];

int m, ptr[LIM_N + 10], next[LIM_M * 2 + 10], zu[LIM_M * 2 + 10];
int ips[LIM_N + 10], depths[LIM_N + 10];
int badCnt, goodCnt;
int bad[LIM_N + 10], good[LIM_N + 10];

void dfs0(int u, int ip, int depth) {
	int i, v;
	ips[u] = ip;
	depths[u] = depth;
	for (i = ptr[u]; ~i; i = next[i]) if ((i ^ 1) != ip) {
		v = zu[i];
		if (!~depths[v]) {
			//	tree edge
			dfs0(v, i, depth + 1);
		} else if (depths[u] > depths[v]) {
			//	back edge
			if (depths[u] % 2 == depths[v] % 2) {
				++badCnt;
				++bad[u];
				--bad[v];
			} else {
				++goodCnt;
				++good[u];
				--good[v];
			}
		}
	}
}

void dfs1(int u, int ip) {
	int i, v;
	for (i = ptr[u]; ~i; i = next[i]) if ((i ^ 1) != ip) {
		v = zu[i];
		if (i == ips[v]) {
			dfs1(v, i);
			bad[u] += bad[v];
			good[u] += good[v];
		}
	}
}

int main() {
	int i, u;
	
	for (; ~scanf("%d%d", &N, &M); ) {
		for (i = 0; i < M; ++i) {
			scanf("%d%d", &A[i], &B[i]);
			--A[i];
			--B[i];
		}
		m = 0;
		memset(ptr, ~0, N * 4);
		for (i = 0; i < M; ++i) {
			next[m] = ptr[A[i]]; ptr[A[i]] = m; zu[m] = B[i]; ++m;
			next[m] = ptr[B[i]]; ptr[B[i]] = m; zu[m] = A[i]; ++m;
		}
		
		memset(ips, ~0, N * 4);
		memset(depths, ~0, N * 4);
		badCnt = 0;
		goodCnt = 0;
		memset(bad, 0, N * 4);
		memset(good, 0, N * 4);
		for (u = 0; u < N; ++u) if (!~depths[u]) {
			dfs0(u, -1, 0);
		}
		for (u = 0; u < N; ++u) if (!~ips[u]) {
			dfs1(u, -1);
		}
		
		int ans = 0;
		//	tree edge
		for (u = 0; u < N; ++u) if (~ips[u]) {
			if (bad[u] == badCnt && good[u] == 0) {
				++ans;
			}
		}
		//	back edge
		if (badCnt == 1) {
			++ans;
		}
		printf("%d\n", ans);
	}
	
	return 0;
}

