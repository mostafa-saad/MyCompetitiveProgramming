/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *   Opis:              Rozwiazanie niepoprawne                          *
 *                      Przechodzimy graf DFS-em, gdy napotkamy cykl     *
 *                      zawierajacy wierzcholek o numerze <=k            *
 *                      usuwamy dowolna krawedz tego cyklu               *
 *                                                                       *
 *************************************************************************/

#include <vector>
#include <iostream>
using namespace std;

#define MAXN 1000001
typedef pair<int, int> PII;

vector<int> krawedzie[MAXN]; /* dany graf w postaci list sasiedztwa */
vector<PII> zablokowane; /* krawedzie, ktore zostana zablokowane */
int n, m, k, visit[MAXN];

void wczytaj_dane() {
  cin >> n >> m >> k;
  for (int i = 1; i <= n; ++i) visit[i] = 0;
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    krawedzie[a].push_back(b);
    krawedzie[b].push_back(a);
  }
}

void DFS(int v, int depth, int last) {
  vector<int>::iterator it;
  visit[v] = depth;
  for (it = krawedzie[v].begin(); it < krawedzie[v].end(); ++it) {
    if (visit[*it] == 0) DFS(*it, depth+1, (*it <= k) ? *it : last);
    else if (visit[*it] < depth - 1 && visit[last] >= visit[*it]) {
      if (v < *it) zablokowane.push_back(make_pair(v, *it));
      else zablokowane.push_back(make_pair(*it, v));
    }
  }
}

int main() {
  wczytaj_dane();
  for (int i = 1; i <= k; ++i) if (visit[i] == 0) DFS(i, 1, i);
  /* wypisujemy wynik */
  cout << zablokowane.size() << endl;
  for (size_t i = 0; i < zablokowane.size(); ++i)
    cout << zablokowane[i].first << " " << zablokowane[i].second << endl;
  return 0;
}
