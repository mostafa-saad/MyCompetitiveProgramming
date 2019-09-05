#include <iostream>
#include <vector>
#include <memory.h>
#include <algorithm>
#include <set>
#include <map>

#define pb push_back
#define mp make_pair

using namespace std;

const int maxn = 1000000 + 10;
const long long inf = 1e18;
int n, m, X[maxn], Y[maxn], H[maxn], L[maxn], R[maxn], a[maxn], b[maxn], node, y_map[maxn];
vector<int> neiL[maxn], neiR[maxn];
long long dis[maxn];
vector<pair<int, long long>> adj[maxn];
map<pair<int, int>, int> nodes;
vector<int> all_y;

void devide(int idx)
{
	memset(a, -1, sizeof(a));
	memset(b, -1, sizeof(b));
	vector<pair<pair<int, int>, int>> sky;
	vector<pair<int, int>> st;
	st.pb(mp(H[idx], idx));
	for (int i = idx - 1; i >= 0; i--)
	{
		if (H[i] > st.back().first)
			st.push_back(mp(H[i], i));
		for (int j = 0; j < neiL[i].size(); j++)
		{
			int cur = neiL[i][j];
			if (R[cur] > idx)
			{
				int pos = upper_bound(st.begin(), st.end(), mp(Y[cur], -1)) - st.begin();
				a[cur] = st[pos].second;
			}
		}
	}
	st.clear();
	st.pb(mp(H[idx], idx));
	for (int i = idx + 1; i < n; i++)
	{
		if (H[i] > st.back().first)
			st.push_back(mp(H[i], i));
		for (int j = 0; j < neiR[i].size(); j++)
		{
			int cur = neiR[i][j];
			if (L[cur] < idx)
			{
				int pos = upper_bound(st.begin(), st.end(), mp(Y[cur], -1)) - st.begin();
				b[cur] = st[pos].second;
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		if (a[i] != -1)
		{
			if (a[i] != L[i])
				sky.pb(mp(mp(L[i], a[i]), Y[i]));
			if (a[i] != b[i])
				sky.pb(mp(mp(a[i], b[i]), Y[i]));
			if (b[i] != R[i])
				sky.pb(mp(mp(b[i], R[i]), Y[i]));
		}
		else
			sky.pb(mp(mp(L[i], R[i]), Y[i]));
	}
	for (int i = 0; i < n; i++)
	{
		neiL[i].clear();
		neiR[i].clear();
	}
	m = sky.size();
	for (int i = 0; i < m; i++)
	{
		L[i] = sky[i].first.first;
		R[i] = sky[i].first.second;
		Y[i] = sky[i].second;
		neiL[L[i]].pb(i);
		neiR[R[i]].pb(i);
	}
}

long long dijkstra(int source, int sink)
{
	set<pair<long long, int>> S;
	for (int i = 0; i <= node; i++)
		dis[i] = inf;
	dis[source] = 0;
	S.insert(mp(0, source));
	while (S.size())
	{
		set<pair<long long, int>>::iterator it = S.begin();
		long long dist = (*it).first;
		int v = (*it).second;
		S.erase(it);
		for (int i = 0; i < adj[v].size(); i++)
		{
			int u = adj[v][i].first;
			long long w = adj[v][i].second;
			if (dist + w < dis[u])
			{
				S.erase(mp(dis[u], u));
				dis[u] = dist + w;
				S.insert(mp(dis[u], u));
			}
		}
	}
	if (dis[sink] == inf)
		return -1;
	return dis[sink];
}

int add_map(int x, int y)
{
	if (!nodes[mp(x, y)])
		nodes[mp(x, y)] = ++node;
	return nodes[mp(x, y)];
}

void add_edge(int x1, int y1, int x2, int y2)
{
	int u = add_map(x1, y1);
	int v = add_map(x2, y2);
	if (x1 == x2)
	{
		adj[u].push_back(mp(v, abs(y2 - y1)));
		adj[v].push_back(mp(u, abs(y2 - y1)));
	}
	else
	{
		adj[u].push_back(mp(v, abs(x2 - x1)));
		adj[v].push_back(mp(u, abs(x2 - x1)));
	}
}

void build_graph()
{
	set<int> line;
	line.insert(0);
	set<int>::iterator it;
	map<int, int> st;
	vector<int> set_res;
	memset(y_map, -1, sizeof(y_map));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < neiL[i].size(); j++)
		{
			int cur = neiL[i][j];
			line.insert(-Y[cur]);
		}
		for (int j = 0; j < neiL[i].size(); j++)
		{
			int cur = neiL[i][j];
			it = line.upper_bound(-Y[cur]);
			int y2 = Y[cur];
			int y1 = -(*it);
			int y2_id = lower_bound(all_y.begin(), all_y.end(), y2) - all_y.begin() + 1;
			int y1_id = lower_bound(all_y.begin(), all_y.end(), y1) - all_y.begin() + 1;
			set_res.pb(y1_id);
			set_res.pb(y2_id);
			add_edge(X[i], y1, X[i], y2);
			if (y_map[y1_id] != -1 && y1 != 0)
			{
				add_edge(X[i], y1, y_map[y1_id], y1);
			}
		}
		for (int j = 0; j < neiR[i].size(); j++)
		{
			int cur = neiR[i][j];
			it = line.upper_bound(-Y[cur]);
			int y2 = Y[cur];
			int y1 = -(*it);
			int y2_id = lower_bound(all_y.begin(), all_y.end(), y2) - all_y.begin() + 1;
			int y1_id = lower_bound(all_y.begin(), all_y.end(), y1) - all_y.begin() + 1;
			set_res.pb(y1_id);
			set_res.pb(y2_id);
			add_edge(X[i], y1, X[i], y2);
			add_edge(X[i], y2, y_map[y2_id], y2);
			if (y_map[y1_id] != -1 && y1 != 0)
			{
				add_edge(X[i], y1, y_map[y1_id], y1);
			}
		}

		for (int j = 0; j < set_res.size(); j++)
			y_map[set_res[j]] = X[i];
		set_res.clear();

		for (int j = 0; j < neiR[i].size(); j++)
		{
			int cur = neiR[i][j];
			int y2 = lower_bound(all_y.begin(), all_y.end(), Y[cur]) - all_y.begin() + 1;
			y_map[y2] = -1;
			line.erase(-Y[cur]);
		}
		for (int j = 0; j < neiL[i].size(); j++)
		{
			int cur = neiL[i][j];
			int y2 = lower_bound(all_y.begin(), all_y.end(), Y[cur]) - all_y.begin() + 1;
			y_map[y2] = X[i];
			line.insert(-Y[cur]);
		}
	}
}


bool cmp(pair<int, pair<int, int> > aa, pair<int, pair<int, int> > bb){
	if(aa.first < bb.first)
		return true;
	if(aa.first > bb.first)
		return false;
	return aa.second.first < bb.second.first;
	
}

void init(){
	vector<pair<int, pair<int, int> > > tmp, nw;
	for(int i = 0; i < m; i++)
		tmp.push_back(mp(Y[i], mp(L[i], R[i])));
	sort(tmp.begin(), tmp.end(), cmp);
	for(int i = 0; i < m; i++){
		if(tmp[i].second.first == tmp[i].second.second) continue;
		int j = i;
		int hei = tmp[i].first;
		int lo = tmp[i].second.first;
		int hi = tmp[i].second.second;
		while(tmp[j].first == hei && tmp[j].second.first <= hi && tmp[j].second.first >= lo){
			hi = max(hi, tmp[j].second.second);
			j++;
		}
		nw.push_back(mp(hei, mp(lo, hi)));
		i = j - 1;
	}
	m = nw.size();
	for (int i = 0; i < m; i++)
	{
		L[i] = nw[i].second.first;
		R[i] = nw[i].second.second;
		Y[i] = nw[i].first;
		neiL[L[i]].pb(i);
		neiR[R[i]].pb(i);
	}
	
}

long long min_distance(vector<int> XX, vector<int> HH, vector<int> LL, vector<int> RR, vector<int> YY, int S, int G)
{
	n = XX.size();
	m = LL.size();
	for (int i = 0; i < n; i++)
	{
		X[i] = XX[i];
		H[i] = HH[i];
	}
	for (int i = 0; i < m; i++)
	{
		L[i] = LL[i];
		R[i] = RR[i];
		Y[i] = YY[i];
		all_y.push_back(Y[i]);
	}
	init();
	all_y.push_back(0);
	sort(all_y.begin(), all_y.end());
	all_y.resize(unique(all_y.begin(), all_y.end()) - all_y.begin());
	devide(S);
	devide(G);
	build_graph();
	return dijkstra(add_map(X[S], 0), add_map(X[G], 0));
}

