/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Skalniak (SKA)                                             *}
{*   Plik:    skab7.cpp                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie zadania stosuje programowanie zachlanne        *}
{*            przetwarzajace kamienie w kolejnosci rosnacego minimow ze  *}
{*            wspolrzednych                                              *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

struct kamien {
  int x, y, w, nr;
};

bool cmp(const kamien& a, const kamien &b) {
  int m1 = min(a.x, a.y);
  int m2 = min(b.x, b.y);
  if (m1 != m2) return m1 < m2;
  return a.nr < b.nr;
}

int main() {
  int size;
  scanf("%d", &size);
  vector<kamien> l(size);
  string ans;
  ans.resize(size + 1);
  for(int x = 0; x < size; x++) {
    scanf("%d %d %d", &l[x].x, &l[x].y, &l[x].w);
    l[x].nr = x;
  }
  sort(l.begin(), l.end(), cmp);
  int minx = l[0].x, maxx = l[0].x, miny = l[0].y, maxy = l[0].y, waga = 0;
  ans[l[0].nr] = '0';
  for(int x = 1; x < size; x++) {
    int c1 = max(maxx, l[x].x) - min(minx, l[x].x) + max(maxy, l[x].y) - min(miny, l[x].y);
    int c2 = max(maxx, l[x].y) - min(minx, l[x].y) + max(maxy, l[x].x) - min(miny, l[x].x);
    if (c1 > c2) {
      waga += l[x].w;
      ans[l[x].nr] = '1';
      swap(l[x].x, l[x].y);
    } else {
      ans[l[x].nr] = '0';
    }
    maxx = max(maxx, l[x].x);
    minx = min(minx, l[x].x);
    maxy = max(maxy, l[x].y);
    miny = min(miny, l[x].y);
  }
  printf("%u %u\n%s\n", (unsigned int) 2 * (unsigned int) ((maxx - minx) + (maxy - miny)), waga, ans.c_str());
  return 0;
}
