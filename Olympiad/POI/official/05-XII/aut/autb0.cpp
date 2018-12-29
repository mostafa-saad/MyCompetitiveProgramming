/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: AUT (Autobus)                                  *
 *   Plik:                autb0.cpp                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie niepoprawne (zachlanne)            *
 *                        Program wybiera przystanki o najwiekszej       *
 *                        liczbie pasazerow, sprawdzajac czy moze do     *
 *                        nich dojechac z aktualnej pozycji.             *
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
//wzgledem liczby oczekujacych pasazerow
bool kryt(przystanek a, przystanek b)
{
  return a.p != b.p ? a.p > b.p : (a.x != b.x ? a.x < b.x : a.y < b.y);
}

void licz()
{
  int x, y, ilu;
  x = y = 1;                    //poczatkowa pozycja
  ilu = 0;                      //poczatkowa liczba pasazerow
  sort(przys, przys + k, kryt); //sortuje przystanki
  for (int i = 0; i < k; ++i)
    if (x <= przys[i].x && y <= przys[i].y) {
      x = przys[i].x;
      y = przys[i].y;
      ilu += przys[i].p;
    }
  printf("%d\n", ilu);
}

int main()
{
  czytaj();
  licz();
  return 0;
}
