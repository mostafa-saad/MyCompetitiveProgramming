/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LUS (Lustrzana pu³apka)                        *
 *   Plik:                lus.cpp                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        Sprawdza w czasie logarytmiczym, czy strzal    *
 *                        jest ok. Przeglada od rogu, jak trafi optymalny*
 *                        T, to konczy. O( DUZA_STALA log(xyz))          *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

int nwd(int a, int b)
{
  return a ? nwd(b % a, a) : b;
}

// Globalne - rozmary pulapki
int x, y, z;
// I wynik aktualny
int wx, wy, wz;
long long dlug;
// Aktualnie przegladane wartosci
int ax, ay, az;

// Ile razy cos sie dzieli przez 2?
int liczrazy(int a)
{
  int i;
  for (i = 0; (a & 1) == 0; i++)
    a >>= 1;
  return i;
}

int ile[1001];
#define ilerazy(a) (ile[a])

// Czy (ax,ay) w 2x na 2y walnie w krawedz?
int czykrawedz(int ileax, int ileay, int ilex, int iley)
{
  return (ilex - iley == ileax - ileay) ? 1 : 0;
}

// Funkcja zwracajaca dlugosc pulapki
// W czymaks umieszcza, czy bylo maksymalne mozliwe T.
int maksymalneT;
int czymaks;
long long dlugosc(void)
{
  int nx, ny, nz, T;

  if ((ax && ay
       && czykrawedz(ilerazy(ax), ilerazy(ay), ilerazy(x), ilerazy(y)))
      || (ax && az
          && czykrawedz(ilerazy(ax), ilerazy(az), ilerazy(x), ilerazy(z)))
      || (ay && az
          && czykrawedz(ilerazy(ay), ilerazy(az), ilerazy(y), ilerazy(z))))
    return 0LL;

  nx = (2 * x) / nwd(ax, 2 * x);
  ny = (2 * y) / nwd(ay, 2 * y);
  nz = (2 * z) / nwd(az, 2 * z);
  T = nx * (ny / nwd(nx, ny));
  T = (T / nwd(T, nz)) * nz;
  czymaks = ((T >= maksymalneT) ? 1 : 0);
  return ((long long) (ax + ay + az)) * ((long long) T);
}

// Funkcja rozwiazujaca.
void rozwiaz(void)
{
  // Aktualnie sprawdzane wartosci
  long long ad;
  int suma;
  dlug = 0LL;
  czymaks = 0;
  maksymalneT = x * (y / nwd(x, y));
  maksymalneT = 2 * maksymalneT * (z / nwd(maksymalneT, z));
  for (suma = x + y + z - 1; suma > 0; --suma)
    for (ax = ((suma > x) ? x : suma); ax >= 0; --ax)
      for (ay = ((suma - ax > y) ? y : (suma - ax)); ay >= 0; --ay) {
        az = suma - ax - ay;
        if (az > z)
          break;
        if (az < 0)
          continue;
        if ((nwd(nwd(ax, ay), az) == 1)) {
          if (dlug < (ad = dlugosc())) {
            wx = ax;
            wy = ay;
            wz = az;
            dlug = ad;
          }
          if (czymaks)
            return;
        }
      }
}

// Main - wczytuje wszystkie testy i wywoluje funkcje rozwiazujaca
int main(void)
{
  int d, i;
  scanf("%d", &d);
  //liczymy tablice ile
  for (i = 1; i < 1001; i++)
    ile[i] = liczrazy(i);
  while (d--) {
    scanf("%d%d%d", &x, &y, &z);
    rozwiaz();
    printf("%d %d %d\n", wx, wy, wz);
  }
  return 0;
}
