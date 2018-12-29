/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: AUT (Autobus)                                  *
 *   Plik:                auts1.cpp                                      *
 *   Autor:               Piotr Stanczyk                                 *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                        Zlozonosc: O(k^2)                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#define INF 2000000000
using namespace std;

struct przyst {
  int x, y, p;
};

struct warstwa {
  int y, p;
};

bool cmp(const przyst & a, const przyst & b)
{
  if (a.x == b.x)
    return a.y < b.y;
  return a.x < b.x;
}

vector < przyst > l;
vector < warstwa > res[2];
przyst pz;

int main()
{
  int k;
  pz.p = 0;
  pz.x = pz.y = 1;
  l.push_back(pz);
  scanf("%d %d %d", &pz.x, &pz.y, &k);
  l.push_back(pz);
  for (int x = 0; x < k; x++) {
    scanf("%d %d %d", &pz.x, &pz.y, &pz.p);
    l.push_back(pz);
  }
  sort(l.begin(), l.end(), cmp);
  int val, vala, pos = INF;
  warstwa wa;
  for (int x = l.size() - 1; x >= 0; x--) {
    if (pos != l[x].x) {
      while (res[0].size()) {
        if (val < res[0][res[0].size() - 1].p) {
          wa.p = val = res[0][res[0].size() - 1].p;
          wa.y = res[0][res[0].size() - 1].y;
          res[1].push_back(wa);
        }
        res[0].pop_back();
      }
      pos = l[x].x;
      val = 0, vala = 0;
      reverse(res[1].begin(), res[1].end());
      swap(res[0], res[1]);
    }
    while (res[0].size() && res[0][res[0].size() - 1].y >= l[x].y) {
      if (val < res[0][res[0].size() - 1].p) {
        wa.p = val = res[0][res[0].size() - 1].p;
        wa.y = res[0][res[0].size() - 1].y;
        vala = max(vala, val);
        res[1].push_back(wa);
      }
      res[0].pop_back();
    }
    wa.y = l[x].y;
    vala = wa.p = vala + l[x].p;
    res[1].push_back(wa);
  }
  printf("%d\n", vala);
  return 0;
}
