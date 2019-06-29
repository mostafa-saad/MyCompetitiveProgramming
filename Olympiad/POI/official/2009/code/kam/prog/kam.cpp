/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kamyki (KAM)                                              *
 *   Plik:     kam.cpp                                                   *
 *   Autor:    Szymon Wrzyszcz                                           *
 *   Opis:     Rozwiazanie wzorcowe O(n)                                 *
 *                                                                       *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

const int MAXN = 1000; // max. liczba kupek kamieni

int a[MAXN+1]; // liczba kamieni na poszczegolnych kupkach
int d[MAXN+1]; // odwrocony ciag roznic rozmiarow kolejnych kupek kamieni

int main() {
  int u;       // liczba ustawien poczatkowych do przeanalizowania
  scanf("%d", &u);
  for (int i=0; i<u; i++) {
    int n;                   // liczba kupek kamieni
    int x = 0;               // xor d[1], d[3], ...
    
    scanf("%d", &n);
    for (int j=1; j<=n; j++)
      scanf("%d", &a[j]);
    
    for (int j=1; j<n; j++)  // wyznaczanie ciagu d
      d[j] = a[n-j+1] - a[n-j];
    d[n] = a[1];
    
    for (int j=1; j<=n; j+=2)// xor-uj elementy o nieparzystych indeksach
      x ^= d[j];
      
    puts(x?"TAK":"NIE");
  }
  return 0;
}
