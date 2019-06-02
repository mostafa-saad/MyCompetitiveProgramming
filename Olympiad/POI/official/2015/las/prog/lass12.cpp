/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Lasuchy                                            *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O(2 ^ n)                                           *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 rozwiazanie wolne                                  *
 *                                                                            *
 *****************************************************************************/

#include <cstdio>

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
  for(int i = 0; i < n; i++)
  {
    int x = policz(i);
    wyb[i] ^= 1;
    int y = policz(i);
    wyb[i] ^= 1;
    if(y > x)
      return false;
  }
  return true;
}

int main()
{
  scanf("%d", &n);
  if(n > 30)
    while(true)
      ;
  for(int i = 0; i < n; i++)
  {
    scanf("%d", tab + i);
    tab[i] *= 2;
  }
  for(int i = 0; i < (1 << n); i++)
  {
    for(int j = 0; j < n; j++)
      wyb[j] = (i & (1 << j)) >> j;
    if(ok())
    {
      for(int j = 0; j < n; j++)
      {
        if(j)
          printf(" ");
        printf("%d", ((j + wyb[j]) % n) + 1);
      }
      printf("\n");
      return 0;
    }
  }
  printf("NIE\n");
  return 0;
}
