/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: AUT (Autobus)                                  *
 *   Plik:                auts0.cpp                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                        Rozwiazanie poprawne z uzyciem STL'a, lecz     *
 *                        o zbyt duzej zlozonosci obliczeniowej (O(k*k)).*
 *                        Zlozonosc pamieciowa wynosi O(k)               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
int n, m, k;
const int MAXK = 100000;

struct przystanek {
  int x, y, p;                  //polozenie oraz liczba pasazerow
} przys[MAXK];                  //przystanki

void czytaj()
{
  scanf("%d %d %d", &n, &m, &k);
  //wczytywanie przystankow
  for (int i = 0; i < k; ++i)
    scanf("%d %d %d", &przys[i].x, &przys[i].y, &przys[i].p);
}

//funkcja porownujaca do sortowania przystankow
bool kryt(przystanek a, przystanek b)
{
  return (a.y != b.y ? a.y < b.y : a.x < b.x);
}

//w tej strukturze bedziemy trzymac pary 
//(wpolrzednax,liczba roznych <= wspolrzednychx 
//(dla pozostalych przystankow))
//analogicznie mapa[1] robi to samo dla wspolrzednych y-owych
map < int, int >mapa[2];

set < int >s;


//przeskalowanie wspolrzednych przystankow
void przenumeruj_wspolrzedne(int nr, int &n, int &rzutuj(przystanek &))
{
  s.clear();
  for (int i = 0; i < k; ++i)
    s.insert(rzutuj(przys[i]));

  n = 0;
  mapa[nr][0] = 0;
  for (set < int >::iterator it = s.begin(); it != s.end(); ++it)
    mapa[nr].insert(make_pair(*it, ++n));

  for (int i = 0; i < k; ++i)
    rzutuj(przys[i]) = mapa[nr][rzutuj(przys[i])];
}

int &rzutx(przystanek & a)
{
  return a.x;
}

int &rzuty(przystanek & a)
{
  return a.y;
}

void licz()
{
  sort(przys, przys + k, kryt); //sortuje przystanki
  przenumeruj_wspolrzedne(0, n, rzutx); //wspolrzedne x-owe
  przenumeruj_wspolrzedne(1, m, rzuty); //wspolrzedne y-owe
  int t[MAXK + 1], nowy[MAXK + 1], pos = 0;
  for (int i = 0; i <= n; ++i)
    t[i] = 0;

  for (int j = 1; j <= m; ++j) {
    for (int i = 0; i <= n; ++i) {
      nowy[i] = t[i];
      if (i)
        nowy[i] >?= nowy[i - 1];
      if (pos < k && i == przys[pos].x && j == przys[pos].y)
        nowy[i] += przys[pos++].p;
    }
    for (int i = 0; i <= n; ++i)
      t[i] = nowy[i];
  }
  printf("%d\n", t[n]);
}

int main()
{
  czytaj();
  licz();
  return 0;
}
