/*
	Problem: Modern Mansion
	Solution by: Kazuhiro Hosaka
	
	O(K log K)
	Dijkstra: |V| <= 2 (K + 2), |E| <= 3 |V|
*/

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

#define MAX_K 1000010
#define MAX_V 2000010

const Int INF = 1001001001001001001LL;

Int M, N;
int K;
Int X[MAX_K], Y[MAX_K];
int L, S, T;
pair< pair<Int,Int>,int > XYs[MAX_K], YXs[MAX_K];

int V;
int deg[MAX_V];
pair<Int,int> graph[MAX_V][3];

void addEdge(int u, int v, Int c) {
	graph[u][deg[u]++] = mp(c, v);
	graph[v][deg[v]++] = mp(c, u);
}

bool visited[MAX_V];
Int dist[MAX_V];

int main() {
	int i, j, l;
	int u, v;
	Int c, cc;
	
	scanf("%lld%lld%d", &M, &N, &K);
	for (i = 0; i < K; ++i) {
		scanf("%lld%lld", &X[i], &Y[i]);
	}
	
	L = K;
	for (i = 0; i < K; ++i) {
		if (X[i] == 1 && Y[i] == 1) {
			S = i;
			break;
		}
	}
	if (i == K) {
		S = L;
		X[L] = 1;
		Y[L] = 1;
		++L;
	}
	for (i = 0; i < K; ++i) {
		if (X[i] == M && Y[i] == N) {
			T = i;
			break;
		}
	}
	if (i == K) {
		T = L;
		X[L] = M;
		Y[L] = N;
		++L;
	}
	
	V = L * 2;
	for (i = 0; i < K; ++i) {
		addEdge(i * 2 + 0, i * 2 + 1, 1);
	}
	for (i = 0; i < L; ++i) {
		XYs[i] = mp(mp(X[i], Y[i]), i);
		YXs[i] = mp(mp(Y[i], X[i]), i);
	}
	sort(XYs, XYs + L);
	sort(YXs, YXs + L);
	for (l = 0; l < L - 1; ++l) {
		i = XYs[l    ].second;
		j = XYs[l + 1].second;
		if (X[i] == X[j]) {
			addEdge(i * 2 + 0, j * 2 + 0, Y[j] - Y[i]);
		}
	}
	for (l = 0; l < L - 1; ++l) {
		i = YXs[l    ].second;
		j = YXs[l + 1].second;
		if (Y[i] == Y[j]) {
			addEdge(i * 2 + 1, j * 2 + 1, X[j] - X[i]);
		}
	}
	
	typedef pair<Int,int> node;
	priority_queue< node,vector<node>,greater<node> > q;
	for (u = 0; u < V; ++u) {
		visited[u] = false;
		dist[u] = INF;
	}
	dist[S * 2 + 0] = 0;
	q.push(mp(0, S * 2 + 0));
	for (; !q.empty(); ) {
		c = q.top().first;
		u = q.top().second;
		q.pop();
		if (!visited[u]) {
			visited[u] = true;
			if (u / 2 == T) {
				printf("%lld\n", c);
				goto found;
			}
			for (i = 0; i < deg[u]; ++i) {
				cc = c + graph[u][i].first;
				v = graph[u][i].second;
				if (dist[v] > cc) {
					dist[v] = cc;
					q.push(mp(cc, v));
				}
			}
		}
	}
	puts("-1");
found:;
	
	return 0;
}

