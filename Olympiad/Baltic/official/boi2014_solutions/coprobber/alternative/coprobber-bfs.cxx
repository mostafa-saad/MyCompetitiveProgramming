#include "coprobber.h"
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

typedef tuple<int, int, int> Position;

const int COP = 0, ROBBER = 1;
int LeftToWin[2][MAX_N][MAX_N];
int NextPos[MAX_N][MAX_N];

int start(int N, bool A[MAX_N][MAX_N]) {
	for (int r = 0; r < N; r++) {
		int degree = count(A[r], A[r] + N, true);
		for (int c = 0; c < N; c++)
			if (c != r) {
				LeftToWin[COP][c][r] = 1;
				LeftToWin[ROBBER][c][r] = degree;
			}
	}

	queue<Position> q;
	for (int i = 0; i < N; i++) {
		q.push(Position(COP, i, i));
		q.push(Position(ROBBER, i, i));
	}
	
	int numProcessed = 0;
	while (!q.empty()) {
		int t, c, r;
		tie(t, c, r) = q.front();
		q.pop();
		numProcessed++;
		if (t == COP) {
			for (int n = 0; n < N; n++)
				if (A[r][n] && LeftToWin[ROBBER][c][n]) {
					LeftToWin[ROBBER][c][n]--;
					if (LeftToWin[ROBBER][c][n] == 0)
						q.push(Position(ROBBER, c, n));
				}
		} else if (t == ROBBER) {
			for (int n = 0; n < N; n++)
				if ((c == n || A[c][n]) && LeftToWin[COP][n][r]) {
					LeftToWin[COP][n][r] = 0;
					q.push(Position(COP, n, r));
					NextPos[n][r] = c;
				}
		}
	}
	
	return numProcessed == 2*N*N ? 0 : -1;
}

int cop = 0;

int nextMove(int robber) {
	cop = NextPos[cop][robber];
	return cop;
}
