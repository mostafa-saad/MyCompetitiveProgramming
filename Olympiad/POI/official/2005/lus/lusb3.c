/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LUS (Lustrzana pu³apka)                        *
 *   Plik:                lusb3.cpp                                      *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie niepoprawne                        *
 *                        Heurystyczna modyfikacja rozwiazania wg        *
 *                        programu dr Marcina Kubicy w Ocamlu. Symuluje  *
 *                        lot dla kazdego strzalu, wybiera najlepszy.    *
 *                        Poprawnie sprawdza, czy uderzylismy w krawedz, *
 *                        sprawdzajac w kazdej plaszczyznie czy to       *
 *                        zrobilismy. Natomiast szuka tylko w odleglosci *
 *                        ILE=6 w metryce miejskiej od wierzcholka.      *
 *                        x,x-1,x-2.                                     *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

#define ILE 6

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

// Sprawdza, czy uderzymy w krawedz strzalem plaskim
// (a,b) w klatce (A,B)
int czyplaskakrawedz(int a, int b, int A, int B)
{
  // aktualne polozenie
  int aa, bb;
  // Skrocenie a i b
  int pom;
  pom = nwd(a, b);
  a /= pom;
  b /= pom;
  aa = (A + a) % (2 * A);
  bb = (B + b) % (2 * B);
  while (aa != A || bb != B) {
    if (aa == 0 && bb == 0)
      return 1;
    aa += a;
    bb += b;
    aa %= 2 * A;
    bb %= 2 * B;
  }
  return 0;
}

// Sprawdza czy strzal uderzy w krawedz
int czykrawedz(int sx, int sy, int sz)
{
  if (sx && sy && czyplaskakrawedz(sx, sy, x, y))
    return 1;
  if (sx && sz && czyplaskakrawedz(sx, sz, x, z))
    return 1;
  if (sz && sy && czyplaskakrawedz(sz, sy, z, y))
    return 1;
  return 0;
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
  // Czy krawedz?
  if (czykrawedz(sx, sy, sz))
    return 0LL;
  xx = (x + sx) % (2 * x);
  yy = (y + sy) % (2 * y);
  zz = (z + sz) % (2 * z);
  dlug += krok;
  // i symulujemy.
  while ((xx != x) || (yy != y) || (zz != z)) {
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
  int i, j, k, suma;
  long long dlug;
  naj = 0LL;
  for (suma = x + y + z - 1; suma > x + y + z - 1 - ILE && suma > 0;
       --suma)
    for (i = ((suma > x) ? x : suma); i >= 0; --i)
      for (j = ((suma - i > y) ? y : (suma - i)); j >= 0; --j) {
        k = suma - i - j;
        if (k < 0 || k > z)
          continue;
        if (nwd(nwd(i, j), k) == 1) {
          dlug = dlugosc(i, j, k);
          if (dlug > naj) {
            naj = dlug;
            ax = i;
            ay = j;
            az = k;
          }
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
