/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O((n + m) * log^*(n + m))                        *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                      Spojne skladowe i las budujemy przy pomocy lasu  *
 *                      zbiorow rozlacznych (find-union)                 *
 *                                                                       *
 *************************************************************************/

#include <vector>
#include <cstdio>
using namespace std;

#define MAXN 1000001
typedef pair<int, int> PII;

vector<PII> kandydaci; /* krawedzie o poczatku o numerze <=k */
vector<PII> zablokowane; /* krawedzie, ktore zostana zablokowane */
int ojciec[MAXN]; /* las zbiorow rozlacznych */
int rozmiar[MAXN]; /* rozmiary zbiorow rozlacznych */
int n, m, k;

int find(int x) {
  if (x != ojciec[x]) ojciec[x] = find(ojciec[x]);
  return ojciec[x];
}

void make_union(int x, int y) {
  int a = find(x), b = find(y);
  if (a != b) {
    if (rozmiar[a] > rozmiar[b]) {
      ojciec[b] = a;
      rozmiar[a] += rozmiar[b];
    } else {
      ojciec[a] = b;
      rozmiar[b] += rozmiar[a];
    }
  }
}

void wyznacz_spojne_i_kandydatow() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) { ojciec[i] = i; rozmiar[i] = 1; }
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    if (a > k)
      make_union(a, b);
    else
      kandydaci.push_back(make_pair(a, b));
  }
}

void wybierz_zablokowane() {
  vector<PII>::iterator it;
  for (it = kandydaci.begin(); it != kandydaci.end(); ++it)
    if (find(it->first) == find(it->second))
      zablokowane.push_back(*it);
    else
      make_union(it->first, it->second);
}

int main() {
  wyznacz_spojne_i_kandydatow();
  wybierz_zablokowane();
  /* wypisujemy wynik */
  printf("%d\n", (int)zablokowane.size());
  for (size_t i = 0; i < zablokowane.size(); ++i)
    printf("%d %d\n", zablokowane[i].first, zablokowane[i].second);
  return 0;
}

