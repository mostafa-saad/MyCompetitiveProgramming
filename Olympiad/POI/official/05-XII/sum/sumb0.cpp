/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SUM (Sumy Fibbonacciego)                       *
 *   Plik:                sumb0.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie niepoprawne                        *
 *                        Rozwi±zanie przekszta³ca liczby do systemu     *
 *                        dziesiêtnego, dodaje i sprawadza do systemu    *
 *                        Zeckendorfa. Obliczenia wykonywane na typie    *
 *                        64-bitowym (long long).                        *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
using namespace std;

long long fib[1000100];
int slowo1[1000100];
int slowo2[1000100];
int wynik[1000100];
int n, m, dlugosc_wyniku;
long long liczba1, liczba2;


int max(int x, int y)
{
  return (x > y ? x : y);
}

void czysc()
{
  for (int i = 0; i < 1000; i++)
    wynik[i] = 0;
}

void wczytaj()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &slowo1[i]);
  }
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf("%d", &slowo2[i]);
  }
  return;
}

void wypisz_wynik()
{
  printf("%d", dlugosc_wyniku);
  for (int i = 0; i < dlugosc_wyniku; i++)
    printf(" %d", wynik[i]);
  printf("\n");
  return;
}

int main()
{
  fib[0] = 1;
  fib[1] = 2;
  wczytaj();
  // wyznaczanie liczb Fibonacciego
  for (int i = 2; i < max(n, m) + 4; i++)
    fib[i] = fib[i - 1] + fib[i - 2];
  // zamiana na system dziesietny
  liczba1 = 0;
  for (int i = 0; i < n; i++)
    if (slowo1[i] == 1)
      liczba1 += fib[i];
  liczba2 = 0;
  for (int i = 0; i < m; i++)
    if (slowo2[i] == 1)
      liczba2 += fib[i];
  long long suma = liczba1 + liczba2;
  // i z powrotem
  int wart = 0;
  while (fib[wart] <= suma) {
    wart++;
  }
  wart--;
  dlugosc_wyniku = wart;
  for (int i = dlugosc_wyniku; i >= 0; i--) {
    if (fib[i] <= suma) {
      suma -= fib[i];
      wynik[i] = 1;
    }
    else
      wynik[i] = 0;
  }
  dlugosc_wyniku++;
  wypisz_wynik();
  return 0;
}
