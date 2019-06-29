/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Waga Czworkowa (WAG)                                       *}
{*   Plik:    wag2.cpp                                                   *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwiazanie o zlozonosci O(log^2n), oparte na idei         *}
{*            programowania dynamicznego.                                *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define MD 1000000000

/* Z duzym zapasem */
#define MAX_LEN 5000

/* Liczba n podana od najmniej znaczacych cyfr czworkowych. */
vector<int> p;
/* t[i][j] - ile monet potrzeba, zeby wydac ilosc zlota okreslona
 * przez pierwsze i+1 czworkowych cyfr liczby n, jezeli nominal
 * 4^i lezy na przeciwnej szalce (j=0) lub tej samej (j=1, i wtedy
 * uzywamy nominalu 4^{i+1}). */
int t[MAX_LEN][2];
/* w[i][j] - liczba sposobow, na ktore mozna uzyskac zadeklarowana w t[i][j]
 * liczbe uzytych monet. */
int w[MAX_LEN][2];

/* Programowanie dynamiczne */
int dyna()
{
  t[0][0] = p[0];     w[0][0] = 1;
  t[0][1] = 4 - p[0]; w[0][1] = 1;
  int l = (int)p.size() - 1;
  for (int i = 1; i <= l; i++)
  {
    t[i][0] = min(t[i-1][0] + p[i], t[i-1][1] + p[i] + 1);
    if (t[i][0] == t[i-1][0] + p[i])
      w[i][0] += w[i-1][0];
    if (t[i][0] == t[i-1][1] + p[i] + 1)
      w[i][0] += w[i-1][1];
    w[i][0] %= MD;

    t[i][1] = min(t[i-1][0] + 4 - p[i], t[i-1][1] + 3 - p[i]);
    if (t[i][1] == t[i-1][0] + 4 - p[i])
      w[i][1] += w[i-1][0];
    if (t[i][1] == t[i-1][1] + 3 - p[i])
      w[i][1] += w[i-1][1];
    w[i][1] %= MD;
  }
  t[l][1]++;
  int x = min(t[l][0], t[l][1]), wyn = 0;
  if (x == t[l][0])
    wyn += w[l][0];
  if (x == t[l][1])
    wyn += w[l][1];
  return wyn % MD;
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
  printf("%d\n", dyna());
  return 0;
}
