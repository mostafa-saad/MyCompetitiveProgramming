/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kamyki (KAM)                                              *
 *   Plik:     kamb1.cpp                                                *
 *   Autor:    Szymon Wrzyszcz                                           *
 *   Opis:     Rozwiazanie niepoprawne. Zaklada, ze r_n=r_{n-2}=...=0    *
 *             jest warunkiem dostatecznym, zeby uklad byl przegrywajacy.*
 *                                                                       *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

const int MAXN = 1000; // max. liczba kupek kamieni

int a[MAXN+1]; // liczba kamieni na poszczegolnych kupkach

int main() {
  int u;       // liczba ustawien poczatkowych do przeanalizowania
  scanf("%d", &u);
  for (int i=0; i<u; i++) {
    int n;                   // liczba kupek kamieni
    scanf("%d", &n);
    if (n%2 == 0) {
      for (int j=0; j<n; j++)
        scanf("%d", &a[j]);
    } else {
      a[0] = 0;
      for (int j=1; j<=n; j++)
        scanf("%d", &a[j]);
      n++;
    }
    
    int wygra = 0;
    for (int j=0; j<n; j+=2)
      if (a[j] != a[j+1]) {
        wygra = 1;
        break;
      }
      
    puts(wygra?"TAK":"NIE");
  }
  return 0;
}
