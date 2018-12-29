/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Waga Czworkowa (WAG)                                       *}
{*   Plik:    wagb4.cpp                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Heurystyka ze wzgledu na liczbe dwojek w zapisie           *}
{*            czworkowym n.                                              *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX_LEN 2000

vector<int> p;
int wyn;

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
  for (int i = 0; i < (int)p.size(); i++)
    if (p[i] == 2)
      wyn++;
  printf("%d\n", wyn);
  return 0;
}
