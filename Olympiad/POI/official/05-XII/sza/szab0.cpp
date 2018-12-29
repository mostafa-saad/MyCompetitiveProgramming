/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZA (Szablon)                                  *
 *   Plik:                szan0.cpp                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie niepoprawne                        *
 *                        program szuka najkrotszej dlugosci slowa,      *
 *                        takiego ze napis jest potega tego slowa,       *
 *                        zlozonosc O(n)                                 *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

const int MAX_LEN = 500000;     // maksymalna dlugosc napisu

string napis;                   //wczytywany napis 
int dlugosc;                    // dlugosc napisu
int p[MAX_LEN + 2];             //tablica, z wartosciami funkcji prefiksowej

//wczytywanie danych
void czytaj_dane()
{
  char s[MAX_LEN + 3];
  fgets(s, MAX_LEN + 2, stdin); //wczytanie napisu ze standardowego wejscia
  napis = s;
  dlugosc = napis.size() - 1;   // nie liczymy znaku konca stringa
  napis.resize(dlugosc);
}

//obliczanie funkcji prefiksowej dla napisu
void licz_funkcje_prefiksowa()
{
  int i, t;
  p[0] = p[1] = 0;
  t = 0;
  for (i = 2; i <= dlugosc; ++i) {
    while (t > 0 && napis[t] != napis[i - 1])
      t = p[t];
    if (napis[t] == napis[i - 1])
      t++;
    p[i] = t;
  }
}

//szukanie najktotszej dlugosci slowa, takiego ze
//napis jest potega tego slowa, wyszukuje wystapienie napisu
//w slowie bedacym konkatenacja napisu i napisu (napis^napis)
int znajdz_dlugosc()
{
  int j = 0;
  bool found = false;           // czy znalezlismy wystapienie napisu
  int i = 1;
  napis += napis;
  while (!found)                // zawsze sie zatrzyma, gdyz oryginalny napis
    // zawsze wystepuje w podwdojonym napisie na koncu
  {
    while (j < dlugosc && napis[j] == napis[i + j])
      j++;
    if (j == dlugosc && dlugosc % i == 0)
      found = true;             //znalezlismy kolejne wystapienie szablonu
    else {
      i += max(1, j - p[j]);
      j = p[j];
    }
  }
  return i;;                    //caly napis zostal pokryty
}

int rozwiaz()
{
  licz_funkcje_prefiksowa();
  return znajdz_dlugosc();
}

int main()
{
  czytaj_dane();
  printf("%d\n", rozwiaz());
  return 0;
}
