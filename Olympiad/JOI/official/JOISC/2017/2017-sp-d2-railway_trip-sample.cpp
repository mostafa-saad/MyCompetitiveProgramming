#include <cstdio>
#include <algorithm>
#include <vector>

static const int MAXN = 100000;
static const int DEPTH = 20;

using namespace std;

struct segtree
{
	static const int kDepth = 17;
	static const int kSize = 1 << kDepth;
	pair<int, int> *data;

	segtree() {
		data = new pair<int, int>[2 * kSize];
	}
	void init(int len, int* v)
	{
		for (int i = 0; i < len; ++i) data[kSize + i] = make_pair(v[i], -i);
		for (int i = len; i < kSize; ++i) data[kSize + i] = make_pair(-1, -i);
		for (int i = kSize - 1; i >= 1; --i) data[i] = max(data[i * 2], data[i * 2 + 1]);
	}
	pair<int, int> query(int l, int r)
	{
		l += kSize;
		r += kSize;
		pair<int, int> ret(-1, -1);
		while (l < r) {
			if (l & 1) ret = max(ret, data[l++]);
			if (r & 1) ret = max(ret, data[--r]);
			l >>= 1; r >>= 1;
		}
		ret.second = -ret.second;
		return ret;
	}
};

int N, K, Q;
int L[MAXN];
vector<int> child[MAXN * 2]; int dep[MAXN * 2], ci[MAXN * 2];
int nlast, root;
int wnode[MAXN];
segtree lst;
bool nonstop;

int parent[MAXN * 6][DEPTH], weight[MAXN * 6][DEPTH];

int build(int l, int r)
{
	if (r - l == 1) {
		return wnode[l] = nlast++;
	}
	auto tmp = lst.query(l + 1, r);
	int bp = tmp.first;
	vector<int> sep;
	sep.push_back(l);
	sep.push_back(tmp.second);
	for (;;) {
		auto q = lst.query(sep.back() + 1, r);
		if (q.first != bp) break;
		sep.push_back(q.second);
	}
	sep.push_back(r);

	int ret = nlast++;
	for (int i = 0; i < (int)sep.size() - 1; ++i) {
		child[ret].push_back(build(sep[i], sep[i + 1]));
	}
	return ret;
}
inline int forest_vtx(int p, int mode)
{
	// mode 0: (x+1, x), 1: (x, x), 2: (x, x+1)
	return p * 3 + mode;
}
void assign_parent(int p, int par, int tl, int tr)
{
	tl = min(tl, tr + 1);
	tr = min(tr, tl + 1);
	if (tl == tr + 1) {
		parent[p][0] = forest_vtx(par, 0);
		weight[p][0] = tr;
	} else if (tl == tr) {
		parent[p][0] = forest_vtx(par, 1);
		weight[p][0] = tr;
	} else {
		parent[p][0] = forest_vtx(par, 2);
		weight[p][0] = tl;
	}
}
void gen_forest(int p)
{
	for (int p2 = p * 3; p2 < (p + 1) * 3; ++p2) {
		for (int i = 1; i < DEPTH; ++i) {
			if (parent[p2][i - 1] == -1) {
				parent[p2][i] = -1;
				weight[p2][i] = weight[p2][i - 1];
			} else {
				parent[p2][i] = parent[parent[p2][i - 1]][i - 1];
				weight[p2][i] = weight[p2][i - 1] + weight[parent[p2][i - 1]][i - 1];
			}
		}
	}
	for (int i = 0; i < child[p].size(); ++i) {
		int q = child[p][i];
		int j = (int)child[p].size() - i - 1;
		dep[q] = dep[p] + 1;
		ci[q] = i;
		assign_parent(forest_vtx(q, 0), p, 1 + i, j);
		assign_parent(forest_vtx(q, 1), p, i, j);
		assign_parent(forest_vtx(q, 2), p, i, j + 1);
		gen_forest(q);
	}
}
pair<int, int> descend(int p, int d)
{
	int dist = 0;
	for (int i = DEPTH - 1; i >= 0; --i) if (d & (1 << i)) {
		dist += weight[p][i];
		p = parent[p][i];
	}
	return{ p, dist };
}
int solve(int a, int b)
{
	if (b == a + 1) return 1;
	int p = forest_vtx(wnode[a], 2);
	int q = forest_vtx(wnode[b - 1], 0);
	int dist = 0;
	if (dep[p / 3] < dep[q / 3]) {
		auto tmp = descend(q, dep[q / 3] - dep[p / 3]);
		dist = tmp.second;
		q = tmp.first;
	} else if (dep[p / 3] > dep[q / 3]) {
		auto tmp = descend(p, dep[p / 3] - dep[q / 3]);
		dist = tmp.second;
		p = tmp.first;
	}
	for (int i = DEPTH - 1; i >= 0; --i) {
		if (parent[p][i] / 3 != parent[q][i] / 3) {
			dist += weight[p][i] + weight[q][i];
			p = parent[p][i];
			q = parent[q][i];
		}
	}
	int ret = N;
	ret = min(ret, dist + ci[q / 3] - ci[p / 3] - 1 + (p % 3 == 2 ? 1 : 0) + (q % 3 == 0 ? 1 : 0));
	if (parent[p][0] / 3 != root || nonstop) {
		ret = min(ret, dist + ci[p / 3] + ((int)child[parent[p][0] / 3].size() - ci[q / 3] - 1) + (p % 3 == 0 ? 1 : 0) + (q % 3 == 2 ? 1 : 0) + 1);
	}
	return ret;
}
int main()
{
	scanf("%d%d%d", &N, &K, &Q);
	nonstop = true;
	for (int i = 0; i < N; ++i) {
		scanf("%d", L + i);
		--L[i];
		if (i != 0 && i != N - 1 && L[i] == K - 1) nonstop = false;
	}
	
	nlast = 0;
	lst.init(N, L);
	root = build(0, N - 1);
	dep[root] = 0; ci[root] = 0;
	for (int i = 0; i < 3; ++i) {
		parent[root * 3 + i][0] = -1;
		weight[root * 3 + i][0] = 0;
	}
	gen_forest(root);

	for (int q = 0; q < Q; ++q) {
		int a, b;
		scanf("%d%d", &a, &b);
		--a; --b;
		if (a > b) swap(a, b);
		printf("%d\n", solve(a, b) - 1);
	}
	return 0;
}
