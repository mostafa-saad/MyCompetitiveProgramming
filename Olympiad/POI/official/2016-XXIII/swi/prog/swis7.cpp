/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Swiateczny lancuch                                 *
 *   Autor programu:       Krzysztof Kiljan                                   *
 *   Zlozonosc czasowa:    O(sum(l_i))                                        *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                         Tworzymy przy wczytywaniu caly graf,               *
 *                         a nastepnie puszczamy,                             *
 *                         z kazdego nieodwiedzonego wierzcholka dfs          *
 *                         by policzyc ilosc kolorow.                         *
 *****************************************************************************/

#include <cstdio>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 500013;

int n, m, a, b, l;

vector<int> E[MAXN];
bool vis[MAXN];


void addRange(int a, int b, int len)
{
  for(int i = 0; i < len; i++)
  {
    E[a+i].push_back(b+i);
    E[b+i].push_back(a+i);
  }
}

void readInput()
{
  for(int i = 0; i < MAXN; i++)
    vis[i] = false;

    scanf("%d%d", &n, &m);

    for(int i = 0; i < m; i++)
    {
      scanf("%d %d %d", &a, &b, &l);
      a--;
      b--;
      addRange(a, b, l);
    }
}

void dfs(int v)
{
  vis[v] = true;

  for(vector<int>::iterator it = E[v].begin(); it != E[v].end(); it++)
  {
    if(!vis[*it])
      dfs(*it);
  }
}

void solve()
{
  int ans = 0;

  for(int i = 0; i < n; i++)
  {
    if(!vis[i])
    {
      ans++;
      dfs(i);
    }
  }

  printf("%d\n", ans);
}

int main()
{
    readInput();
    solve();
    return 0;
}
