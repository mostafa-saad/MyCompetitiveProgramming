#include "walk.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cassert>

using namespace std;

const int MAXN = 200 * 1000 + 10;
const int MAXM = 200 * 1000 + 10;
const int MAXRM = 5 * MAXM;
const int MAXV = 2 * 2 * MAXRM;
const long long INF = 1000ll * 1000 * 1000 * 1000 * 1000 * 1000;

typedef pair<int, int> pii;
typedef set<pii>::iterator sit;

typedef pair<long long, int> pli;
long long dist[MAXV];

int vcnt = 0;
vector<pii> edges[MAXV];
set<pli> dij;
int last_x[MAXRM];
int last_vertex[MAXRM];
int last_height[MAXN];
int first_height[MAXN];
vector<pii> adds[MAXN];
vector<pii> removes[MAXN];
set<pii> walks;

long long dijkstra(int start, int dest)
{
	for (int i = 0; i < vcnt; i++)
		dist[i] = INF;
	dist[start] = 0;
	dij.insert(pli(dist[start], start));
	while (!dij.empty())
	{
		int v = dij.begin()->second;
		dij.erase(dij.begin());
		if (v == dest)
			return dist[v];
		for (int i = 0; i < (int)edges[v].size(); i++)
		{
			int u = edges[v][i].first;
			int w = edges[v][i].second;
			if (dist[u] > dist[v] + w)
			{
				dij.erase(pli(dist[u], u));
				dist[u] = dist[v] + w;
				dij.insert(pli(dist[u], u));
			}
		}
	}
	return -1;
}

void add_edge(int u, int v, int w)
{
	edges[u].push_back(pii(v, w));
	edges[v].push_back(pii(u, w));
}

int make_vertex(int walk, int x)
{
	if (last_x[walk] == x)
		return last_vertex[walk];
	int cur = vcnt++;
	if (last_vertex[walk] != -1)
		add_edge(last_vertex[walk], cur, x - last_x[walk]);
	last_x[walk] = x;
	last_vertex[walk] = cur;
	return cur;
}

void break_segments(vector<int> &l, vector<int> &r, vector<int> &y, int s, vector<int> &h)
{
	vector<int> heights = h;
	sort(heights.begin(), heights.end());
	heights.resize(unique(heights.begin(), heights.end()) - heights.begin());
	for (int i = 0; i < (int)heights.size(); i++)
	{
		last_height[i] = -1;
		first_height[i] = h.size() + 1;
	}
	for (int i = 0; i < (int)h.size(); i++)
	{
		int idx = lower_bound(heights.begin(), heights.end(), h[i]) - heights.begin();
		assert(idx < (int)heights.size());
		if (i <= s)
			last_height[idx] = max(last_height[idx], i);
		if (i >= s)
			first_height[idx] = min(first_height[idx], i);
	}
	for (int i = (int)heights.size() - 2; i >= 0; i--)
	{
		last_height[i] = max(last_height[i], last_height[i + 1]);
		first_height[i] = min(first_height[i], first_height[i + 1]);
	}
	for (int i = 0; i < (int)l.size(); i++)
		if (l[i] < s && r[i] > s)
		{
			int idx = lower_bound(heights.begin(), heights.end(), y[i]) - heights.begin();
			assert(idx < (int)heights.size());
			int x = l[i];
			int a = last_height[idx];
			int b = first_height[idx];
			int q = r[i];

			assert(a != -1);
			assert(b != (int)h.size() + 1);

			if (x < a)
			{
				r[i] = a;
				if (a < b)
				{
					l.push_back(a);
					r.push_back(b);
					y.push_back(y[i]);
				}
			}
			else
			{
				assert(x == a);
				r[i] = b;
			}
			if (q > b)
			{
				l.push_back(b);
				r.push_back(q);
				y.push_back(y[i]);
			}
			else
			{
				assert(q == b);
			}
		}
}

long long min_distance(vector<int> x, vector<int> h, vector<int> l, vector<int> r, vector<int> y, int s, int g)
{
	if (s == g)
		return 0;
	int n = x.size();

	break_segments(l, r, y, s, h);
	break_segments(l, r, y, g, h);
	int m = l.size();

	for (int i = 0; i < m; i++)
	{
		last_x[i] = last_vertex[i] = -1;
		adds[l[i]].push_back(pii(y[i], i));
		removes[r[i]].push_back(pii(y[i], i));
	}
	int sv = -1, gv = -1;
	long long res = 0;
	for (int i = 0; i < n; i++)
	{
		sort(adds[i].begin(), adds[i].end());
		for (int j = 0; j < (int)adds[i].size(); j++)
		{
			int v = make_vertex(adds[i][j].second, x[i]);
			sit it = walks.lower_bound(adds[i][j]);
			if (it != walks.begin())
			{
				it--;
				int u = make_vertex(it->second, x[i]);
				add_edge(u, v, adds[i][j].first - it->first);
			}
			walks.insert(adds[i][j]);
		}
		if (i == s)
		{
			if (walks.empty() || walks.begin()->first > h[i])
				return -1;
			sv = make_vertex(walks.begin()->second, x[i]);
			res += walks.begin()->first;
		}
		if (i == g)
		{
			if (walks.empty() || walks.begin()->first > h[i])
				return -1;
			gv = make_vertex(walks.begin()->second, x[i]);
			res += walks.begin()->first;
		}
		sort(removes[i].begin(), removes[i].end(), greater<pii>());
		for (int j = 0; j < (int)removes[i].size(); j++)
		{
			int v = make_vertex(removes[i][j].second, x[i]);
			sit it = walks.find(removes[i][j]);
			if (it != walks.begin())
			{
				sit it2 = it;
				it2--;
				int u = make_vertex(it2->second, x[i]);
				add_edge(u, v, removes[i][j].first - it2->first);
			}
			assert(it != walks.end());
			walks.erase(it);
		}
	}
	assert(sv != -1);
	assert(gv != -1);
	long long dij_res = dijkstra(sv, gv);
	if(dij_res == -1)
		return -1;
	return res + dij_res;
}
