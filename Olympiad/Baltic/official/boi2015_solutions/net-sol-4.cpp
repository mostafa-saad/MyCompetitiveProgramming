/*/
  Task: net
  Random solution
  With O(n) bridge finding
  Author: Bartosz Kostka 
/*/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 500007;

vector <int> L, G[MAXN];
int w, n;

int licz;
int d[MAXN], low[MAXN], par[MAXN];
bool vis[MAXN];

void dfs(int v)
{
  vis[v] = 1;
  for(auto w : G[v])
  {
    if(vis[w] == false)
    {
       par[w] = v;
       d[w] = d[v] + 1;
       dfs(w);
    }
  }
  low[v] = d[v];
  bool multiple = false;
  for(auto w : G[v])
  {
    //jest moim synem
    if(par[w] == v)
    {
      low[v] = min(low[v], low[w]);
      continue;
    }
    
    //jest moim ojcem
    if(w == par[v] and multiple == false)
    {
      multiple = true;
      continue;
    }

    //jest krawedzia wtorna
    low[v] = min(low[v], d[w]);
  }
}

bool bridges()
{
  for(int i=1; i<=n; i++)
    vis[i] = false;
  for(int i=1; i<=n; i++)
    low[i] = par[i] = d[i] = 0;
  dfs(1);
  for(int i=1; i<=n; i++)
    if(d[i]==low[i] and d[i])
      return true;
  return false;
}

void print(vector <int> &S)
{
  printf("%d\n", (int)S.size()/2);
  for(int i=0; i<(int)S.size(); i+=2)
    printf("%d %d\n", S[i], S[i+1]);
  exit(0);
}

int main()
{
  srand(42);
  scanf("%d", &n);
  for(int i=1; i<n; i++)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    G[a].push_back(b);
    G[b].push_back(a);
  }
  for(int i=1; i<=n; i++)
  {
    if((int)G[i].size() == 1)
      L.push_back(i);
    else
      w = i;
  }
  if((int)L.size() % 2 == 1)
    L.push_back(w);
  while(true)
  {
    cerr << "X";
    random_shuffle(L.begin(), L.end());
    for(int i=0; i<(int)L.size(); i+=2)
    {
      int a = L[i], b = L[i+1];
      G[a].push_back(b);
      G[b].push_back(a);
    }
    if(bridges() == false)
      print(L);
    for(int i=0; i<(int)L.size(); i+=2)
    {
      int a = L[i], b = L[i+1];
      G[a].pop_back();
      G[b].pop_back();
    }    
  } 
}
