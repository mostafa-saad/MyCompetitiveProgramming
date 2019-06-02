/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n^2 + m)                                       *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Spojne i las budujemy przy pomocy naiwnej        *
 *                      implementacji zbiorow rozlacznych                *
 *                                                                       *
 *************************************************************************/

#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define MAXN 1000001
typedef pair<int, int> PII;
typedef struct elem {
  int x;
  elem * nx;
} elem;

void push(elem ** p, int x) {
  elem *tmp = (elem*) malloc(sizeof(elem));
  tmp->x = x;
  tmp->nx = *p;
  *p = tmp;
}

int pop(elem ** p) {
  elem *tmp = (*p)->nx;
  int x = (*p)->x;
  free(*p);
  *p = tmp;
  return x;
}

vector<PII> kandydaci; /* krawedzie o poczatku o numerze <=k */
vector<PII> zablokowane; /* krawedzie, ktore zostana zablokowane */
int numer[MAXN]; /* do ktorego zbioru nalezy miasto */
elem * zbior[MAXN]; /* miasta nalezace do zbioru */
int n, m, k;

void make_union(int x, int y) {
  int a = numer[x], b = numer[y];
  if (a != b)
    while (zbior[b] != NULL) {
      push(zbior + a, pop(zbior + b));
      numer[zbior[a]->x] = a;
    }
}

void wyznacz_spojne_i_kandydatow() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) {
    numer[i] = i;
    zbior[i] = NULL;
    push(zbior + i, i);
  }
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
    if (numer[it->first] == numer[it->second])
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

