/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Skalniak (SKA)                                             *}
{*   Plik:    ska2.cpp                                                   *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie wzorcowe.                                      *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <vector>
#include <string>

#define INF 2100000000

using namespace std;

struct kamien {
  int x, y, w;
};

int testujProstokat(int minx, int maxx, int miny, int maxy, const vector<kamien> &l, string &ans) {
  int waga = 0;
  ans.resize(l.size() + 1);
  for(int x = 0; x < l.size(); x++) {
    if (minx <= l[x].x && maxx >= l[x].x && miny <= l[x].y && maxy >= l[x].y) {
      ans[x] = '0';
    } else if (miny <= l[x].x && maxy >= l[x].x && minx <= l[x].y && maxx >= l[x].y) {
      ans[x] = '1';
      waga += l[x].w;
    } else {
      return INF;
    }
  }
  return waga;
}

int main() {
  int size;
  scanf("%d", &size);
  vector<kamien> l(size);
  int minmin = INF, minmax = INF, maxmin = -INF, maxmax = -INF;
  for(int x = 0; x < size; x++) {
    scanf("%d %d %d", &l[x].x, &l[x].y, &l[x].w);
    minmin = min(min(l[x].x, l[x].y), minmin);
    minmax = min(max(l[x].x, l[x].y), minmax);
    maxmin = max(min(l[x].x, l[x].y), maxmin);
    maxmax = max(max(l[x].x, l[x].y), maxmax);
  }
  string s1, s2;
  int w1, w2;
  w1 = testujProstokat(minmin, maxmin, minmax, maxmax, l, s1);
  w2 = testujProstokat(minmax, maxmax, minmin, maxmin, l, s2);
  if (w1 > w2) {
    w1 = w2;
    s1 = s2;
  }
  w2 = testujProstokat(minmin, maxmax, minmax, maxmin, l, s2);
  if (w1 > w2) {
    w1 = w2;
    s1 = s2;
  }
  w2 = testujProstokat(minmax, maxmin, minmin, maxmax, l, s2);
  if (w1 > w2) {
    w1 = w2;
    s1 = s2;
  }
  printf("%u %u\n%s\n", (unsigned int) 2 * (unsigned int) ((maxmax - minmax) + (maxmin - minmin)), w1, s1.c_str());
  return 0;
}
