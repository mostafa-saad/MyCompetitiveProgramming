/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Osie (OSI)                                                 *}
{*   Plik:    osib1.cpp                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie niepoprawne. Zlozonosc obliczeniowa: O(n).     *}
{*            Program nie znajduje osi symetrii przechodzacych przez     *}
{*            boki wielokata                                             *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

typedef long long LL;

#define Cyc(a, b) ((a) < 0 ? (a+b) : (a) >= b ? (a-b) : a) 

struct POINT {
    int x, y;
    POINT(int x=0, int y=0) : x(x), y(y) {}
};

LL sqr(int a) {
    return LL(a) * LL(a);
}

LL Det(POINT a, POINT b, POINT c) {
    return LL(b.x - a.x) * LL(c.y - a.y) - LL(b.y - a.y) * LL(c.x - a.x);
}

int main() {
    int testy;
    scanf("%d", &testy);
    while(testy--) {
    int n;
    scanf("%d", &n);
    vector<POINT> v(n);
    for(int x = 0; x < n; x++)
  scanf("%d %d", &v[x].x, &v[x].y);
    vector<LL> rep(2*n);
    for(int x = 0; x < n; x++) {
  rep[2*x] = sqr(v[x].x - v[Cyc(x-1, n)].x) + sqr(v[x].y - v[Cyc(x-1, n)].y);
  rep[2*x+1] = LL(2) * Det(v[x], v[Cyc(x-1, n)], v[Cyc(x+1, n)]) +
      (Det(v[x], POINT(v[Cyc(x-1, n)].y - v[x].y + v[x].x, -v[Cyc(x-1, n)].x + v[x].x + v[x].y), v[Cyc(x+1, n)]) < 0 ? 1 : 0);
    }
    vector<int> rad(4*n, 0);
    int i = 1, j = 0, k;
    while(i < 4*n) {
  while(i+j+1 <= 4*n && i - j > 0 && rep[Cyc(i-j-1,2*n)] == rep[Cyc(i+j+1,2*n)]) j++;
  rad[i] = j;
  k = 1;
  while(rad[i-k] != j - k && k <= j) rad[i+k] = rad[i-k] <? j - k++;
  j = 0 >? j - k;
  i += k;
    }
    int res = 0;
    for(int x = 0; x < n; x++) if(rad[2*x+1+n] >= n) res++;
    printf("%d\n", res/2);
    }
    return 0;
}
