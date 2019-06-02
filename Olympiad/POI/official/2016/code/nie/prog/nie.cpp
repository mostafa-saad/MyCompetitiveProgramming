/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Niebanalne podroze                                 *
 *   Autor:                Bartosz Kostka                                     *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/


#include "bits/stdc++.h"

using namespace std;

const int MAXN = 500007, MAXE = 500007, MOD = 1000*1000*1000+7;

static vector <int> G[MAXN];
static int pre[MAXN], ojc[MAXN], low[MAXN], st[MAXN], przy[MAXN], odl[MAXN];
static bool used[MAXN];
static vector <pair <int, int>> CC[MAXE];
static stack <pair <int, int>> S;

int n, m; 
int timer, dcccount;

pair <int, int> para(int a, int b)
{
  return {min(a,b),max(a,b)};
}

void dfs(int v, int root = 0)
{
  int synowie = 0;
  used[v] = true;
  pre[v] = ++timer;
  low[v] = pre[v];
  for(auto w : G[v])
  {
    if(w == ojc[v])
      continue;
    if(used[w] == true)
    {
       if(pre[w] < pre[v] and ojc[v] != w)
         S.push(para(v,w));
       low[v] = min(low[v], pre[w]);
       continue;
    }
    synowie++;
    //cerr << v << synowie << "\n";
    S.push(para(v,w));
    ojc[w] = v;
    dfs(w);
    if(low[w] >= pre[v])
    {
       dcccount++;
       do
       {
          CC[dcccount].push_back(S.top());
          S.pop();
       }while(CC[dcccount].back() != para(v,w));
    }
    low[v] = min(low[v], low[w]);  
  }  
}

void znajdzdwuspojne()
{
  for(int i=1; i<=n; i++)
    if(used[i] == false)
      dfs(i,i);
  /*/
  cerr << dcccount << "\n";
  for(int i=1; i<=dcccount; i++)
  {
    cerr << "----------\n";
    for(auto ele : CC[i])
      cerr << "(" << ele.first << ", " << ele.second  << ")" << "\n";
  }
  /*/
}

int T1;
vector <int> T2;
vector <pair <int, int>> T3;
int T4;

void identyfikujdwuspojne()
{
  // 1 - krawedz
  // 2 - cykl
  // 3 - zbior sciezek
  // 4 - inne

  for(int i=1; i<=dcccount; i++)
  {
    //czy jest krawdzia
    
    if((int)CC[i].size() == 1)
    {
      T1++;
      continue;
    }

    
    
    //czy jest cyklem
 
    bool czycykl = true;

    vector <int> V;
    for(int j=0; j<(int)CC[i].size(); j++)
    {
      if(przy[CC[i][j].first] != i) 
        V.push_back(CC[i][j].first);
      if(przy[CC[i][j].second] != i) 
        V.push_back(CC[i][j].second);
      przy[CC[i][j].first] = i;
      przy[CC[i][j].second] = i;
    }

    for(auto v : V)
      st[v] = 0;
    for(int j=0; j<(int)CC[i].size(); j++)
    {
      st[CC[i][j].first]++;
      st[CC[i][j].second]++;
    }
    for(auto v : V)
    {
      //cerr << v << " " << st[v] << "\n";
      if(st[v] != 2)
        czycykl = false;
    }
    if(czycykl)
    {
       T2.push_back(CC[i].size());
       continue;
    }

    // czy jest zbior sciezek

    vector <int> F;

    for(auto v : V)
      if(st[v] > 2)
      {
        F.push_back(v);
        st[v] = 0;
      }

    if(F.size() != 2)
    {
      T4++;
      continue;
    }

    for(auto v : V)
      odl[v] = -1;

    queue <int> Q;
    Q.push(F[0]);
    odl[F[0]] = 0;
    while(!Q.empty())
    {
      int v = Q.front();
      Q.pop();
      for(auto w : G[v]) //czy to nie robi kwadratu dla gwiazdki?
      {
        if(przy[w] != i)
          continue;
        if(odl[w] == -1)
        {
          odl[w] = odl[v]+1;
          Q.push(w);
        }
      }
    }
    bool rowne = true;
    for(auto v : V)
      if(v != F[1] and odl[v] == odl[F[1]])
        rowne = false;
    if(rowne)
    {
      int zlicz = 0;
      for(auto v : G[F[0]])
        if(przy[v] == i)
          zlicz++;
      T3.push_back({odl[F[1]], zlicz});
    }
    else
      T4++;
  }
}

bool drzewo()
{
  return T1 == dcccount;
}

void napraw(int &a, int b)
{
  if(a == -1)
    a = b;
  else if(a != b)
    a = -2;
}

long long countthem = 0;

long long po2(int a)
{
  return 1LL*a*(a-1)/2;
}

int dlugosc()
{
  if((!T2.empty()) and (!T3.empty()))
  {
    int kan = T3[0].first;
    for(auto t : T2)
      if(t != 2*kan)
        return -1;
    for(auto t : T3)
      if(t.first != kan)
        return -1;
    countthem += (int)T2.size();
    for(auto t : T3)
      countthem += po2(t.second);
    return 2*kan; 
  }
  if(!T2.empty())
  { 
    int kan = T2[0];
    for(auto t : T2)
      if(t != kan)
        return -1;
    countthem += (int)T2.size();
    return kan;
  }
  if(!T3.empty())
  { 
    int kan = T3[0].first;
    for(auto t : T3)
      if(t.first != kan)
        return -1;
    for(auto t : T3)
      countthem += po2(t.second);
    return 2*kan; 
  }
  assert(true);
  return -7;
}

int main()
{
  scanf("%d%d", &n, &m);
  while(m--)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    G[a].push_back(b);
    G[b].push_back(a);
  }  
  znajdzdwuspojne();
  identyfikujdwuspojne();
  cerr << T1 << " " << T2.size() << " "  << T3.size() << " " <<  T4 << "\n";
  if(drzewo() == true)
  {
    puts("BRAK");
    return 0;
  }
  if(T4)
  {
    puts("NIE");
    return 0;
  }
  int dl = dlugosc();
  if(dl == -1)
  {
    puts("NIE");
    return 0;
  }
  puts("TAK");
 
  //zaczynamy w dowolnym miejscu 
  //i w dowolna strone
  countthem *= 2LL*dl;
  countthem %= MOD;
  printf("%d %lld\n", dl, countthem);
}
