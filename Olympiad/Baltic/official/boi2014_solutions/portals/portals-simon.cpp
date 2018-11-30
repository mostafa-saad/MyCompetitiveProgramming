/**
 * Official solution for task PORTALS.
 *
 * Performs a breadth-first search starting from the blocked tiles, to find the distance from
 * each tile to its nearest wall, and then uses Dijkstra's algorithm on the derived graph
 * where each tile has outgoing edges to its adjacent tiles (of weight 1) and to the tiles
 * it can reach by portal (of weight 'distance to nearest wall').
 *
 * Runs in O(N).
 *
 * Author: Simon Lindholm
 */
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

template <class T, int N>
struct ar {
	T v[N];
	T& operator[](int x) { return v[x]; }
};

int main() {
	const int X[4] = {-1, 1, 0, 0};
	const int Y[4] = {0, 0, -1, 1};

	int R, C;
	cin >> R >> C;
	vector<string> map(R+2, string(C+2, '#'));
	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j)
			cin >> map[i][j];
	}
	R += 2;
	C += 2;

	// Indices of start and end positions.
	int startx, starty, endx, endy;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (map[i][j] == 'S')
				starty = i, startx = j;
			if (map[i][j] == 'C')
				endy = i, endx = j;
		}
	}

	// Find distances to the nearest wall.
	vector<vector<int> > distToWall(R, vector<int>(C, -1));
	{
		queue<pair<int, int> > q;
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				if (map[i][j] == '#') {
					q.push(make_pair(i, j));
					distToWall[i][j] = 0;
				}
			}
		}
		while (!q.empty()) {
			pair<int, int> pa = q.front();
			q.pop();
			int y = pa.first, x = pa.second;
			for (int d = 0; d < 4; ++d) {
				int nx = x + X[d], ny = y + Y[d];
				if (0 <= nx && 0 <= ny && nx < C && ny < R && distToWall[ny][nx] == -1) {
					distToWall[ny][nx] = distToWall[y][x] + 1;
					q.push(make_pair(ny, nx));
				}
			}
		}
	}

	// Find the square you see when standing at a given square and looking in a
	// given direction.
	vector<vector<ar<pair<int, int>, 4> > > seen(R, vector<ar<pair<int, int>, 4> >(C));
	{
		int last;
		for (int y = 0; y < R; ++y) {
			for (int x = 0; x < C; ++x) {
				if (map[y][x] == '#') last = x;
				seen[y][x][0] = make_pair(y, last+1);
			}
			for (int x = C; x --> 0; ) {
				if (map[y][x] == '#') last = x;
				seen[y][x][1] = make_pair(y, last-1);
			}
		}
		for (int x = 0; x < C; ++x) {
			for (int y = 0; y < R; ++y) {
				if (map[y][x] == '#') last = y;
				seen[y][x][2] = make_pair(last+1, x);
			}
			for (int y = R; y --> 0; ) {
				if (map[y][x] == '#') last = y;
				seen[y][x][3] = make_pair(last-1, x);
			}
		}
	}

	// Finally, solve the problem with Dijkstra's algorithm.
	vector<vector<int> > dists(R, vector<int>(C, -1));
	{
		const int MaxDist = R * C;
		vector<vector<pair<int, int> > > q(MaxDist + 1);
		q[0].push_back(make_pair(starty, startx));
		for (int dist = 0; dist <= MaxDist; ++dist) {
			vector<pair<int, int> >& dq = q[dist];
			for (int i = 0; i < (int)dq.size(); ++i) {
				pair<int, int> pa = dq[i];
				int y = pa.first, x = pa.second;
				if (dists[y][x] != -1)
					continue;
				dists[y][x] = dist;

				// Move to an adjacent square.
				for (int d = 0; d < 4; ++d) {
					int nx = x + X[d], ny = y + Y[d];
					if (map[ny][nx] != '#' && dist+1 <= MaxDist)
						q[dist+1].push_back(make_pair(ny, nx));
				}

				// Shoot a portal
				for (int d = 0; d < 4; ++d) {
					pair<int, int> pa2 = seen[y][x][d];
					int ndist = dist + distToWall[y][x];
					if (ndist <= MaxDist)
						q[ndist].push_back(pa2);
				}
			}
		}
	}

	cout << dists[endy][endx] << endl;
	return 0;
}
