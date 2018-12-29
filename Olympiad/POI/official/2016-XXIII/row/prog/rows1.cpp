/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Rownowazne programy                                *
 *   Autor programu:       Bartosz Kostka                                     *
 *   Zlozonosc czasowa:    O(n!)                                              *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/


#include "bits/stdc++.h"

using namespace std;

const int MAXN = 1007; // 100007
const int MAXK = 1007;
vector <int> W[2][MAXK];
bool blo[MAXN][MAXN];
vector <int> cia[2];
int n, k, m;
queue <vector <int> > Q;
map <vector <int>, bool> odw;

bool czy()
{
  for(int i=1; i<=k; i++)
    if((int)W[0][i].size() != (int)W[1][i].size())
      return false;
  if(cia[0] == cia[1])
    return true;
  odw[cia[0]] = true;
  Q.push(cia[0]);
  while(!Q.empty())
  {
    auto v = Q.front();
    Q.pop();
    for(int i=0; i<n-1; i++)
      if(blo[v[i]][v[i+1]] == false)
      {
        swap(v[i], v[i+1]);
        if(odw.find(v) == odw.end())
        {
          if(v == cia[1])
            return true;
          odw[v] = true;
          Q.push(v);
        }
        swap(v[i], v[i+1]);
      }
  }
  return false;
}

int main()
{
  cin >> n >> k >> m;
  while(m--)
  {
    int a, b;
    cin >> a >> b;
    blo[a][b] = true;
    blo[b][a] = true;
  }
  for(int e=0; e<2; e++)
  {
    cia[e].resize(n);
    for(int i=0; i<n; i++)
    {
      cin >> cia[e][i];
      W[e][cia[e][i]].push_back(i);
    }
  }
  puts(czy() ? "TAK" : "NIE");
}
