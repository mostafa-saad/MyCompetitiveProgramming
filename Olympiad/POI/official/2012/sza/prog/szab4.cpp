/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Szatnia                                          *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie bledne, w przypadku dwoch eventow    *
 *                      zaczynajacych sie w jednym momencie ustawiamy je *
 *                      w kolejnosci losowej, a nie "dodaj przedmiot",   *
 *                      "kradnij przedmiot"                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

const int MAXN = 1000123;
const int MAXK = 100000;
const int MAXKK = MAXK + 123;
const int INF = 2000000123;

int main() {
  std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > v;
  int poss[MAXKK]; // poss[i] -- jak dlugo bede miec pakiet o wartosci i
  int n, m, a, b, c, totWeight = 0, maxOrder = 0;
  assert(scanf("%d", &n));
  for(int i = 0; i < n; i++) {
    assert(scanf("%d%d%d", &a, &b, &c));
    v.push_back(std::make_pair(std::make_pair(b, c), std::make_pair(a, -1)));
    totWeight += a;
  }
  assert(scanf("%d", &m));
  for(int i = 0; i < m; i++) {
    assert(scanf("%d%d%d", &a, &b, &c));
    v.push_back(std::make_pair(std::make_pair(a, a + c), std::make_pair(b, i)));
    maxOrder = std::max(maxOrder, b);
  }
  totWeight = std::min(totWeight, maxOrder);
  std::sort(v.begin(), v.end());
  
  bool result[MAXN];
  for(int i = 0; i < m; i++) {
    result[i] = false;
  }
  for(int i = 1; i < MAXKK; i++) {
    poss[i] = -INF;
  }
  poss[0] = INF;
  for(size_t i = 0; i < v.size(); i++) {
    std::pair<std::pair<int, int>, std::pair<int, int> >& curr = v[i];
    if (curr.second.second > 0) {
      result[curr.second.second] = (poss[curr.second.first] > curr.first.second);
    } else {
      for(int p = totWeight - curr.second.first; p >= 0; p--) {
        if (poss[p] != -INF) {
          poss[p + curr.second.first] =
            std::max(poss[p + curr.second.first], std::min(poss[p], curr.first.second));
        }
      }
    }
  }
  for(int i = 0; i < m; i++) {
    result[i]?printf("TAK\n"):printf("NIE\n");
  }
  return 0;
}
