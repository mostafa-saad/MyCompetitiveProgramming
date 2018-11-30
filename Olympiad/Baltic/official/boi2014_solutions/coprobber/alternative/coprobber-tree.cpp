#include "coprobber.h"

int cop = 0;
int N;
bool (*A)[MAX_N];

int start(int n, bool a[MAX_N][MAX_N]) {
	N = n;
	A = a;
	return 0;
}

int dist(int v, int to, int parent) {
	if (v == to)
		return 0;
	for (int j = 0; j < N; j++)
		if (j != parent && A[v][j]) {
			int d = dist(j, to, v);
			if (d != -1)
				return 1 + d;
		}
	return -1;
}

int nextMove(int robber) {
	int d = dist(cop, robber, -1);
	for (int j = 0; j < N; j++)
		if (A[cop][j] && dist(j, robber, -1) < d)
			return cop = j;
}
