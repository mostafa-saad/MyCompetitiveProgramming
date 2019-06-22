/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: AUT (Autobus)                                  *
 *   Plik:                aut.cpp                                        *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie wzorcowe (z uzyciem STL)           *
 *                        Zlozonosc obliczeniowa O(k*log k),             *
 *                        a pamieciowa O(k).                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <map>
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
  return (a.x != b.x ? a.x < b.x : a.y < b.y);
}

map < int, int >mapa;           //struktura w ktorej bedziemy trzymac "wazne" punkty

void licz()
{
  sort(przys, przys + k, kryt); //sortuje przystanki
  mapa.insert(make_pair(0, 0)); //wrzucamy do struktury punkt poczatkowy
  for (int i = 0; i < k; ++i) {
    map < int, int >::iterator it = mapa.upper_bound(przys[i].y);
    int ilu;
    ilu = (--it)->second + przys[i].p;
    ++it;
    //usuwam niepotrzebne pary z naszego zbioru
    while (it != mapa.end() && it->second < ilu) {
      mapa.erase(it++);
    }
    //dodaje nowy element do zbioru
    mapa[przys[i].y] = max(mapa[przys[i].y], ilu);
  }
  printf("%d\n", (--mapa.end())->second);
}

int main()
{
  czytaj();
  licz();
  return 0;
}
