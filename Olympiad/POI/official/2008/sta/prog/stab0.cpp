/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Stacja (STA)                                              *
 *   Plik:     stab0.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie bledne, podobne do wzorcowego, ale zapomina   *
 *             o long longach.                                           *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 1000000

int n;
vector<int> graf[MAX_N];
int wezly[MAX_N];
bool odw[MAX_N];
/* Uwaga: Trzeba zastosowac typ 64-bitowy! */
int drogi[MAX_N];
int wynik[MAX_N];

/* Liczenie liczb wezlow i sum odleglosci w poddrzewach */
void faza1(int v)
{
  odw[v] = true;
  wezly[v] = 1;
  drogi[v] = 0;
  for (int i = 0; i < (int)graf[v].size(); i++)
  {
    int w = graf[v][i];
    if (!odw[w])
    {
      faza1(w);
      wezly[v] += wezly[w];
      drogi[v] += drogi[w] + wezly[w];
    }
  }
}

/* Liczenie wlasciwych wynikow, par to ojciec danego wezla */
void faza2(int v, int par)
{
  wynik[v] = wynik[par] - wezly[v] + (n - wezly[v]);
  for (int i = 0; i < (int)graf[v].size(); i++)
    if (graf[v][i] != par)
      faza2(graf[v][i], v);
}

int main()
{
  /* Odczyt */
  scanf("%d", &n);
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    graf[a].push_back(b);
    graf[b].push_back(a);
  }
  
  /* Dwukrotne programowanie dynamiczne */
  faza1(0);
  wynik[0] = drogi[0];
  for (int i = 0; i < (int)graf[0].size(); i++)
    faza2(graf[0][i], 0);
  
  /* Wyznaczanie i wypisywanie wyniku */
  int wyn = *max_element(wynik, wynik + n);
  for (int i = 0; i < n; i++)
    if (wynik[i] == wyn)
    {
      printf("%d\n", i + 1);
      break;
    }
  return 0;
}
