/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Waga Czworkowa (WAG)                                       *}
{*   Plik:    wags4.cpp                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwiazanie o zlozonosci O(sqrt(n)+log^2(n)), ale ten      *}
{*            pierwiastek jest calkiem pesymistyczny..                   *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAX_LEN 2000
#define MD 1000000000

vector<int> p;
int l;
int wyn, wynik;

void generuj(int akt, int c, int i)
{
  if (i == l)
  {
    int u = p[i] + c;
    if (u >= 3)
      u = 5 - u;
    if (akt + u < wyn)
    {
      wyn = akt + u;
      wynik = 1;
    } else if (akt + u == wyn)
    {
      wynik++;
      if (wynik == MD)
        /* Tutaj i tak program w zyciu nie dojdzie ;-) */
        wynik = 0;
    }
    return;
  }
  int r = p[i] + c;
  if (r % 4 <= 2)
    generuj(akt + r % 4, r / 4, i + 1);
  if (r % 4 >= 2)
    generuj(akt + 4 - r % 4, r / 4 + 1, i + 1);
}


char n[MAX_LEN];
int len;

void odczyt()
{
  scanf("%s", n);
  len = strlen(n);
  reverse(n, n + len);
  while (len > 0)
  {
    int c = 0;
    for (int i = len - 1; i >= 0; i--)
    {
      int a = 10 * c + (n[i] - '0');
      n[i] = '0' + a / 4;
      c = a % 4;
    }
    p.push_back(c);
    while (len > 0 && n[len - 1] == '0')
      len--;
  }
}


int main()
{
  odczyt();
  l = (int)p.size() - 1;
  wyn = 1000000000;
  generuj(0, 0, 0);
  printf("%d\n", wynik);
  return 0;
}
