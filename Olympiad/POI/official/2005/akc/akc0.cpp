/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: AKC (Akcja Komandosów)                         *
 *   Plik:                akc0.cpp                                       *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        Z³o¿ono¶æ obliczeniowa wynosi O(n*n),          *
 *                        natomiast pamiêciowa O(n). U¿yto arytmetyki    *
 *                        zmiennopozycyjnej typu double.                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

typedef long double typ;        //typ danych zmiennoprzecinowych

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

//aktualizuje skrajnie lewy punkt
void poprawPunkt(typ x, typ y, punkt & lewy)
{
  if (x < lewy.x) {
    lewy.x = x;
    lewy.y = y;
  }
}

/*
   procedura to oblicza punkty przeciecia dwoch okregow,
   zakladajac ze okregi te sie przecinaja
*/
void dodajPrzeciecie(int a1, int b1, int r1, int a2, int b2, int r2,
                     punkt & lewy)
{
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
  if (x1 > x2)
    poprawPunkt(x1, y1, lewy);
  else
    poprawPunkt(x2, y2, lewy);
}

//wartosc bezwzgledna
int abs(int x)
{
  return x >= 0 ? x : -x;
}

/*funkcja ta sprawdza czy kola o numerach i oraz j sie przecinaja,
  a jesli tak, to aktualizuje "lewy" punkt
*/
bool przeciecie(int i, int j, punkt & lewy)
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
  //kola sa rozlaczne
  if (dist > llsqr(r1 + r2))
    return false;
  //sprawdzam skrajne prawe punkty kol
  if (llsqr(a1 + r1 - a2) + llsqr(b1 - b2) <= llsqr(r2))
    poprawPunkt(a1 + r1, b1, lewy);
  else if (llsqr(a2 + r2 - a1) + llsqr(b2 - b1) <= llsqr(r1))
    poprawPunkt(a2 + r2, b2, lewy);
  else
    dodajPrzeciecie(a1, b1, r1, a2, b2, r2, lewy);
  return true;
}

//wczytywanie polozenia i promieni kolejnych kol
void czytaj()
{
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d %d %d", &kola[i].x, &kola[i].y, &kola[i].r);
}

//funkcja ta sprawdza, czy punkt p nalezy do pierwszych n kó³
bool nieNalezy(punkt p, int n)
{
  for (int i = 0; i < n; ++i)
    if (sqr(p.x - kola[i].x) + sqr(p.y - kola[i].y) >
        sqr(kola[i].r) + epsilon)
      return true;
  return false;
}

//glowna procedura programu
void rozwiaz()
{
  bool puste = false;           //zmienna zawiera informacje, czy aktualne przeciecie wszystkich kol jest puste
  int i = 1;
  punkt lewy;                   //najbardziej "lewy" punkt, ze wszystkich kandydatow
  lewy.x = kola[0].x + kola[0].r;
  lewy.y = kola[0].y;
  while (!puste && i < n) {
    for (int j = 0; j < i; ++j)
      if (!przeciecie(j, i, lewy))
        puste = true;           //kola sie nie przecinaja
    //wybrany punkt nie nalezy do wszystkich okregow
    if (nieNalezy(lewy, i++))
      puste = true;
  }
  if (!puste)
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
