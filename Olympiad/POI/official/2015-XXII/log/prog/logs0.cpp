/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Logistyka                                          *
 *   Autor programu:       Bartosz Lukasiewicz                                *
 *   Zlozonosc czasowa:    O(nm)                                              *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                         w kazdym zapytaniu przegladamy wszystkich kierowcow*
 *****************************************************************************/


#include <iostream>
#include <cstdio>

typedef long long ll;

const int MAX_N=1e6;

int n, m, wpis[MAX_N+5];

void uaktualnij ()
{
  int k, a;
  scanf ("%d %d", &k, &a);
  wpis[k]=a;
}

void zapytaj ()
{
  int c, s;
  scanf ("%d %d", &c, &s);
  
  ll suma=0;
  for (int i=1; i<=n; i++)
    suma+=ll (std::min (wpis[i], s));
  
  printf ((suma>=ll (c)*ll (s)) ? "TAK\n" : "NIE\n");
}

int main ()
{
  scanf ("%d %d", &n, &m);
  
  while (m--)
  {
    char zdarzenie;
    scanf (" %c", &zdarzenie);
    
    if (zdarzenie=='U')
      uaktualnij ();
    else
      zapytaj ();
  }
  
  return 0;
}