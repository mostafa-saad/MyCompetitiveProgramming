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

typedef long long Int;

const int LIM_N = 200000;
const int INF = 1001001001;

struct Point {
	int x, y;
	friend ostream &operator<<(ostream &os, const Point &a) {
		return os << "(" << a.x << ", " << a.y << ")";
	}
};
bool cmpX(const Point &a, const Point &b) {
	return (a.x < b.x);
}
bool cmpY(const Point &a, const Point &b) {
	return (a.y < b.y);
}

int N;
Point P[LIM_N + 10];

//	increasing order of y
int lefbotLen, leftopLen, rigbotLen, rigtopLen;
Point lefbot[LIM_N + 10], leftop[LIM_N + 10], rigbot[LIM_N + 10], rigtop[LIM_N + 10];

Int solve(int lefbotU, int lefbotV, int leftopU, int leftopV, int rigbotU, int rigbotV, int rigtopU, int rigtopV) {
	Int ret = 0;
	int i, j, k, l, m;
	lefbotLen = 0;
	leftopLen = 0;
	rigbotLen = 0;
	rigtopLen = 0;
	for (i = lefbotV; i-- > lefbotU; ) {
		if (lefbotLen == 0 || lefbot[lefbotLen - 1].x < P[i].x) {
			lefbot[lefbotLen++] = P[i];
		}
	}
	reverse(lefbot, lefbot + lefbotLen);
	for (j = leftopU; j < leftopV; ++j) {
		if (leftopLen == 0 || leftop[leftopLen - 1].x < P[j].x) {
			leftop[leftopLen++] = P[j];
		}
	}
	for (k = rigbotV; k-- > rigbotU; ) {
		if (rigbotLen == 0 || rigbot[rigbotLen - 1].x > P[k].x) {
			rigbot[rigbotLen++] = P[k];
		}
	}
	reverse(rigbot, rigbot + rigbotLen);
	for (l = rigtopU; l < rigtopV; ++l) {
		if (rigtopLen == 0 || rigtop[rigtopLen - 1].x > P[l].x) {
			rigtop[rigtopLen++] = P[l];
		}
	}
	for (j = leftopLen, k = 0, l = rigtopLen, m = rigtopLen, i = 0; i < lefbotLen; ++i) {
		/*	
			leftop[j - 1].x < lefbot[i].x < leftop[j].x
			rigbot[k - 1].y < lefbot[i].y < rigbot[k].y
			rigtop[l - 1].y < leftop[j].y < rigtop[l].y
			rigtop[m].x < rigbot[k].x < rigtop[m - 1].x
		*/
		for (; j > 0 && leftop[j - 1].x > lefbot[i].x; --j);
		for (; k < rigbotLen && rigbot[k].y < lefbot[i].y; ++k);
		for (; l > 0 && rigtop[l - 1].y > ((j < leftopLen) ? leftop[j].y : INF); --l);
		for (; m > 0 && rigtop[m - 1].x < ((k < rigbotLen) ? rigbot[k].x : INF); --m);
		ret += max(l - m, 0);
	}
	return ret;
}

Int solve(int lefU, int lefV, int rigU, int rigV) {
	Int ret = 0;
	if (lefV - lefU >= 1 && rigV - rigU >= 1) {
		int half = ((lefV - lefU) + (rigV - rigU)) / 2;
		int lefW = lefU, rigW = rigU;
		for (; half--; ) {
			(lefW < lefV && (rigW == rigV || P[lefW].y < P[rigW].y)) ? ++lefW : ++rigW;
		}
		ret += solve(lefU, lefW, rigU, rigW);
		ret += solve(lefW, lefV, rigW, rigV);
		ret += solve(lefU, lefW, lefW, lefV, rigU, rigW, rigW, rigV);
	}
	return ret;
}

Int solve(int U, int V) {
	Int ret = 0;
	if (V - U >= 2) {
		int W = (U + V) / 2;
		ret += solve(U, W);
		ret += solve(W, V);
		ret += solve(U, W, W, V);
		inplace_merge(P + U, P + W, P + V, cmpY);
	}
	return ret;
}

int main() {
	int i;
	
	for (; ~scanf("%d", &N); ) {
		for (i = 0; i < N; ++i) {
			scanf("%d%d", &P[i].x, &P[i].y);
		}
		sort(P, P + N, cmpX);
		Int res = solve(0, N);
		printf("%lld\n", res);
	}
	
	return 0;
}

