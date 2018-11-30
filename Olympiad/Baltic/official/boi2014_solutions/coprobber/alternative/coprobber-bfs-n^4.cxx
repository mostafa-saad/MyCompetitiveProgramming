#include "coprobber.h"
#include <queue>
#include <tuple>

using namespace std;

typedef tuple<int, int, int> Position;

const int COP = 0, ROBBER = 1;
bool CopWins[2][MAX_N][MAX_N];
int NextPos[MAX_N][MAX_N];

int start(int N, bool A[MAX_N][MAX_N]) {
	queue<Position> q;
	for (int i = 0; i < N; i++) {
		q.push(Position(COP, i, i));
		q.push(Position(ROBBER, i, i));
		CopWins[COP][i][i] = true;
		CopWins[ROBBER][i][i] = true;
	}
	
	while (!q.empty()) {
		int t, c, r;
		tie(t, c, r) = q.front();
		q.pop();
		if (t == COP) {
			for (int n = 0; n < N; n++)
				if (A[r][n] && !CopWins[ROBBER][c][n]) {
					bool all = true;
					for (int i = 0; i < N; i++)
						if (A[n][i] && !CopWins[COP][c][i])
							all = false;
					if (all) {
						CopWins[ROBBER][c][n] = true;
						q.push(Position(ROBBER, c, n));
					}
				}
		} else if (t == ROBBER) {
			for (int n = 0; n < N; n++)
				if ((c == n || A[c][n]) && !CopWins[COP][n][r]) {
					CopWins[COP][n][r] = true;
					NextPos[n][r] = c;
					q.push(Position(COP, n, r));
				}
		}
	}
	
	for (int c = 0; c < N; c++)
		for (int r = 0; r < N; r++)
			if (!CopWins[COP][c][r])
				return -1;
	return 0;
}

int cop = 0;

int nextMove(int robber) {
	cop = NextPos[cop][robber];
	return cop;
}
