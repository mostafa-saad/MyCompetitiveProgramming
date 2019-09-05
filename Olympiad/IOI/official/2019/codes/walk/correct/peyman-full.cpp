//Peyman Jabbarzade
#include "walk.h"
#include <bits/stdc++.h>
#define MP make_pair
#define X first
#define Y second
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 2e5 + 100, MAXN = 1e6;
int n, m, cnt, x[maxn], h[maxn], l[maxn], r[maxn], hb[maxn];
ll dis[MAXN];
vector<int> incL, incR, G[MAXN], W[MAXN];
vector<pii> nodes[maxn];
vector<pair<pii, pii>> q;
set<pii> sd;

struct hbCmp
{
  bool operator()(const int &A, const int &B)
  {
    if (hb[A] == hb[B])
      return A < B;
    return hb[A] < hb[B];
  }
};
set<int, hbCmp> s;

bool cmp(int A, int B)
{
  return (h[A] >= B);
}

ll dijkstra(int vv, int uu)
{
  memset(dis, 63, sizeof dis);
  dis[vv] = 0;
  sd.insert(pii(0, vv));

  while (sd.size())
  {
    int v = sd.begin()->Y;
    if (v == uu)
      return dis[v];
    sd.erase(sd.begin());
    for (int i = 0; i < G[v].size(); i++)
    {
      int u = G[v][i], w = W[v][i];
      if (dis[v] + w < dis[u])
      {
        sd.erase(pii(dis[u], u));
        dis[u] = dis[v] + w;
        sd.insert(pii(dis[u], u));
      }
    }
  }
  return -1;
}

int add_vertex(int bridge, int building)
{
  cnt++;
  nodes[bridge].push_back(pii(building, cnt));
  return cnt;
}

void add_edge(int v, int u, int w)
{
  G[v].push_back(u);
  G[u].push_back(v);
  W[v].push_back(w);
  W[u].push_back(w);
}

void add_edge_to_down_bridge(int bridge, int building)
{
  set<int, hbCmp>::iterator it = s.find(bridge);
  if (it != s.begin())
  {
    int down_bridge = *(--it);
    int v = add_vertex(bridge, building);
    int u = add_vertex(down_bridge, building);
    add_edge(v, u, hb[bridge] - hb[down_bridge]);
  }
}

int add_bridge(int L, int R, int HB)
{
  l[m] = L, r[m] = R, hb[m] = HB;
  m++;
  return m - 1;
}

void cut(int ind, int mid)
{
  if (hb[ind] <= h[mid])
  {
    add_bridge(mid, r[ind], hb[ind]);
    r[ind] = mid;
    return;
  }
  int indL = incL[lower_bound(incL.begin(), incL.end(), hb[ind], cmp) - incL.begin()];
  int indR = incR[lower_bound(incR.begin(), incR.end(), hb[ind], cmp) - incR.begin()];
  if (indL > l[ind])
  {
    add_bridge(l[ind], indL, hb[ind]);
    l[ind] = indL;
  }
  if (indR < r[ind])
  {
    add_bridge(indR, r[ind], hb[ind]);
    r[ind] = indR;
  }
}

void cut_all(int ind)
{
  int oldM = m;
  incL.clear();
  incR.clear();
  for (int i = ind - 1; i > -1; i--)
    if (incL.empty() || h[incL.back()] < h[i])
      incL.push_back(i);
  for (int i = ind + 1; i < n; i++)
    if (incR.empty() || h[incR.back()] < h[i])
      incR.push_back(i);
  for (int i = 0; i < oldM; i++)
    if (l[i] < ind && ind < r[i])
      cut(i, ind);
}

long long min_distance(vector<int> X, vector<int> H, vector<int> L, vector<int> R, vector<int> Y, int st, int en)
{
  //read input
  n = X.size();
  m = Y.size();
  for (int i = 0; i < n; i++)
    x[i] = X[i], h[i] = H[i];
  for (int i = 0; i < m; i++)
    l[i] = L[i], r[i] = R[i], hb[i] = Y[i];
  if (st == en)
    return 0;
  //cut bridge on start or end
  cut_all(st);
  cut_all(en);
  st = add_bridge(st, st, 0);
  en = add_bridge(en, en, 0);
  //make graph
  for (int i = 0; i < m; i++)
  {
    q.push_back(MP(pii(l[i], 0), pii(hb[i], i)));
    q.push_back(MP(pii(r[i], 1), pii(-hb[i], i)));
  }
  sort(q.begin(), q.end());
  for (int i = 0; i < q.size(); i++)
  {
    int building = q[i].X.X, bridge = q[i].Y.Y, type = q[i].X.Y; //st -> 0, en -> 1
    if (type == 0)
    {
      s.insert(bridge);
      add_edge_to_down_bridge(bridge, building);
    }
    else
    {
      add_edge_to_down_bridge(bridge, building);
      s.erase(bridge);
    }
  }
  for (int i = 0; i < m; i++)
  {
    sort(nodes[i].begin(), nodes[i].end());
    for (int j = 0; j < nodes[i].size() - 1; j++)
      add_edge(nodes[i][j].Y, nodes[i][j + 1].Y, x[nodes[i][j + 1].X] - x[nodes[i][j].X]);
  }
  //find shortest path
  if (nodes[st].empty() || nodes[en].empty())
    return -1;
  int st_node = nodes[st][0].Y;
  int en_node = nodes[en][0].Y;
  return dijkstra(st_node, en_node);
}
