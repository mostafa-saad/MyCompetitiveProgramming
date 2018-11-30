/*/
   Checker for task: NET
   Author: Bartek Kostka
*/

#include "bits/stdc++.h"
#include "oi.h"

using namespace std;

void own_error_function(const char* msg, int line, int position)
{
	printf("WRONG\n%s\n",msg);
	exit(1);
}

const int MAXN = 500000;

vector <int> G[MAXN+7];

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

bool bridges(int n)
{
  dfs(1);
  for(int i=1; i<=n; i++)
    if(d[i]==low[i] and d[i])
      return true;
  return false;
}

int main(int argc, char **argv)
{
    oi::Scanner in(argv[1], own_error_function, oi::PL);
    oi::Scanner out(argv[2], own_error_function, oi::PL);
    oi::Scanner out_correct(argv[3], own_error_function, oi::PL);
    int n = in.readInt();
    in.readEoln();
    for(int i=1; i<n; i++)
    {
        int u = in.readInt(1,n);
        in.readSpace();
        int v = in.readInt(1,n);
        G[u].push_back(v);
        G[v].push_back(u);
        in.readEoln();
    }
    in.readEof();
    
    int e = out_correct.readInt();
    int f = out.readInt();
    out.skipWhitespacesUntilEOLN();
    out.readEoln();
    if(e != f)
        out.error("Invalid number of links.");
    for(int i=0; i<f; i++)
    {
       int a = out.readInt(1,n);
       out.skipWhitespaces();
       int b = out.readInt(1,n);
       out.skipWhitespacesUntilEOLN();
       out.readEofOrEoln();

       G[a].push_back(b);
       G[b].push_back(a);
    } 
    if(bridges(n)==true)
      out.error("Breaking single line is causing network to disconnect.");
    printf("OK\nOK\n100");
    return 0;
}
