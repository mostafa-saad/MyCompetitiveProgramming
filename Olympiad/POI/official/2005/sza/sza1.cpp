/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZA (Szablon)                                  *
 *   Plik:                sza1.cpp                                       *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        rozwiazanie o zlozonosci O(n * lg n),          *
 *                        wyszukiwanie wzorca za pomoca algorytmu KMP,   *
 *                        ze zbioru wszystkich prefikso-sufiksow te,     *
 *                        ktore na pewno nie zostana szablonami          *
 *                        i do sprawdzenia pozostaje co najwyzej (lg n)  *
 *                        prefikso-sufiksow                              *
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
    if (2 * kandydaci[i] < kandydaci[i - 1])
      //jezeli krotszy kandydat na szablon nie pokrywa dluzszego
      nowe_dlugosci.push_back(kandydaci[i - 1]);
  nowe_dlugosci.push_back(kandydaci[kandydaci.size() - 1]);
  kandydaci = nowe_dlugosci;
}

//sprawdzenie czy prefikso-sufiks wejsciowego napisu o dlugosci n
//moze posluzyc jako szablon
bool dobry(int n)
{
  int i;
  int last = -1;                //last to numer pozycji ostatniego znaku,
  //w ostatnio znalezionym wystapieniu szablonu
  int j = 0;
  i = 0;
  while (i + n - 1 < dlugosc) {
    if (last + 1 < i)
      // "dziura" miedzy kolenymi wystapieniami szablonu
      return false;
    while (j < n && napis[j] == napis[i + j])
      j++;
    if (j == n)                 //znalezlismy kolejne wystapienie szablonu
      last = i + n - 1;
    i += max(1, j - p[j]);
    j = p[j];
  }
  return true;                  //caly napis zostal pokryty
}

int rozwiaz()
{
  vector < int >kandydaci;
  int i;
  licz_funkcje_prefiksowa();
  licz_prefikso_sufiksy(kandydaci);
  usun_zbedne(kandydaci);
  i = kandydaci.size();
  //sprawdzamy dlugosci kandydatow na szablony, sprawdzajac od najktotszych
  //oraz konczac na pierwszym znalezionym szablonie
  while (!dobry(kandydaci[--i])); //ta petla musi sie zatrzymac, bo caly napis jest dobrym szablonem
  return kandydaci[i];
}

int main()
{
  czytaj_dane();
  printf("%d\n", rozwiaz());
  return 0;
}
