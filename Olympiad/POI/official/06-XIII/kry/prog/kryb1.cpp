/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                kryb1.cpp                                      *
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
#define MAX_K 4000000

int n;
unsigned int a[MAX_N], t[MAX_N];
unsigned long long wynik;
unsigned int lewy[MAX_N], prawy[MAX_N];
unsigned int L[MAX_K], P[MAX_K];
int l, p, le, pr;

void sprawdzl()
{
  unsigned int w = 0;
  for (int i = 0; i < l; i++)
    w ^= t[i];
  L[le++] = w;
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
  P[pr++] = w;
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
  le = pr = 0;
  brutalnyl(0);
  brutalnyp(0);
  sort(L, L + le);
  sort(P, P + pr);
  int i = 0, j = 0, ile1, ile2;
  unsigned int a;
  while (i < le && j < pr)
  {
    if (L[i] <= P[j])
      a = L[i];
    else
      a = P[j];
    ile1 = ile2 = 0;
    while (i < le && L[i] == a)
    {
      i++;
      ile1++;
    } /* while */
    while (j < pr && P[j] == a)
    {
      j++;
      ile2++;
    } /* while */
    wynik += (unsigned long long)ile1 * ile2;
  } /* while */
  printf("%llu\n", wynik - 1);
  return 0;
} /* main */
