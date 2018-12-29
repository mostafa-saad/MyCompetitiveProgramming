/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                kryb5.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Algorytm o z³o¿ono¶ci O(sqrt(iloczyn a_i)).    *
 *                        Uznany formalnie za b³êdny, gdy¿ mo¿e nie      *
 *                        mie¶ciæ siê w pamiêci.                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_N 50
#define MAX_K 2000000

int n;
unsigned int a[MAX_N], t[MAX_N];
unsigned long long wynik;
unsigned int lewy[MAX_N], prawy[MAX_N];
unsigned long long L[MAX_K], P[MAX_K];
int l, p;

void sprawdzl()
{
  unsigned int w = 0;
  for (int i = 0; i < l; i++)
    w ^= t[i];
  L[w]++;
} /* sprawdzl */

void brutalnyl(int poz)
{
  if (poz == l)
    sprawdzl();
  else
  for (unsigned int i = 0; i <= lewy[poz]; i++)
  {
    t[poz] = i;
    brutalnyl(poz + 1);
  } /* for */
} /* brutalnyl */

void sprawdzp()
{
  unsigned int w = 0;
  for (int i = 0; i < p; i++)
    w ^= t[i];
  P[w]++;
} /* sprawdzp */

void brutalnyp(int poz)
{
  if (poz == p)
    sprawdzp();
  else
  for (unsigned int i = 0; i <= prawy[poz]; i++)
  {
    t[poz] = i;
    brutalnyp(poz + 1);
  } /* for */
} /* brutalnyp */


int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%u", &a[i]);
  sort(a, a + n);
  l = p = 0;
  for (int i = 0; i < n; i++)
    if (i % 2)
      prawy[p++] = a[i];
    else
      lewy[l++] = a[i];
  wynik = 0;
  memset(L, 0, sizeof(L));
  memset(P, 0, sizeof(P));
  brutalnyl(0);
  brutalnyp(0);
  for (int i = 0; i < MAX_K; i++)
    wynik += L[i] * P[i];
  printf("%llu\n", wynik - 1);
  return 0;
} /* main */
