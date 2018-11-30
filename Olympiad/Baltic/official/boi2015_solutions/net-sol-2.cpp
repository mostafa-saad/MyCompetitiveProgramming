/*/
  Task: net
  Alternative model solution O(n log n)
    with set
  Author: Bartosz Kostka 
/*/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 500007;

bool odw[MAXN];
int leaves[MAXN];
int numleaves;

vector <int> G[MAXN], S[MAXN];

void dfs(int v)
{
  odw[v] = true;
  if((int)G[v].size() == 1)
    leaves[v] = 1;
  for(auto w : G[v])
    if(odw[w]==false)
    {
      dfs(w);
      leaves[v] += leaves[w];
    }
} 

int findcut(int v)
{
  odw[v] = true;
  for(auto w : G[v])
    if(odw[w] == false)
      if(leaves[w] > numleaves/2)
        return findcut(w);
  return v;
}

void newdfs(int v, int tree)
{
  //cerr << v << " " << tree << "T\n";
  odw[v] = true;
  if((int)G[v].size() == 1)
    S[tree].push_back(v);
  for(auto w : G[v])
    if(odw[w] == false)
      newdfs(w,tree);
}

int subtree;

int cut(int n)
{
  dfs(1);
  for(int i=1; i<=n; i++)
    odw[i] = false;
  int w = findcut(1);
  for(int i=1; i<=n; i++)
    odw[i] = false;
  odw[w] = true;
  for(auto v : G[w])
    newdfs(v,++subtree);
  return w;
}

struct cmp {
    bool operator() (const int &a, const int &b) {
        if(S[a].size() != S[b].size()) return S[a].size() > S[b].size();
        else return a < b;
    }
};

set <int, cmp> Q;
vector <int> W;

int main()
{
  int n;
  scanf("%d", &n);
  if(n==1)
  {
    printf("0\n");
    return 0;
  }
  if(n==2)
  {
    printf("1\n1 2\n");
    return 0;
  }
  for(int i=1; i<n; i++)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    G[a].push_back(b);
    G[b].push_back(a);
  }
  for(int i=1; i<=n; i++)
    if((int)G[i].size() == 1)
      numleaves++;
  printf("%d\n", (numleaves+1)/2);
  cut(n);
  for(int i=1; i<=subtree; i++)
    Q.insert(i);
  while(!Q.empty())
  {
    int a = (*Q.begin());
    Q.erase(a);
    W.push_back(S[a].back());
    S[a].pop_back();
    if(!Q.empty())
    {
      int b = (*Q.begin());
      Q.erase(b);
      W.push_back(S[b].back());
      S[b].pop_back(); 
      if(!S[b].empty())
        Q.insert(b);
    }
    if(!S[a].empty())
      Q.insert(a); 
  }

  if((int)W.size() % 2)
    W.push_back(S[1][0]);

  for(int i=0; i<(int)W.size(); i+=2)
    printf("%d %d\n", W[i], W[i+1]);
} 
