/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O((n + m) * k)                                   *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Dla kolejnych miast kibicow szukamy DFS-em       *
 *                      cykli, ale maksymalna glebokosc = 5              *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<vector>
#include<set>
using namespace std;

#define MAXN 1000000

typedef pair<int,int> PII;

int n, m, k;
int osiagniete[MAXN+1], uzyte[MAXN+1];
vector<int> krawedzie[MAXN+1];
set<PII> zablokowane;

void wczytaj_dane() {
  ios_base::sync_with_stdio(0);
  cin >> n >> m >> k;
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    krawedzie[a].push_back(b);
    krawedzie[b].push_back(a);
  }
}

void DFS(int v, int depth) {
  if (depth > 5) return;
  osiagniete[v] = k;
  for (size_t j = 0; j < krawedzie[v].size(); ++j) {
    int w = krawedzie[v][j];
    if (osiagniete[w] != k) DFS(w, depth + 1);
  }
}

void zablokuj_drogi() {
  for (int i = 1; i <= n; ++i) { osiagniete[i] = 0; uzyte[i] = 0; }
  while (k > 0) {
    osiagniete[k] = k;
    for (size_t j = 0; j < krawedzie[k].size(); ++j) {
      int w = krawedzie[k][j];
      if (osiagniete[w] == k) {
        krawedzie[k][j--] = krawedzie[k].back();
        krawedzie[k].pop_back();
        for (size_t l = 0; l < krawedzie[w].size(); ++l)
          if (krawedzie[w][l] == k) {
            krawedzie[w][l--] = krawedzie[w].back();
            krawedzie[w].pop_back();
          }
        if (k < w) zablokowane.insert(make_pair(k, w));
        else zablokowane.insert(make_pair(w, k));
      } else DFS(krawedzie[k][j], 1);
    }
    --k;
  }
}

int main() {
  wczytaj_dane();
  zablokuj_drogi();
  cout << zablokowane.size() << endl;
  for (set<PII>::iterator it = zablokowane.begin(); it != zablokowane.end(); ++it)
    cout << it->first << " " << it->second << endl;
  return 0;
}
