/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Konewka                                       *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O((n + q) log n)                              *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
using namespace std;

const int MAXN = 1<<19;
const int INF = 2000000000;

int N, K, treeH[2*MAXN], maxTreeH[2*MAXN], fromMaxTreeH[2*MAXN], treeF[MAXN];

void TreeHModify(int a, int b, int x) {
	a += MAXN;
	b += MAXN;

	treeH[a] += x;
	maxTreeH[a] = treeH[a];
	fromMaxTreeH[a] = a-MAXN;
	if (a != b) {
		treeH[b] += x;
		maxTreeH[b] = treeH[b];
		fromMaxTreeH[b] = b-MAXN;
	}

	while (a/2 != b/2) {
		if (a%2 == 0) {
			treeH[a+1] += x;
			maxTreeH[a+1] = max(maxTreeH[2*(a+1)], maxTreeH[2*(a+1)+1]) + treeH[a+1];
			fromMaxTreeH[a+1] = (maxTreeH[2*(a+1)] >= maxTreeH[2*(a+1)+1] ? fromMaxTreeH[2*(a+1)] : fromMaxTreeH[2*(a+1)+1]);
		}
		if (b%2 == 1) {
			treeH[b-1] += x;
			maxTreeH[b-1] = max(maxTreeH[2*(b-1)], maxTreeH[2*(b-1)+1]) + treeH[b-1];
			fromMaxTreeH[b-1] = (maxTreeH[2*(b-1)] >= maxTreeH[2*(b-1)+1] ? fromMaxTreeH[2*(b-1)] : fromMaxTreeH[2*(b-1)+1]);
		}
		a /= 2;
		b /= 2;
		maxTreeH[a] = max(maxTreeH[2*a], maxTreeH[2*a+1]) + treeH[a];
		maxTreeH[b] = max(maxTreeH[2*b], maxTreeH[2*b+1]) + treeH[b];
		fromMaxTreeH[a] = (maxTreeH[2*a] >= maxTreeH[2*a+1] ? fromMaxTreeH[2*a] : fromMaxTreeH[2*a+1]);
		fromMaxTreeH[b] = (maxTreeH[2*b] >= maxTreeH[2*b+1] ? fromMaxTreeH[2*b] : fromMaxTreeH[2*b+1]);
	}

	while (a > 1) {
		a /= 2;
		maxTreeH[a] = max(maxTreeH[2*a], maxTreeH[2*a+1]) + treeH[a];
		fromMaxTreeH[a] = (maxTreeH[2*a] >= maxTreeH[2*a+1] ? fromMaxTreeH[2*a] : fromMaxTreeH[2*a+1]);
	}
}

int Magic(int x) {
	return x&(-x);
}

void TreeFModify(int p, int x) {
	while (p < MAXN) {
		treeF[p] += x;
		p += Magic(p);
	}
}

int TreeFPrefSum(int p) {
	int result = 0;
	while (p > 0) {
		result += treeF[p];
		p -= Magic(p);
	}
	return result;
}

int TreeFSum(int a, int b) {
	return TreeFPrefSum(b)-TreeFPrefSum(a-1);
}

void RecomputeTrees() {
	while (maxTreeH[1] >= K) {
		TreeFModify(fromMaxTreeH[1], +1);
		TreeHModify(fromMaxTreeH[1], fromMaxTreeH[1], -INF);
	}
}



void inicjuj(int n, int k, int *D) {
	N = n;
	K = k;

	for (int i = 0; i < N; i++) {
		TreeHModify(i+1, i+1, +D[i]);
		RecomputeTrees();
	}
}

void podlej(int a, int b) {
	TreeHModify(a+1, b+1, +1);

	RecomputeTrees();
}

int dojrzale(int a, int b) {
	return TreeFSum(a+1, b+1);
}
