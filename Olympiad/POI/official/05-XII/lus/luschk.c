/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LUS (Lustrzana pu³apka)                        *
 *   Plik:                luschk.cpp                                     *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Weryfikator wyjscia                            *
 *                        Sprawdza czy wyjscie nie uderzy w krawedz i czy*
 *                        jest to tak samo dlugie jak wyjscie wlasciwe.  *
 *                        u¿ycie:                                        *
 *                        luschk dane.in wynik_prog.out odp_wzorc.out    *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// liczenie nwd 
int nwd(int a, int b)
{
  return a ? nwd(b % a, a) : b;
}

// Globalne - rozmiary pulapki, wyjscia uzytkownika i wyjscia poprawnego
int x, y, z, ax, ay, az, wx, wy, wz;

// Ile razy cos sie dzieli przez 2?
int ile(int a)
{
  int i = 0;
  while ((a & 1) == 0) {
    ++i;
    a >>= 1;
  }
  return i;
}

// Czy (ax,ay) w 2x na 2y walnie w krawedz?
// ileCOS = ord2(COS)
int czykrawedz(int ileax, int ileay, int ilex, int iley)
{
  return (ilex - iley == ileax - ileay) ? 1 : 0;
}

// Funkcja zwracajaca dlugosc pulapki
long long dlugosc(int ax, int ay, int az)
{
  int T, nx, ny, nz;

  if ((ax && ay && czykrawedz(ile(ax), ile(ay), ile(x), ile(y)))
      || (ax && az && czykrawedz(ile(ax), ile(az), ile(x), ile(z)))
      || (ay && az && czykrawedz(ile(ay), ile(az), ile(y), ile(z))))
    return 0LL;

  nx = (2 * x) / nwd(ax, 2 * x);
  ny = (2 * y) / nwd(ay, 2 * y);
  nz = (2 * z) / nwd(az, 2 * z);
  T = nx * (ny / nwd(nx, ny));
  T = (T / nwd(T, nz)) * nz;
  return ((long long) (ax + ay + az)) * ((long long) T);
}

int nr_testu;

void wypisz(int wyn, char *kom)
{
  if (wyn)
    printf("OK\n");
  else
    printf("WRONG\nPrzyklad %d: %s\n", nr_testu, kom);
}

int main(int argc, char *argv[])
{
  FILE *wej, *zaw, *wzo;
  int pom, i, K;
  char txt[1024];
  long long dl;

  wej = fopen(argv[1], "r");
  zaw = fopen(argv[2], "r");
  wzo = fopen(argv[3], "r");
  if (!wej || !zaw || !wzo) {
    wypisz(0, "Brak pliku.");
    return 0;
  }

  fscanf(wej, "%d", &K);
  for (nr_testu = 1; nr_testu <= K; nr_testu++) {
    fscanf(wej, "%d%d%d", &x, &y, &z);
    fscanf(wzo, "%d%d%d", &wx, &wy, &wz);
    if (fscanf(zaw, "%d%d%d", &ax, &ay, &az) < 3) {
      wypisz(0, "Nie udalo sie wczytac 3 liczb w tescie.");
      return 0;
    }
    if (ax < 0LL)
      ax = -ax;
    if (ay < 0LL)
      ay = -ay;
    if (az < 0LL)
      az = -az;
    if (ax > x || ay > y || az > z) {
      wypisz(0, "Punkt poza pulapka");
      return 0;
    }
    if (!(ax || ay || az)) {
      wypisz(0, "Strzal w (0,0,0)");
      return 0;
    }
    pom = nwd(nwd(ax, ay), az);
    ax /= pom;
    ay /= pom;
    az /= pom;
    pom = nwd(nwd(wx, wy), wz);
    wx /= pom;
    wy /= pom;
    wz /= pom;
    dl = dlugosc(ax, ay, az);
    if (dl == 0LL) {
      wypisz(0, "Strzal uderza w krawedz");
      return 0;
    }
    if (dl < dlugosc(wx, wy, wz)) {
      wypisz(0, "Rozwiazanie nieoptymalne");
      return 0;
    }
  }
  nr_testu--;
  while (fgets(txt, 1023, zaw)) {
    for (i = 0; txt[i]; i++)
      if (txt[i] != '\n' && txt[i] != '\r' && txt[i] != '\t'
          && txt[i] != ' ') {
        wypisz(0, "Smieci na koncu pliku");
        return 0;
      }
  }
  wypisz(1, "");
  return 0;
}
