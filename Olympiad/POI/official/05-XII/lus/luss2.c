/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LUS (Lustrzana pu³apka)                        *
 *   Plik:                lus2s.cpp                                      *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                        Rozwiazanie polowicznie dobre. Sprawdza        *
 *                        w czasie logarytmiczym, czy strzal jest ok.    *
 *                        Natomiast przeglada wszystko jak leci, bez     *
 *                        odcinania. O(xyz log(xyz))                     *
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
int ilerazy(int a)
{
  int i;
  for (i = 0; (a & 1) == 0; i++)
    a >>= 1;
  return i;
}

// Czy (ax,ay) w 2x na 2y walnie w krawedz?
int czykrawedz(int ileax, int ileay, int ilex, int iley)
{
  return (ilex - iley == ileax - ileay) ? 1 : 0;
}

// Funkcja zwracajaca dlugosc pulapki
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
  return ((long long) (ax + ay + az)) * ((long long) T);
}

// Funkcja rozwiazujaca - brutalnie
// Przelatuje mozliwe rozwiazania i wywoluje dlugosc dla kazdego
void rozwiaz(void)
{
  // Aktualnie sprawdzane wartosci
  long long ad;
  dlug = 0LL;
  for (ax = 0; ax <= x; ax++)
    for (ay = 0; ay <= y; ay++)
      for (az = 0; az <= z; az++)
        if ((nwd(nwd(ax, ay), az) == 1))
          if (dlug < (ad = dlugosc())) {
            wx = ax;
            wy = ay;
            wz = az;
            dlug = ad;
          }
}

// Main - wczytuje wszystkie testy i wywoluje funkcje rozwiazujaca
int main(void)
{
  int d;
  scanf("%d", &d);

  while (d--) {
    scanf("%d%d%d", &x, &y, &z);
    rozwiaz();
    printf("%d %d %d\n", wx, wy, wz);
  }
  return 0;
}
