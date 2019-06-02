/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: AKC (Akcja Komandosów)                         *
 *   Plik:                akcs0.cpp                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                        Z³o¿ono¶æ obliczeniowa wynosi O(n^3),          *
 *                        natomiast pamiêciowa O(n). U¿yto arytmetyki    *
 *                        zmiennopozycyjnej typu double.                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

typedef double typ;             //typ danych zmiennoprzecinowych

const int MAXN = 2000;          //maksymalna liczba kol
const typ epsilon = 1E-5;

struct punkt {
  typ x, y;
};

struct kolo {
  int x, y, r;                  //polozenie i promien
} kola[MAXN];

int n;                          //liczba kol

typ sqr(typ x)
{
  return x * x;
}

long long llsqr(int x)
{
  return (long long int) x *(long long int) x;
}


//wartosc bezwzgledna
int abs(int x)
{
  return x >= 0 ? x : -x;
}

//wczytywanie polozenia i promieni kolejnych kol
void czytaj()
{
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d %d %d", &kola[i].x, &kola[i].y, &kola[i].r);
}

punkt punkty[MAXN * MAXN / 4];
int l_punktow;                  //liczba_punktow w tablicy punkty

/*
   procedura to oblicza punkty przeciecia dwoch okregow,
   zakladajac ze okregi te sie przecinaja
*/
void oblicz_przeciecie(int a1, int b1, int r1, int a2, int b2, int r2)
{
  if (b1 == b2) {
    typ x = (sqr(r1) - sqr(r2) + sqr(a2) - sqr(a1)) / (2.0 * (a2 - a1));
    typ z;
    z = sqrt(sqr(r1) - sqr(x - a1));
    punkty[l_punktow].x = x;
    punkty[l_punktow++].y = b1 + z;
    punkty[l_punktow].x = x;
    punkty[l_punktow++].y = b1 - z;
    return;
  }
  //sprowadzenie ukladu równañ do równania kwadratowego
  typ z =
      (sqr(r1) - sqr(r2) + sqr(b2) - sqr(b1) + sqr(a2) -
       sqr(a1)) / (2.0 * (b2 - b1));
  typ q = (a1 - a2) / (typ) (b2 - b1);
  typ beta = -2.0 * a1 + 2.0 * (z - b1) * q;
  typ alfa = 1 + sqr(q);
  typ gamma = sqr(a1) + sqr(z - b1) - sqr(r1);
  typ delta = sqr(beta) - 4.0 * alfa * gamma;

  //rozwi±zywanie równania kwadratowego
  typ x1 = (-beta + sqrt(delta)) / (2.0 * alfa);
  typ x2 = (-beta - sqrt(delta)) / (2.0 * alfa);
  typ y1 = z + q * x1;
  typ y2 = z + q * x2;
  //wybieram skrajnie prawy punkt przeciecia 2 kol
  punkt nowy;
  nowy.x = x1;
  nowy.y = y1;
  punkty[l_punktow++] = nowy;
  nowy.x = x2;
  nowy.y = y2;
  punkty[l_punktow++] = nowy;
}


/*funkcja ta sprawdza czy kola o numerach i oraz j sie przecinaja,
  a jesli tak, to dopisuje punkty przeciecia do tablicy punkty
*/
void przeciecie(int i, int j)
{
  int a1, b1, r1;
  int a2, b2, r2;
  a1 = kola[i].x;
  b1 = kola[i].y;
  r1 = kola[i].r;
  a2 = kola[j].x;
  b2 = kola[j].y;
  r2 = kola[j].r;
  //kwadrat odleglosci miedzy srodkami okregow
  long long dist = llsqr(a1 - a2) + llsqr(b1 - b2);
  if (dist <= llsqr(r1 + r2) && dist > llsqr(r1 - r2))
    oblicz_przeciecie(a1, b1, r1, a2, b2, r2);
}


void dodaj_przeciecia(int i)
{
  //dodaje srodek i-tego kola
  punkty[l_punktow].x = kola[i].x;
  punkty[l_punktow++].y = kola[i].y;
  //przeciecia z wczesniejszymi kolami
  for (int j = 0; j < i; ++j)
    przeciecie(j, i);
}

//funkcja ta sprawdza, czy punkt p nalezy do n-tego kola
bool nalezy(punkt p, int n)
{
  return (sqr(p.x - kola[n].x) + sqr(p.y - kola[n].y) <=
          sqr(kola[n].r) + epsilon);
}

//funkcja ta sprawdza, czy punkt p nalezy do pierwszych n kó³
bool nieNalezy(punkt p, int n)
{
  for (int i = 0; i < n; ++i)
    if (!nalezy(p, i))
      return true;
  return false;
}

//glowna procedura programu
void rozwiaz()
{
  l_punktow = 1;
  punkty[0].x = kola[0].x;
  punkty[0].y = kola[0].y;
  int i = 1;
  while (l_punktow && i < n) {
    int k = 0;                  //nowa liczba punktow
    for (int j = 0; j < l_punktow; ++j)
      if (nalezy(punkty[j], i))
        punkty[k++] = punkty[j];
    l_punktow = k;
    dodaj_przeciecia(i);
    for (int j = k; j < l_punktow; ++j)
      if (!nieNalezy(punkty[j], i))
        punkty[k++] = punkty[j];
    l_punktow = k;
    i++;
  }
  if (l_punktow)
    printf("NIE\n");
  else
    printf("%d\n", i);
}

int main()
{
  czytaj();
  rozwiaz();
  return 0;
}
