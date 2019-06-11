#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef long long i64;

const int MAXN = 500500;
const i64 INF = 1LL << 60LL;

template <class T>
struct RMQ
{
	static const int DEPTH = 20;
	static const int N = 1 << DEPTH;

	T val[2 * N];
	T TINF;

	RMQ(T TINF_) { TINF = TINF_; }

	void init()
	{
		for(int i = 0; i < 2 * N; i++) val[i] = TINF;
	}

	void init(T* iv, int sz)
	{
		for(int i = 0; i < sz; i++) val[i + N] = iv[i];
		for(int i = sz; i < N; i++) val[i + N] = TINF;

		for(int i = N-1; i >= 1; i--) val[i] = min(val[i*2], val[i*2+1]);
	}

	void init(vector<T> &iv)
	{
		int sz = iv.size();
		for(int i = 0; i < sz; i++) val[i + N] = iv[i];

		int L = N, R = N + sz;
		L >>= 1; R >>= 1;

		while(L < R) {
			for(int i = L; i < R; i++) val[i] = min(val[i*2], val[i*2+1]);
			L >>= 1; R >>= 1;
		}
	}

	void set_value(int p, T v)
	{
		p += N;
		val[p] = v;
		p >>= 1;

		while(p) {
			val[p] = min(val[p*2], val[p*2+1]);
			p >>= 1;
		}
	}

	T query(int L, int R)
	{
		T ret = TINF;
		L += N; R += N;
		while(L < R) {
			if(L & 1) ret = min(ret, val[L++]);
			if(R & 1) ret = min(ret, val[--R]);

			L >>= 1; R >>= 1;
		}
		return ret;
	}
};

int N, M, Q;
vector<int> to[MAXN], dist[MAXN];

int root[MAXN], lv[MAXN], ll;
i64 depth[MAXN];
vector<int> el;

RMQ <pair<int, int> > lca_tbl (make_pair(INT_MAX, 0));
pair<int, int> lca_sub[2*MAXN];
bool city_kind[MAXN];

void euler_tour(int p, int rt, i64 cd)
{
	depth[p] = cd;
	root[p] = rt;
	lv[p] = el.size();

	el.push_back(p);

	for(int i = 0; i < to[p].size(); i++) {
		if(to[p][i] == rt) continue;

		euler_tour(to[p][i], p, cd + dist[p][i]);

		el.push_back(p);
	}

	for(int i = 0; i < to[p].size(); i++)
		if(to[p][i] == root[p]) {
			to[p].erase(to[p].begin() + i);
			dist[p].erase(dist[p].begin() + i);
		}
}

void init_lca()
{
	for(int i = 0; i < el.size(); i++) {
		lca_sub[i] = make_pair(lv[el[i]], el[i]);
	}

	lca_tbl.init(lca_sub, el.size());
}

int lca(int p, int q)
{
	if(lv[p] > lv[q]) swap(p, q);

	return lca_tbl.query(lv[p], lv[q] + 1).second;
}

i64 sol;
vector<pair<int, int> > ord, ord2;
RMQ <pair<int, int> > rmq (make_pair(INT_MAX, INT_MAX));
vector<int> cityX, cityY;

pair<i64, i64> solve_small_dfs(int p, int q, int rt)
{
	if(p+1 == q) {
		i64 dd = (rt == -1 ? 0 : (depth[ord[p].second] - depth[rt]));

		if(city_kind[ord[p].second]) return make_pair(dd, INF);
		else return make_pair(INF, dd);
	}

	int bas = (int) rmq.query(p, q-1).second;

	pair<i64, i64> lf = solve_small_dfs(p, bas+1, ord2[bas].second),
				   rg = solve_small_dfs(bas+1, q, ord2[bas].second);
	i64 dd = (rt == -1 ? 0 : (depth[ord2[bas].second] - depth[rt]));

	sol = min(sol, min(lf.first + rg.second, lf.second + rg.first));
	return make_pair(dd + min(lf.first, rg.first), dd + min(lf.second, rg.second));
}

void Init(int N_, int A[], int B[], int D[])
{
	N = N_;

	for(int i = 0; i < N-1; i++) {
		to[A[i]].push_back(B[i]);
		dist[A[i]].push_back(D[i]);
		to[B[i]].push_back(A[i]);
		dist[B[i]].push_back(D[i]);
	}

	ll = 0;
	euler_tour(0, -1, 0);

	init_lca();
}

long long Query(int S, int X[], int T, int Y[])
{
	cityX.clear();
	for(int i = 0; i < S; i++) cityX.push_back(X[i]);
	cityY.clear();
	for(int i = 0; i < T; i++) cityY.push_back(Y[i]);

	ord.clear(); ord2.clear();

	for(int i = 0; i < cityX.size(); i++) {
		ord.push_back(make_pair(lv[cityX[i]], cityX[i]));
		city_kind[cityX[i]] = true;
	}

	for(int i = 0; i < cityY.size(); i++) {
		ord.push_back(make_pair(lv[cityY[i]], cityY[i]));
		city_kind[cityY[i]] = false;
	}

	sort(ord.begin(), ord.end());

	vector<pair<int, int> > ord3;

	for(int i = 1; i < ord.size(); i++) {
		int l = lca(ord[i-1].second, ord[i].second);

		ord2.push_back(make_pair(lv[l], l));
		ord3.push_back(make_pair(lv[l], i-1));
	}

	rmq.init(ord3);

	sol = INF;
	solve_small_dfs(0, ord.size(), -1);

	return sol;
}
