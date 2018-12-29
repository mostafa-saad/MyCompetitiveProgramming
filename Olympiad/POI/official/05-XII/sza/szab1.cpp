/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZA (Szablon)                                  *
 *   Plik:                szab1.cpp                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie niepoprawne                        *
 *                        rozwiazanie o zlozonosci O(n * lg n)           *
 *                        bledne zalozenie:                              *
 *                        dlugosc szablonu mozna wyszukiwac binarnie     *
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

//obliczanie dlugosci wszystkich prefiksow napisu,
//ktore sa jednoczesnie jego sufiksami
void licz_prefikso_sufiksy(vector < int >&kandydaci)
{
  int i = dlugosc;
  kandydaci.clear();
  while (i > 0) {
    kandydaci.push_back(i);
    i = p[i];
  }
}

//usuwanie tych dlugosci, ktore na pewno nie
//posluza jako najkrotszy szablon
void usun_zbedne(vector < int >&kandydaci)
{
  vector < int >nowe_dlugosci;
  int i;

  for (i = 1; i < (int) kandydaci.size(); ++i)
    if (2 * kandydaci[i] < kandydaci[i - 1])  //jezeli krotszy kandydat na szablon nie pokrywa dluzszego
      nowe_dlugosci.push_back(kandydaci[i - 1]);
  nowe_dlugosci.push_back(kandydaci[kandydaci.size() - 1]);
  kandydaci = nowe_dlugosci;
}

//sprawdzenie czy prefiks wejsciowego napisu o dlugosci n
//moze posluzyc jako szablon
bool dobry(int n)
{
  int i;
  int last = -1;                //last to numer pozycji ostatniego znaku, w ostatnio znalezionym wystapieniu szablonu
  int j = 0;
  i = 0;
  while (i + n - 1 < dlugosc) {
    if (last + 1 < i)
      return false;             // "dziura" miedzy kolenymi wystapieniami szablonu
    while (j < n && napis[j] == napis[i + j])
      j++;
    if (j == n)                 //znalezlismy kolejne wystapienie szablonu
      last = i + n - 1;
    i += max(1, j - p[j]);
    j = p[j];
  }
  return last == dlugosc - 1;   //sprawdzenie, prefiks o dlugosci n jest tez sufiksem napisu
}

//binarne wyszukiwanie dlugosci szablonu
int szukaj(int l, int r)
{
  int m = (l + r) / 2;
  if (l == r)
    return l;
  if (l + 1 == r)
    return (dobry(l) ? l : r);
  if (dobry(m))
    return szukaj(l, m);
  else
    return szukaj(m + 1, r);
}

int rozwiaz()
{
  vector < int >kandydaci;
  licz_funkcje_prefiksowa();
  return szukaj(1, dlugosc);
}

int main()
{
  czytaj_dane();
  printf("%d\n", rozwiaz());
  return 0;
}
