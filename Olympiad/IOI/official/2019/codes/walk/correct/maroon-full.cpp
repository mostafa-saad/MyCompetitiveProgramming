#include <bits/stdc++.h>
#include <type_traits>
#include "walk.h"

using namespace std;

using ll = int64_t;

#define FOR(i, a, b) for (int i = int(a); i < int(b); i++)
#define REP(i, b) FOR(i, 0, b)
#define MP make_pair
#define PB push_back
#define EB emplace_back
#define ALL(x) x.begin(), x.end()
auto &errStream = cerr;
#ifdef LOCAL
#define cerr (cerr << "-- line " << __LINE__ << " -- ")
#else
class CerrDummy
{
} cerrDummy;
template <class T>
CerrDummy &operator<<(CerrDummy &cd, const T &)
{
	return cd;
}
using charTDummy = char;
using traitsDummy = char_traits<charTDummy>;
CerrDummy &operator<<(CerrDummy &cd, basic_ostream<charTDummy, traitsDummy> &(basic_ostream<charTDummy, traitsDummy> &))
{
	return cd;
}
#define cerr cerrDummy
#endif
#define REACH cerr << "reached" << endl
#define DMP(x) cerr << #x << ":" << x << endl
#define ZERO(x) memset(x, 0, sizeof(x))
#define ONE(x) memset(x, -1, sizeof(x))

using pi = pair<int, int>;
using vi = vector<int>;
using ld = long double;

template <class T, class U>
ostream &operator<<(ostream &os, const pair<T, U> &p)
{
	os << "(" << p.first << "," << p.second << ")";
	return os;
}

template <class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
	os << "{";
	REP(i, (int)v.size())
	{
		if (i)
			os << ",";
		os << v[i];
	}
	os << "}";
	return os;
}

ll read()
{
	ll i;
	scanf("%" SCNd64, &i);
	return i;
}

void printSpace()
{
	printf(" ");
}

void printEoln()
{
	printf("\n");
}

void print(ll x, int suc = 1)
{
	printf("%" PRId64, x);
	if (suc == 1)
		printEoln();
	if (suc == 2)
		printSpace();
}

string readString()
{
	static char buf[3341000];
	scanf("%s", buf);
	return string(buf);
}

char *readCharArray()
{
	static char buf[3341000];
	static int bufUsed = 0;
	char *ret = buf + bufUsed;
	scanf("%s", ret);
	bufUsed += strlen(ret) + 1;
	return ret;
}

template <class T, class U>
void chmax(T &a, U b)
{
	if (a < b)
		a = b;
}

template <class T, class U>
void chmin(T &a, U b)
{
	if (b < a)
		a = b;
}

template <class T>
T Sq(const T &t)
{
	return t * t;
}

const ll infLL = LLONG_MAX / 3;

#ifdef int
const int inf = infLL;
#else
const int inf = INT_MAX / 2 - 100;
#endif

namespace Subtask4
{
ll Solve(vi x, vi h, vi l, vi r, vi y, int s, int g)
{
	int n = x.size();
	REP(k, 2)
	{
		int w = k == 0 ? s : g;
		vector<pi> p{pi(h[w], w)}, q{pi(h[w], w)};
		for (int i = w - 1; i >= 0; i--)
			if (h[i] > p.back().first)
				p.EB(h[i], i);
		for (int i = w + 1; i < n; i++)
			if (h[i] > q.back().first)
				q.EB(h[i], i);
		vi ll, rr, yy;
		REP(i, l.size())
		{
			if (l[i] < w && w < r[i])
			{
				int a, b;
				{
					auto itr = lower_bound(ALL(p), pi(y[i], -1));
					assert(itr != p.end());
					a = itr->second;
				}
				{
					auto itr = lower_bound(ALL(q), pi(y[i], -1));
					assert(itr != q.end());
					b = itr->second;
				}
				if (l[i] < a)
				{
					ll.PB(l[i]);
					rr.PB(a);
					yy.PB(y[i]);
				}
				if (a < b)
				{
					ll.PB(a);
					rr.PB(b);
					yy.PB(y[i]);
				}
				if (b < r[i])
				{
					ll.PB(b);
					rr.PB(r[i]);
					yy.PB(y[i]);
				}
			}
			else
			{
				ll.PB(l[i]);
				rr.PB(r[i]);
				yy.PB(y[i]);
			}
		}
		l = ll;
		r = rr;
		y = yy;
	}

	int m = l.size();

	vector<pi> posYX{pi(0, x[s]), pi(0, x[g])};
	{
		vector<tuple<int, int, int>> xty;
		REP(i, m)
		{
			xty.EB(x[l[i]], 0, y[i]);
			xty.EB(x[r[i]], 1, -y[i]);
		}

		sort(ALL(xty));
		multiset<int> ys;
		for (auto q : xty)
		{
			int j = get<0>(q), t = get<1>(q), i = get<2>(q) * (t == 0 ? 1 : -1);
			posYX.EB(i, j);
			auto itr = ys.lower_bound(i);
			if (itr != ys.begin())
			{
				--itr;
				posYX.EB(*itr, j);
			}
			if (t == 0)
				ys.insert(i);
			else
				ys.erase(ys.find(i));
		}

		sort(ALL(posYX));
		posYX.erase(unique(ALL(posYX)), posYX.end());
	}

	const auto Idx = [&](int i, int j) {
		return lower_bound(ALL(posYX), pi(i, j)) - posYX.begin();
	};

	int vs = posYX.size();
	vector<vector<pi>> graph(vs);
	const auto AddEdge = [&](int a, int b, int c) {
		graph[a].EB(b, c);
		graph[b].EB(a, c);
	};

	REP(i, m)
	{
		int k = Idx(y[i], x[l[i]]);
		while (k + 1 < int(posYX.size()) && posYX[k + 1] <= pi(y[i], x[r[i]]))
		{
			AddEdge(k, k + 1, posYX[k + 1].second - posYX[k].second);
			k++;
		}
	}

	vector<pi> posXY = posYX;
	for (auto &p : posXY)
		swap(p.first, p.second);
	sort(ALL(posXY));
	REP(i, vs - 1)
	{
		if (posXY[i].first == posXY[i + 1].first)
		{
			AddEdge(Idx(posXY[i].second, posXY[i].first), Idx(posXY[i + 1].second, posXY[i + 1].first), posXY[i + 1].second - posXY[i].second);
		}
	}

	vector<ll> dist(vs, infLL);
	using pli = tuple<ll, int>;
	priority_queue<pli, vector<pli>, greater<pli>> pq;
	const auto Reach = [&](int v, ll d) {
		if (dist[v] > d)
		{
			dist[v] = d;
			pq.push(pli(d, v));
		}
	};
	Reach(Idx(0, x[s]), 0);
	while (!pq.empty())
	{
		int v;
		ll d;
		tie(d, v) = pq.top();
		pq.pop();
		if (dist[v] != d)
			continue;
		for (auto e : graph[v])
			Reach(e.first, dist[v] + e.second);
	}

	return dist[Idx(0, x[g])] == infLL ? -1 : dist[Idx(0, x[g])];
}
} // namespace Subtask4

long long min_distance(std::vector<int> X, std::vector<int> H, std::vector<int> L, std::vector<int> R, std::vector<int> Y, int S, int G)
{
	return Subtask4::Solve(X, H, L, R, Y, S, G);
}
