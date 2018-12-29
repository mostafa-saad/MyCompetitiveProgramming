/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZA (Szablon)                                  *
 *   Plik:                szas1.cpp                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                        rozwiazanie o zlozonosci O(n^3), spowodowane   *
 *                        wyszukiwaniem wzorca za pomoca algorytmu       *
 *                        naiwnego                                       *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <string>
using namespace std;

const int MAX_LEN = 500000;     // maksymalna dlugosc napisu
string napis;                   //wczytywany napis 
int dlugosc;                    // dlugosc napisu

//wczytywanie danych
void czytaj_dane()
{
  char s[MAX_LEN + 3];
  fgets(s, MAX_LEN + 2, stdin); //wczytanie napisu ze standardowego wejscia
  napis = s;
  dlugosc = napis.size() - 1;   // nie liczymy znaku konca stringa
//      cout << dlugosc << " dlugosc\n";
}

//sprawdzenie czy prefiks wejsciowego napisu o dlugosci n
//moze posluzyc jako szablon
bool dobry(int n)
{
  int i, j;
  int last = dlugosc;           //last to numer pozycji pierwszego znaku, w ostatnio znalezionym wystapieniu szablonu
  for (i = dlugosc - n; i >= 0; --i) {
    if (i + n < last)
      return false;             // "dziura" miedzy kolenymi wystapieniami szablonu
    j = 0;
    while (j < n && napis[j] == napis[i + j])
      j++;
    if (j == n)
      last = i;                 // znaleziono nowy szablon, aktualizacja zmiennej "last"
  }
  return (last == 0);
}

int rozwiaz()
{
  int i;
  i = 1;
  while (i <= dlugosc && !dobry(i))
    ++i;
  return i;
}

int main()
{
  czytaj_dane();
  printf("%d\n", rozwiaz());
  return 0;
}
