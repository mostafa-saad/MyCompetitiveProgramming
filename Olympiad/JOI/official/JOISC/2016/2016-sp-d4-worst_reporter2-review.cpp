#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 200200;
const int INF = 1e9;

// range add - range min
struct segtree
{
	static const int DEPTH = 18;
	static const int N = 1 << DEPTH;

	int dsum[2 * N];
	pair<int, int> rmin[2 * N];

	void init()
	{
		fill(dsum, dsum + 2 * N, 0);
		for (int i = 0; i < N; ++i) rmin[i + N] = make_pair(0, i);
		for (int i = N - 1; i >= 1; --i) rmin[i] = min(rmin[2 * i], rmin[2 * i + 1]);
	}
	void add(int p, int qL, int qR, int depth, int v)
	{
		int pL = p << depth, pR = (p + 1) << depth;
		if (qR <= pL || pR <= qL) return;
		if (qL <= pL && pR <= qR) {
			dsum[p] += v;
			rmin[p].first += v;
			return;
		}
		add(p * 2, qL, qR, depth - 1, v);
		add(p * 2 + 1, qL, qR, depth - 1, v);
		rmin[p] = min(rmin[p * 2], rmin[p * 2 + 1]);
		rmin[p].first += dsum[p];
	}
	void add(int qL, int qR, int v)
	{
		add(1, qL + N, qR + N, DEPTH, v);
	}
	pair<int, int> query(int p, int qL, int qR, int depth)
	{
		int pL = p << depth, pR = (p + 1) << depth;
		if (qR <= pL || pR <= qL) return make_pair(INF, INF);
		if (qL <= pL && pR <= qR) return rmin[p];

		dsum[p * 2] += dsum[p];
		rmin[p * 2].first += dsum[p];
		dsum[p * 2 + 1] += dsum[p];
		rmin[p * 2 + 1].first += dsum[p];
		dsum[p] = 0;

		return min(query(p * 2, qL, qR, depth - 1), query(p * 2 + 1, qL, qR, depth - 1));
	}
	pair<int, int> query(int qL, int qR)
	{
		return query(1, qL + N, qR + N, DEPTH);
	}
};

int N, A[MAXN], B[MAXN], C[MAXN], D[MAXN];
set<int> unmet[MAXN];
set<int> unusedA, unusedC;
segtree seg;

long long total_op_size = 0;

void connect(int a, int c)
{
	int ai = lower_bound(D, D + N, B[a]) - D;
	seg.add(ai, c, -1);
	total_op_size += c - ai;
}

void dissolve(int X)
{
	for (;;) {
		auto m = seg.query(0, X);
		if (m.first != 0) break;
		while (unusedC.size() > 0 && *(unusedC.begin()) <= m.second) {
			int a = *(unusedA.begin());
			int c = *(unusedC.begin());

			unusedA.erase(unusedA.begin());
			unusedC.erase(unusedC.begin());
			unmet[A[a]].erase(a);
			connect(a, c);
		}
		seg.add(m.second, m.second + 1, INF);
	}
}

int main()
{
	scanf("%d", &N);
	for (int i = N - 1; i >= 0; --i) scanf("%d%d", A + i, B + i);
	for (int i = N - 1; i >= 0; --i) scanf("%d%d", C + i, D + i);
	seg.init();

	vector<pair<int, int> > eves;
	for (int i = 0; i < N; ++i) {
		eves.push_back({ B[i], i });
		eves.push_back({ D[i], i + N });
	}
	sort(eves.begin(), eves.end());

	int cnt = 0, d_idx = 0;
	int ret = N;
	for (auto p : eves) {
		if (p.second < N) {
			unmet[A[p.second]].insert(p.second);
			unusedA.insert(p.second);
			++cnt;
		} else {
			--cnt;
			p.second -= N;
			seg.add(p.second, p.second + 1, cnt);
			if (unmet[C[p.second]].size() > 0) {
				auto it = unmet[C[p.second]].end();
				--it;
				int a = *it;
				unmet[C[p.second]].erase(it);
				unusedA.erase(a);
				connect(a, p.second);
				--ret;
			} else {
				unusedC.insert(p.second);
			}

			dissolve(++d_idx);
		}
	}

	printf("%d\n", ret);
	return 0;
}
