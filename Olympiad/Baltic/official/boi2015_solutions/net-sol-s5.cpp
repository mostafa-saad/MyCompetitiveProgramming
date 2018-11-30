/*/
  Task: net
  Slow random solution
  With O(n^2) bridge finding
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
  vis[v] = true;
  for(auto w : G[v])
    if(vis[w]==false)
       dfs(w);
}
bool bridges()
{
  for(int i=1; i<=n; i++)
    for(int j=0; j<(int)G[i].size(); j++)
    {
      int c = G[i][j];
      swap(G[i][j], G[i].back());
      G[i].pop_back();
      for(int k=1; k<=n; k++)
        vis[k] = false;
      dfs(1);
      G[i].push_back(c);
      swap(G[i][j], G[i].back());
      for(int k=1; k<=n; k++)
        if(!vis[k])
          return true;
    }
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
