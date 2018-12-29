/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Zapytania (ZAP)                                            *}
{*   Plik:    zaps1.cpp                                                  *}
{*   Autor:   Jakub Pawlewicz                                            *}
{*   Opis:    Rozwiazanie naiwne O(n m^2 log m)                          *}
{*                                                                       *}
{*************************************************************************/
#include <algorithm>
#include <cstdio>

using namespace std;

static inline
int gcd(int a, int b)
{
  int shift = 0;
  while (true) {
    if ((a & 1) == 0) {
      if ((b & 1) == 0) {
  shift++;
  a >>= 1;
  b >>= 1;
      } else {
  do {
    a >>= 1;
  } while ((a & 1) == 0);
  break;
      }
    } else {
      while ((b & 1) == 0) {
  b >>= 1;
      }
      break;
    }
  }
  while (a != b) {
    if (a < b)
      swap(a, b);
    a -= b;
    do {
      a >>= 1;
    } while ((a & 1) == 0);
  }
  return a << shift;
}

int main()
{
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int a, b, d;
    scanf("%d%d%d", &a, &b, &d);
    a /= d;
    b /= d;
    int r = 0;
    for (int x = 1; x <= a; x++)
      for (int y = 1; y <= b; y++)
  if (gcd(x, y) == 1)
    r++;
    printf("%d\n", r);
  }
  return 0;
}
