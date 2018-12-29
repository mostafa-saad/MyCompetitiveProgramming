/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Drogi zmiennokierunkowe                            *
 *   Autor programu:       Bartosz Kostka                                     *
 *   Zlozonosc czasowa:    O(n(n+m))                                          *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/


#include "bits/stdc++.h"

using namespace std;

const int MAXN = 500007;
int n, m;
// G[0] - graf normalny
// G[1] - graf obrocony
vector <int> G[2][MAXN];
bool odw[2][MAXN];

void dfs(int v, int a)
{
  odw[a][v] = true;
  for(auto w : G[a][v])
    if(not(odw[a][w]))
      dfs(w, a);
}

int main()
{
  cin >> n >> m;
  while(m--)
  {
    int a, b;
    cin >> a >> b;
    G[0][a].push_back(b);
    G[1][b].push_back(a);
  }
  vector <int> ANS;
  for(int i=1; i<=n; i++)
  {
    memset(odw, 0, sizeof(odw));
    dfs(i, 0);
    dfs(i, 1);
    bool dobry = true;
    for(int j=1; j<=n; j++)
      if(not(odw[0][j] or odw[1][j]))
        dobry = false;
    if(dobry)
      ANS.push_back(i);
  }
  cout << (int)ANS.size() << "\n";
  bool isfirst = true;
  for(auto a : ANS)
  {
    if(isfirst)
      isfirst = false;
    else
      cout << " ";
    cout << a;
  }
  cout << "\n";
}
