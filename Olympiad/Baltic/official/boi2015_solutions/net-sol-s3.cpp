/*/
  Task: net
  Brute-force solution
  With early termination
  With O(n^2) bridge finding
  Author: Bartosz Kostka 
/*/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 500007;

vector <int> L, G[MAXN];
int w, n;

int licz;

bool vis[MAXN+7];

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
