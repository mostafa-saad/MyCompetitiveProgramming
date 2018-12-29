/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Bezpieczenstwo minimalistyczne                   *
 *   Autor:             Krzysztof Leszczynski                            *
 *   Zlozonosc czasowa: O(p(1)*(n + m))                                  *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>

#define FORI(it,n) for(typeof((n).begin()) it=(n).begin(); it!=(n).end(); it++)
using namespace std;
typedef long long LL;

const int MAXN=500100;
const int MAXM=3000000;
const int INF=1000000100;
const LL LONG_INF=LL(INF)*LL(INF);

int n,m;
int P[MAXN];
vector<pair<int,int> > graf[MAXN];
int vis[MAXN];
int pol[MAXN];
LL S,ans1,ans2;

void read()
{
  int a,b,c;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {cin >> P[i]; S+=P[i];}
  while(m--) {
    cin >> a >> b >> c;
    graf[a].push_back(make_pair(b,c));
    graf[b].push_back(make_pair(a,c));
  }
}
bool dfs(int a, LL &t)
{
  t+=pol[a];
  if(pol[a]<0) return 0;
  if(pol[a]>P[a]) return 0;
  FORI(it,graf[a]) {
    if(vis[it->first]!=vis[a]) {
      pol[it->first]=it->second-pol[a];
      vis[it->first]=vis[a];
      if(!dfs(it->first,t)) return 0;
    }
    if(pol[it->first]!=it->second-pol[a]) return 0;
  }
  return 1;
}
bool play(int a)
{
  LL mini=LONG_INF,maxi=0,t;
  for(int w=0; w<=P[a]; w++) {
    vis[a]=w+1; 
    pol[a]=w;
    t=0;
    if(dfs(a,t)) {
      mini=min(mini,t);
      maxi=max(maxi,t);
    }
  }
  if(mini==LONG_INF) return 0;
  ans1+=mini;
  ans2+=maxi;
  return 1;
}

int main()
{
  ios_base::sync_with_stdio(0);
  read();
  for(int i=1; i<=n; i++) if(!vis[i] && !play(i)) {cout << "NIE\n"; return 0;}
  cout << S-ans2 << " " << S-ans1 << endl;
}
