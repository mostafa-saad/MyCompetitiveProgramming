/*/
  Task: net
  Brute-force solution
  With early termination
  With O(n) bridge finding
  Author: Bartosz Kostka 
/*/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 500007;

vector <int> L, G[MAXN];
int w, n;

int licz;
int d[MAXN+7], low[MAXN+7], par[MAXN+7];
bool vis[MAXN+7];

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

void go(vector <int> &L, vector <int> &A)
{
  if(L.size() <= 1)
  {
    if(!L.empty())
    {
      G[L[0]].push_back(w);
      G[w].push_back(L[0]);
      A.push_back(L[0]);
      A.push_back(w);
      if(bridges()==false)
        print(A);
      A.pop_back();
      A.pop_back();
      G[w].pop_back();
      G[L[0]].pop_back();
    }
    else
    {
      if(bridges()==false)
        print(A);
    }
    return;
  }
  int a = L.back();
  L.pop_back();
  int ls = (int)L.size();
  A.push_back(a);
  for(int i=0; i<ls; i++)
  {
    swap(L[i], L.back());
    int b = L.back();
    L.pop_back();

    G[a].push_back(b);
    G[b].push_back(a);
    A.push_back(b);

    go(L,A);

    A.pop_back();
    G[b].pop_back();
    G[a].pop_back();
    
    L.push_back(b);
    swap(L[i], L.back());
  }
  A.pop_back();
  L.push_back(a);
}

int main()
{
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
  vector <int> AA;
  go(L,AA);
}
