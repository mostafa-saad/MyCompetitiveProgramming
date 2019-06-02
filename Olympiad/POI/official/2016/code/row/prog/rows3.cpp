/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Rownowazne programy                                *
 *   Autor programu:       Bartosz Kostka                                     *
 *   Zlozonosc czasowa:    O(n^2 log(n))                                      *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/

#include "bits/stdc++.h"
using namespace std;

const int MAXN = 100007;
const int MAXK = 1007;
unordered_set <int> G[MAXN];
vector <int> W[2][MAXN];
int cia[2][MAXN], sto[2][MAXN], sor[2][MAXN];
int n, k, m;

// nie umiem zrobic tego ladniej ; ___ ;
// zmienna globalna do klasy comperatora
int te;

class cmp {
    //int pp;
  public:
    //cmp(int e){ pp = e; }
    bool operator()(int i, int j)
    {
      if(cia[te][i] == cia[te][j])
        return i>j;
      return cia[te][i] > cia[te][j];
    }
};

void posortuj(int e)
{
  te = e;
  for(int i=0; i<n; i++)
    for(int j=i+1; j<n; j++)
    {
      int a = cia[e][i], b = cia[e][j];
      if(G[a].find(b) != G[a].end())
      {
        W[e][i].push_back(j);
        sto[e][j]++;
      }
    }
  priority_queue <int, vector <int>, cmp> Q;
  for(int i=0; i<n; i++)
    if(sto[e][i] == 0)
      Q.push(i);
  int nr = 0;
  while(!Q.empty())
  {
    int v = Q.top();
    sor[e][nr++] = cia[e][v];
    Q.pop();
    for(int i=0; i<(int)W[e][v].size(); i++)
    {
      int w = W[e][v][i];
      sto[e][w]--;
      if(sto[e][w]==0)
        Q.push(w);
    }
  }
}

bool czy()
{
  for(int i=0; i<n; i++)
    cerr << sor[0][i] << " ";
  cerr << "\n";
  for(int i=0; i<n; i++)
    if(sor[0][i] != sor[1][i])
      return false;
  return true;
}

int main()
{
  cin >> n >> k >> m;
  while(m--)
  {
    int a, b;
    cin >> a >> b;
    G[a].insert(b);
    G[b].insert(a);
  }
  for(int e=0; e<2; e++)
  {
    for(int i=0; i<n; i++)
      cin >> cia[e][i];
    posortuj(e);
  }
  puts(czy() ? "TAK" : "NIE");
}
