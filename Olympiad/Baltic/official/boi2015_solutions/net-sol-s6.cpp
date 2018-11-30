/*/
  Task: net
  Random solution
  With covering edges
  Author: Bartosz Kostka 
/*/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 500007;

vector <int> L,G[MAXN];
int w, n;

int licz;
int d[MAXN], par[MAXN];
bool vis[MAXN];
map <pair <int, int>, bool> M;

void print(vector <int> &S)
{
  printf("%d\n", (int)S.size()/2);
  for(int i=0; i<(int)S.size(); i+=2)
    printf("%d %d\n", S[i], S[i+1]);
  exit(0);
}

void dfs(int v)
{
  vis[v] = true;
  for(auto w : G[v])
    if(vis[w] == false)
    {
      d[w] = d[v]+1;
      par[w] = v;
      dfs(w);
    }
}

void sset(int a, int b, bool jak)
{
  int x = min(a,b);
  int y = max(a,b);
  M[make_pair(x,y)] = jak;
}

void cover(int a, int b)
{
  if(d[a] < d[b])
    swap(a,b);
  while(d[a] != d[b])
  {
    sset(a,par[a],true);
    a = par[a];
  }
  while(a != b)
  {
    cerr << a << " " << b << "\n";
    cerr << "P" << par[a] << " " << par[b] << "\n";
    sset(a,par[a],true);
    a = par[a];
    sset(b,par[b],true);
    b = par[b];
  }
}

bool bridges()
{
  cerr << "???\n";
  for(auto ele : M)
    if(ele.second == false)
      return true;
  return false;
}

int main()
{
  srand(42);
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
    sset(a,b,false);
  }
  for(int i=1; i<=n; i++)
  {
    if((int)G[i].size() == 1)
      L.push_back(i);
    else
      w = i;
  }
  dfs(w);
  if((int)L.size() % 2 == 1)
    L.push_back(w);
  while(true)
  {
    random_shuffle(L.begin(), L.end());
    for(int i=0; i<(int)L.size(); i+=2)
    {
      int a = L[i], b = L[i+1];
      cerr << a << " " << b << "\n";
      cover(a,b);
    }
    if(bridges() == false)
      print(L);
    for(auto& ele : M)
      ele.second = false; 
  } 
}
