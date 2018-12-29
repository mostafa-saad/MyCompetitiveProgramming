/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: AKC (Akcja Komandosów)                         *
 *   Plik:                akcs2.cpp                                      *
 *   Autor:               Marcin Stefaniak                               *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                        O z³o¿onoœci O(n^2 lg n) - wynik obliczmy      *
 *                        wyszukiwaniem binarnym dla danej liczby kol    *
 *                        stosujemy algorytm oparty na takim samym       *
 *                        pomysle jak w rozwiazaniu wzorcowym            *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<cmath>

using namespace std;

typedef long double dbl;

const int MAX_N = 2001;
const dbl MUCH = 1e12;
const dbl EPS = 1e-10;

int n;
int x[MAX_N], y[MAX_N], r[MAX_N];

void wczytajDane()
{
  scanf("%d", &n);
  int x0, y0;
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &x0, &y0, &r[i]);
    x[i] = y0;
    y[i] = -x0;                 // rotacja plaszczyzny
  }
  /* wartownik - komandos, który w ostateczno¶ci przezyje */
  x[n] = y[n] = 10000;
  r[n] = 1;
  n++;
}

struct Punkt {
  dbl x, y;
   Punkt(dbl _x, dbl _y):x(_x), y(_y) {
}};

inline dbl sqr(dbl x)
{
  return x * x;
}

inline dbl sqroot(dbl x)
{
  return x <= 0 ? 0 : sqrt(x);
}

bool wewnatrz(int i, Punkt p)
{
  return sqr(p.x - x[i]) + sqr(p.y - y[i]) <= sqr(r[i]) + EPS;
}

Punkt znajdzPrawyWspolny(int i, int j, bool * empty)
{
  dbl x1 = x[i], y1 = y[i], r1 = r[i];
  dbl x2 = x[j], y2 = y[j], r2 = r[j];
  dbl d = sqrt(sqr(x2 - x1) + sqr(y2 - y1));
  if (r1 + r2 < d) {            // okregi rozlaczne
    *empty = true;
    return Punkt(0, 0);
  }
  else if (d + r1 <= r2) {      // pierwszy zawarty w drugim
    return Punkt(x1 + r1, y1);
  }
  else if (d + r2 <= r1) {      // drugi zawarty w pierwszym
    return Punkt(x2 + r2, y2);
  }
  dbl u = (d + (sqr(r1) - sqr(r2)) / d) / 2.0;
  dbl h = sqroot(sqr(r1) - sqr(u));
  dbl dx = (x2 - x1) / d, dy = (y2 - y1) / d;
  if (dy < 0)
    h = -h;
  Punkt p = Punkt(x1 + u * dx + h * dy, y1 + u * dy - h * dx);
  Punkt p3 = Punkt(x1 + r1, y1);
  if ((p3.x > p.x) && wewnatrz(j, p3))
    p = p3;
  Punkt p4 = Punkt(x2 + r2, y2);
  if ((p4.x > p.x) && wewnatrz(i, p4))
    p = p4;
  return p;
}


/* oblicza, czy wspolne przeciecie okregow 1, ..., n jest puste */
bool czyPrzezyje(int n)
{
  if (n == 1)
    return false;
  Punkt lewy(MUCH, 0.0);

  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++) {
      bool empty = false;
      Punkt p = znajdzPrawyWspolny(i, j, &empty);
      if (empty)
        return true;
      if (p.x < lewy.x)
        lewy = p;
    }
  for (int i = 0; i < n; i++) {
    if (!wewnatrz(i, lewy))
      return true;
  }
  return false;
}

int main(void)
{
  wczytajDane();

  /* binarne wyszukiwanie odpowiedzi  */
  int d = 1, g = n, s;
  while (d < g) {
    s = (d + g) / 2;
    bool ok = czyPrzezyje(s);
    if (ok) {
      g = s;
    }
    else {
      d = s + 1;
    }
  }
  if (d == n)
    printf("NIE\n");
  else
    printf("%d\n", d);

  return 0;
}
