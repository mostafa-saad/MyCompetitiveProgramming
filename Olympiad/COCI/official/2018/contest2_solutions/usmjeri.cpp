#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair <int, int> pii;

const int MAXN = 300005;
const int LOG = 19;
const int MOD = 1000000007;

int N, M;
vector <int> E[MAXN];
vector <pii> adj[MAXN];
int anc[MAXN][LOG];
int depth[MAXN];
int high[MAXN];
int clr[MAXN];

void load() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i < N; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		E[a].push_back(b);
		E[b].push_back(a);
	}
}

void init(int x, int p) {
	anc[x][0] = p;
	depth[x] = depth[p] + 1;
	for (auto it : E[x])
		if (it != p)
			init(it, x);
}

int lca(int x, int y) {
	if (depth[x] < depth[y])
		swap(x, y);
	int diff = depth[x] - depth[y];
	for (int i = LOG - 1; i >= 0; i--)
		if (diff >> i & 1)
			x = anc[x][i];
	if (x == y)
		return x;
	for (int i = LOG - 1; i >= 0; i--)
		if (anc[x][i] != anc[y][i]) {
			x = anc[x][i];
			y = anc[y][i];
		}
	return anc[x][0];
}

void add_edge(int a, int b, int c) {
	adj[a].push_back({b, c});
	adj[b].push_back({a, c});
}

int connect(int x, int p) {
	for (auto it : E[x])
		if (it != p) {
			int tmp = connect(it, x);
			high[x] = min(high[x], tmp);
			if (tmp < depth[x])
				add_edge(it, x, 0);
		}
	return high[x];
}

bool dfs(int x, int c) {
	if (clr[x] != -1)
		return clr[x] == c;
	clr[x] = c;
	for (auto it : adj[x])
		if (!dfs(it.first, c ^ it.second))
			return false;
	return true;
}

int solve() {
	memset(clr, -1, sizeof clr);
	
	init(1, 0);
	
	for (int j = 1; j < LOG; j++)
		for (int i = 1; i <= N; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
	
	for (int i = 1; i <= N; i++)
		high[i] = depth[i];
			
	while (M--) {
		int a, b;
		scanf("%d%d", &a, &b);
		int c = lca(a, b);
		high[a] = min(high[a], depth[c]);
		high[b] = min(high[b], depth[c]);
		if (a != c && b != c)
			add_edge(a, b, 1);
	}
	
	connect(1, 0);
	
	int sol = 1;
	for (int i = 2; i <= N; i++)
		if (clr[i] == -1) {
			if (!dfs(i, 0))
				return 0;
			sol = 2 * sol % MOD;
		}
	
	return sol;
}

int main() {
	load();
	printf("%d\n", solve());
	return 0;
}
