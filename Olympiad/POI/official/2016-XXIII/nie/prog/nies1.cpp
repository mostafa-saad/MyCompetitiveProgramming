/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Niebanalne podroze                                 *
 *   Autor:                Bartosz Kostka                                     *
 *   Opis:                 Rozwiazanie wolne - sprawdzamy kazdy cykl prosty   *
 *****************************************************************************/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 500007;

static vector <int> G[MAXN], V;
int n, m;
int ilecykli;
static vector <pair <int, int> > A;
bool used[MAXN];

void go(int a, int b)
{
  if(a==b)
  {
    int v = V.back();
    for(auto w : G[v])
      if(w == V.front())
      {
        for(auto x : V)
          cerr << x << " ";
        cerr << "\n";
        ilecykli++;
      }
    return;
  }
  int v = V.back();
  for(auto w : G[v])
    if(used[w] == false)
    {
      used[w] = true;
      V.push_back(w);
      go(a+1,b);
      V.pop_back();
      used[w] = false;
    }
}

void check(int a)
{
  ilecykli = 0;
  for(int i=1; i<=n; i++)
  {
    V.push_back(i);
    used[i] = true;
    go(1,a);
    V.pop_back();
    used[i] = false;
  }
  if(ilecykli)
    A.push_back({a, ilecykli});
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
  //ignorujemy krawedzie (i=2)
  for(int i=3; i<=n; i++)
  {
    check(i);
  }
  if((int)A.size() == 0)
    puts("BRAK");
  else if((int)A.size() > 1)
    puts("NIE");
  else
  {
    puts("TAK");
    printf("%d %d\n", A[0].first, A[0].second);
  }
}
