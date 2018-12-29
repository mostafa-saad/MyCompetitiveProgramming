/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Igor Adamski                                     *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Usuwa krawedzie tak, zeby z kazdego wyroznionego *
 *                      wierzcholka wychodzila tylko jedna.              *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;

const int MAXN = 1000000;

vector<int> G[MAXN+1];

typedef pair<int,int> PII;

vector<PII> ans;

int n, m, k;

int main(int argc, char *argv[]) {
  scanf("%d %d %d", &n, &m, &k);
  while(m--)
  {
    int a, b;
    scanf("%d %d", &a, &b);
    G[a].push_back(b);
    G[b].push_back(a);
  }
  for(int i=1;i<=k;++i)
    for(int j=0;j<(int)G[i].size()-1;++j)
    {
      if(G[i][j] > k)
        swap(G[i][j], G[i][G[i].size()-1]);
      ans.push_back(make_pair(min(i, G[i][j]), max(i, G[i][j])));
    }
  for(printf("%d\n", ans.size());!ans.empty();ans.pop_back())
    printf("%d %d\n", ans.back().first, ans.back().second);
  return 0;
}

