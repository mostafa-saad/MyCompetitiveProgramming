/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LUS (Lustrzana pu³apka)                        *
 *   Plik:                lusb1.cpp                                      *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie niepoprawne                        *
 *                        Rozwiazanie wg programu dr Marcina Kubicy      *
 *                        w Ocamlu. Symuluje lot dla kazdego strzalu,    *
 *                        wybiera najlepszy. Bledny, gdyz zaklada, ze    *
 *                        uderzyc w krawedz mozemy tylko w calkowitych   *
 *                        wielokrotnosciach poczatkowego wektora.        *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

// Wielkosc pulapki
int x, y, z;
// Rozwiazanie
int ax, ay, az;
// Najlepsza dotychczas znaleziona dlugosc
long long naj;

// NWD
int nwd(int a, int b)
{
  return a ? nwd(b % a, a) : b;
}

// Liczy dlugosc, jaka przeleci strzal w (sx,sy,sz)
// Zwraca 0, jesli trafi w krawedz.
// Symulujemy od (x,y,z) modulo 2x,2y,2z
long long dlugosc(int sx, int sy, int sz)
{
  // Juz przelecielismy
  long long dlug = 0LL;
  long long krok = (long long) (sx + sy + sz);
  // Aktualne polozenie wiazki.
  int xx, yy, zz;
  xx = (x + sx) % (2 * x);
  yy = (y + sy) % (2 * y);
  zz = (z + sz) % (2 * z);
  dlug += krok;
  // i symulujemy.
  while ((xx != x) || (yy != y) || (zz != z)) {
    // Czy krawedz?
    if ((xx == 0 && yy == 0) || (xx == 0 && zz == 0)
        || (yy == 0 && zz == 0))
      return 0LL;
    xx = (xx + sx) % (2 * x);
    yy = (yy + sy) % (2 * y);
    zz = (zz + sz) % (2 * z);
    dlug += krok;
  }
  return dlug;
}

// Funkcja rozwiazujaca problem.
// Puszcza symulacje dla kazdego strzalu.
void rozwiaz(void)
{
  int i, j, k;
  long long dlug;
  naj = 0LL;
  for (i = 0; i <= x; i++)
    for (j = 0; j <= y; j++)
      for (k = 0; k <= z; k++)
        if ((i || j || k) && (nwd(nwd(i, j), k) == 1)) {
          dlug = dlugosc(i, j, k);
          if (dlug > naj) {
            naj = dlug;
            ax = i;
            ay = j;
            az = k;
          }
        }
}

int main(void)
{
  int K;
  scanf("%d", &K);
  while (K--) {
    scanf("%d%d%d", &x, &y, &z);
    rozwiaz();
    printf("%d %d %d\n", ax, ay, az);
  }
  return 0;
}
