/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Mastermind II                                  *
 *   Plik:                mas1.cpp                                       *
 *   Autor:               Krzysztof Onak                                 *
 *************************************************************************/

// Opis: Generuje wszystkie wariacje bez powtórzeñ danej d³ugo¶ci
//       dopóki nie znajdzie rozwi±zania.

#include <iostream>
using namespace std;

const int MAX_U = 9;

// Struktura przechowuje informacje o ci±gu
struct Uklad {
  int ciag[MAX_U];
  int A, B;
  int pozycja[MAX_U];  // warto¶æ o indeksie i mówi, gdzie znajduje 
                       // siê cyfra (i+1); -1 gdy nigdzie
};

void wczytajUklad(int u, Uklad &uklad)
{
  for(int i = 0; i < MAX_U; ++i)
    uklad.pozycja[i] = -1;
  cin >> uklad.A >> uklad.B;
  for(int i = 0; i < u; ++i) {
    cin >> uklad.ciag[i];
    uklad.pozycja[--uklad.ciag[i]] = i;
  }
}

void wczytaj(int &u, Uklad *uklady)
{
  cin >> u;
  for(int i = 0; i < u; ++i)
    wczytajUklad(u, uklady[i]);
}

// Sprawdza, czy "rozwiazanie" spe³nia warunki zadane przez "uklady"
bool sprawdz(int u, const Uklad *uklady, const int *rozwiazanie)
{
  for(int i = 0; i < u; ++i) {
    int A = 0, B = 0;
    for(int j = 0; j < u; ++j) {
      int cyfra = rozwiazanie[j];
      int pozycja = uklady[i].pozycja[cyfra];
      if (pozycja == j) A += cyfra + 1;
      else if (pozycja >= 0) B += cyfra + 1;
    }
    if (uklady[i].A != A || uklady[i].B != B) return false;
  }
  return true;
}

// Rekurencyjnie generuje wszystkie wariacje
bool rekurencja(int u, const Uklad *uklady, int *rozwiazanie,
                int glebokosc, int *mozliwosci)
{
  if (glebokosc == u) return sprawdz(u, uklady, rozwiazanie);
  for(int i = 0; i < MAX_U - glebokosc; ++i) {
    rozwiazanie[glebokosc] = mozliwosci[i];
    mozliwosci[i] = mozliwosci[MAX_U - glebokosc - 1];
    if (rekurencja(u, uklady, rozwiazanie, glebokosc + 1, mozliwosci))
      return true;
    mozliwosci[MAX_U - glebokosc - 1] = mozliwosci[i];
    mozliwosci[i] = rozwiazanie[glebokosc];
  }
  return false;
}

// Szuka rozwi±zania
void szukaj(int u, const Uklad *uklady, int *rozwiazanie)
{
  int mozliwosci[MAX_U];
  for (int i = 0; i < MAX_U; ++i)
    mozliwosci[i] = i;
  if (!rekurencja(u, uklady, rozwiazanie, 0, mozliwosci))
    cerr << "Brak rozwi±zania!!!\n";
}

void zapisz(int u, const int *rozwiazanie)
{
  for(int i = 0; i < u; ++i)
    cout << (rozwiazanie[i] + 1) << ((i + 1 == u) ? '\n' : ' ');
}

int main()
{
  int u;
  Uklad uklady[MAX_U];
  wczytaj(u, uklady);
  int rozwiazanie[MAX_U];
  szukaj(u, uklady, rozwiazanie);
  zapisz(u, rozwiazanie);
}
