/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Lasuchy                                            *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 rozwiazanie bledne                                 *
 *                         Kazdy wybiera tort na lewo                         *
 *                         Ustawienie wszystkich lasuchow losowo i            *
 *                         poprawianie 15 razy, przechodzac od prawej do lewej*
 *****************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int max_n = 1 * 1000 * 1000;

int tab[max_n + 5];
int wyb[max_n + 5];

int n;

int policz(int w)
{
  if(wyb[w] == 0)
  {
    if(wyb[(w + n - 1) % n] == 1)
      return tab[w] / 2;
    return tab[w];
  }
  if(wyb[(w + 1) % n] == 0)
    return tab[(w + 1) % n] / 2;
  return tab[(w + 1) % n];
}

bool ok()
{
  bool ret = false;
  for(int i = n - 1; i >= 0; i--)
  {
    int x = policz(i);
    wyb[i] ^= 1;
    int y = policz(i);
    if(x >= y)
      wyb[i] ^= 1;
    else
      ret = true;
  }
  return ret;
}

int main()
{
  scanf("%d", &n);
  srand(((n * n) ^ n) + 1);
  for(int i = 0; i < n; i++)
  {
    scanf("%d", tab + i);
    tab[i] *= 2;
    wyb[i] = rand() % 2;;
  }
  for(int i = 0; i < 15; i++)
    ok();
  for(int i = 0; i < n; i++)
  {
    if(i)
      printf(" ");
    printf("%d", ((i + wyb[i]) % n) + 1);
  }
  printf("\n");
  return 0;
}
