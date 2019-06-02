/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Nadajniki                                          *
 *   Autor programu:       Bartek Kostka                                      *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 200007;
vector <int> G[MAXN];
bool odw[MAXN];

const int INF = MAXN;

struct vertex
{
  //to cur bottom
  int war[3][3][3];

  vertex()
  {
    for(int to=0; to<3; to++)
      for(int cu=0; cu<3; cu++)
        for(int bo=0; bo<3; bo++)
          war[to][cu][bo] = INF;
  }

  vertex leaf()
  {
    vertex x;
    x.war[2][0][0] = 0;
    return x;
  }

  vertex merge(const vertex &a, const vertex &b)
  {
    vertex res;
    for(int to1=0; to1<3; to1++)
      for(int cu1=0; cu1<3; cu1++)
        for(int bo1=0; bo1<3; bo1++)
          for(int to2=0; to2<3; to2++)
            for(int cu2=0; cu2<3; cu2++)
              for(int bo2=0; bo2<3; bo2++)
              {
                int to = max(0, max(to1-cu2, to2-cu1));
                int cu = min(2, cu1 + cu2);
                int bo = max(bo1, bo2);
                res.war[to][cu][bo] = min(res.war[to][cu][bo], a.war[to1][cu1][bo1] + b.war[to2][cu2][bo2]);
              }
    return res;
  }

  vertex construct(vertex x)
  {
    vertex res;
    for(int no=0; no<3; no++)
      for(int bo=0; bo<3; bo++)
      {
        if(no < bo)
          continue;
        for(int cu=0; cu<3; cu++)
          for(int to=0; to<3; to++)
          {
            if(no != 0)
              res.war[0][no][0] = min(res.war[0][no][0], no + x.war[to][cu][bo]);
            else
              res.war[2-cu][no][to] = min(res.war[2-cu][no][to], no + x.war[to][cu][bo]);
          }
      }
    return res;
  }

  vertex merge(vector <int> x, vertex *dp)
  {
    if((int)x.size() == 0)
      return vertex().leaf();
    vertex y = dp[x.front()];
    for(int i=1; i<(int)x.size(); i++)
      y = merge(y, dp[x[i]]);
    return construct(y);
  }
};

vertex dp[MAXN];

void wypisz(int x)
{
  for(int cu=0; cu<3; cu++)
  {
    printf("cu = %d\n", cu);
    printf("bo / to |      0 |      1 |      2 |\n");
    for(int bo=0; bo<3; bo++)
      printf("      %d | %6d | %6d | %6d |\n", bo, dp[x].war[0][cu][bo], dp[x].war[1][cu][bo], dp[x].war[2][cu][bo]);
    printf("\n");
  }
}

void dfs(int v)
{
  vector <int> tmp;
  odw[v] = true;
  for(auto w : G[v])
    if(odw[w] == false)
    {
      dfs(w);
      tmp.push_back(w);
    }
  dp[v] = vertex().merge(tmp, dp);
}

int main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;
  for(int i=1; i<n; i++)
  {
    int a, b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  dfs(1);
  int res = INF;
  for(int to=0; to<3; to++)
    for(int cu=0; cu<3; cu++)
      res = min(res, dp[1].war[to][cu][0]);
  cout << res << "\n";
}
