// Author:	Adrian Kuegel
// Date: 	April 2nd, 2007
// Algorithm:	scanline + dijktra
// Complexity:	O(n^3 log n)

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <assert.h>
using namespace std;

#define MAXN 200

struct rectangle {
	int x1, y1, x2, y2;
}r[MAXN];

bool operator<(const rectangle &a, const rectangle &b) {
	return a.x1 < b.x1;
}

struct edge {
	int dest, cost;
	edge(int d, int c) {
		dest = d;
		cost = c;
	}
};

bool operator<(const edge &a, const edge &b) {
	return a.cost > b.cost;
}

typedef vector<edge> VE;

int n;
int px[MAXN*4], py[MAXN*4], ind[MAXN*4];

bool byx(int a, int b) {
	return px[a] < px[b];
}

bool is_inner_point(int x, int y) {
	for (int i=0; i<n; ++i)
		if (x > r[i].x1 && x < r[i].x2 && y > r[i].y1 && y < r[i].y2)
			return 1;
	return 0;
}

VE adj[MAXN*8];
int len[MAXN*8];

int main() {
	freopen("fence.in","r",stdin);
	freopen("fence.out","w",stdout);

	// read input
	scanf("%d",&n);
	assert(n >= 1 && n <= MAXN);
	for (int i=0; i<n; ++i) {
		scanf("%d %d %d %d",&r[i].x1,&r[i].y1,&r[i].x2,&r[i].y2);
		assert(0 <= r[i].x1 && r[i].x1 < r[i].x2 && r[i].x2 <= 10000);
		assert(0 <= r[i].y1 && r[i].y1 < r[i].y2 && r[i].y2 <= 10000);
	}

	// remember top left corner of the main mansion
	int X = r[0].x1;
	int Y = r[0].y1;
	sort(r, r+n);

	// determine corners which are not inside of any rectangle
	int N = 0;
	for (int i=0; i<n; ++i) {
		if (!is_inner_point(r[i].x1,r[i].y1)) {
			px[N] = r[i].x1;
			py[N++] = r[i].y1;
		}
		if (!is_inner_point(r[i].x2,r[i].y1)) {
			px[N] = r[i].x2;
			py[N++] = r[i].y1;
		}
		if (!is_inner_point(r[i].x1,r[i].y2)) {
			px[N] = r[i].x1;
			py[N++] = r[i].y2;
		}
		if (!is_inner_point(r[i].x2,r[i].y2)) {
			px[N] = r[i].x2;
			py[N++] = r[i].y2;
		}
	}

	// sort points (px, py) indirect by x
	for (int i=0; i<N; ++i)
		ind[i] = i;
	sort(ind, ind+N, byx);

	// use a scanline algorithm to determine edges
	// this step takes O(n^2) time
	for (int ii=0; ii<N; ++ii) {
		int i = ind[ii];
		int j = 0;
		int maxy = 10000, miny = 0; // [miny, maxy] is the current empty range
		while(j < n && r[j].x1 < px[i]) {
			if (r[j].x2 > px[i]) {
				if (r[j].y1 < py[i] && r[j].y2 > py[i]) {
					// this should not happen, otherwise (px[i],py[i]) would be inside r[j]
					assert(0);
				}
				if (r[j].y1 >= py[i])
					maxy = min(maxy, r[j].y1);
				else if (r[j].y2 <= py[i])
					miny = max(miny, r[j].y2);
			}
			++j;
		}
		for (int jj=ii+1; jj<N; ++jj) {
			int k = ind[jj];
			// first update empty range
			while(j < n && r[j].x1 < px[k]) {
				if (r[j].y1 < py[i] && r[j].y2 > py[i]) {
					miny = r[j].y2;
					maxy = r[j].y1;
				}
				else if (r[j].y1 >= py[i])
					maxy = min(maxy, r[j].y1);
				else if (r[j].y2 <= py[i])
					miny = max(miny, r[j].y2);
				++j;
			}
			if (maxy < miny)
				break;
			if (py[k] >= miny && py[k] <= maxy) {
				int from = i;
				int to = k;
//				printf("empty between (%d, %d) and (%d, %d)\n",px[from],py[from],px[to],py[to]);
				int len = abs(px[to]-px[from]) + abs(py[to]-py[from]);
				// check if we need to change layer
				if (px[from] <= X && px[to] > X && py[from] <= Y && py[to] <= Y) {
					adj[from].push_back( edge(to+N,len) );
					adj[from+N].push_back( edge(to,len) );
					adj[to].push_back( edge(from+N,len) );
					adj[to+N].push_back( edge(from,len) );
				}
				// otherwise keep the same layer
				else {
					adj[from].push_back( edge(to,len) );
					adj[from+N].push_back( edge(to+N,len) );
					adj[to].push_back( edge(from, len) );
					adj[to+N].push_back( edge(from+N, len) );
				}
			}
		}
	}

	// now run dijkstra from each node of first layer
	const int INFINITY = 2000000000;
	int best = INFINITY;
	for (int i=0; i<N; ++i) {
		for (int j=0; j<2*N; ++j)
			len[j] = INFINITY;
		priority_queue<edge> Q;
		Q.push( edge(i, 0) );
		len[i] = 0;
		while(!Q.empty()) {
			edge E = Q.top();
			Q.pop();
			if (E.cost >= best)
				break;
			if (E.dest == i+N) {
				best = E.cost;
				break;
			}
			if (E.cost > len[E.dest])
				continue;
			for (VE::iterator it=adj[E.dest].begin(); it!=adj[E.dest].end(); ++it) {
				edge next(it->dest, E.cost + it->cost);
				if (next.cost < len[it->dest]) {
					len[it->dest] = next.cost;
					Q.push(next);
				}
			}
		}
	}
	printf("%d\n",best);
	return 0;
}
