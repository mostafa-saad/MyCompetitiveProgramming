/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TAN (Tance w kolkach)                          *
 *   Plik:                tan.cpp                                        *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwiazanie wzorcowe.                          *
 *                                                                       *
 *************************************************************************/

#include <iostream>

using namespace std;

#define MAX_N 2005

int n, k, l;

int wynik[2][MAX_N + 1];
int iloczyny[MAX_N + 1];


// Funkcja licz±ca rozwi±zanie zadania mod modulo, je¿eli
// parametrami zadania s± n i k.
int policz(int modulo, int n, int k) {
  // Mamy zbyt wiele dzieci, by stworzyæ k kó³ek.
  if ((long long) k * l > n)
    return 0;

  int s = 0;

  // W tablicy iloczyny przechowujemy iloczyny (n-l+1)*...*(n-1).
  for (int i = l; i <= n; ++i) {
    iloczyny[i] = 1;
    for (int j = i - l + 1; j <= i - 1; ++j)
      iloczyny[i] = ((iloczyny[i]) * (j % modulo)) % modulo;
  }
  for (int i = 0; i <= n; ++i)
    wynik[s][i] = 0;
  wynik[s][0] = 1;

  // Liczenie wyniku metod± programowania dynamicznego.
  // Wiêcej szczegó³ów na jego temat mo¿na znale¼æ w opisie rozwi±zania.
  for (int i = 1; i <= k; ++i) {
    s = !s;
    for (int j = 0; j <= n; ++j)
      wynik[s][j] = 0;
    for (int q = i * l; q <= n; ++q)
      wynik[s][q] =
        ((q - 1) * wynik[s][q - 1] + iloczyny[q] * wynik[!s][q - l]) % modulo;
  }

  return wynik[s][n];
}

int liczWynikMod(int modulo) {
  // Nie da siê skonstruowaæ kó³ek o rozmiarze L.
  if (modulo < l)
    return 0;

  int liczbaKolekWielkosciModulo = n / modulo;
  int zostaloKolek = k - liczbaKolekWielkosciModulo;

  // Je¿eli mieli¶my niewystarczaj±c± liczbê kó³ek.
   if (zostaloKolek < 0)
    return 0;


   int wyn = policz(modulo, n % modulo, zostaloKolek);

   if (liczbaKolekWielkosciModulo % 2 == 1)
     wyn = wyn * (modulo - 1) % modulo;

   return wyn;
}



int main() {

  cin >> n >> k >> l;
  // Rozwa¿amy przypadki szczególne.
  if (k == 1) {
    if (n == 3)
    {
      cout << 2 << endl;
      return 0;
    }
    if (n == 4)
    {
      cout << 6 << endl;
      return 0;
    }
  }
  // Liczymy wynik modulo 5 i 401, gdy¿ 2005 = 5 * 401.
  int modulo5 = liczWynikMod(5);
  int modulo401 = liczWynikMod(401);

  // Znaj±c wynik modulo 5 i 401, liczymy wynik modulo 2005.
  int wynik = 0;
  for (int i = 0; i < 5 * 401; i++) {
    if ((i % 5 == modulo5) && (i % 401 == modulo401)) {
      wynik = i;
      break;
    }
  }

  // Wypisujemy wynik.
  cout << wynik << endl;
  return 0;
}
