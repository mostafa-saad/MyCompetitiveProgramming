/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Osie (OSI)                                                 *}
{*   Plik:    osib5.cpp                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie dla kazdego punktu, przez ktory moze           *}
{*            przechodzic os symetii, weryfikuje symetrycznosc tylko     *}
{*            stalej liczby punktow (zwracany wynik moze byc wiekszy od  *}
{*            faktycznego)                                               *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <math.h>

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

LL len(POINT& a, POINT& b) {
  return sqr(a.x - b.x) + sqr(a.y - b.y);
}

int main() {
    int testy;
    scanf("%d", &testy);
    while(testy--) {
        int n;
    scanf("%d", &n);
    vector<POINT> v(2*n);
    for(int x = 0; x < n; x++) {
      scanf("%d %d", &v[2*x].x, &v[2*x].y); 
      v[2*x].x <<= 1;
      v[2*x].y <<= 1;
    }
    for(int x = 0; x < n; x++) {
      v[2*x+1].x = (v[2*x].x + v[Cyc(2*x+2, 2*n)].x) >> 1;
      v[2*x+1].y = (v[2*x].y + v[Cyc(2*x+2, 2*n)].y) >> 1;
    }
    n *= 2;

    int res = 0;
    for(int x = 0; x < n; x++) {
      if (len(v[x], v[Cyc(x+1, n)]) == len(v[x], v[Cyc(x-1, n)])) {
        bool symetria = true;
        for(int y = (int) sqrt((double) n); y > 0; y--) {
          int v1 = rand() % n;
          int v2 = Cyc(2*x - v1, n);
          if (len(v[v1], v[x]) != len(v[v2], v[x]) ||
            len(v[v1], v[Cyc(x+1, n)]) != len(v[v2], v[Cyc(x-1, n)])) {
            symetria = false;
            break;
          }
        }
        if (symetria) {
          res++;
        }
      }
    }
    printf("%d\n", res/2);
    }
    return 0;
}
