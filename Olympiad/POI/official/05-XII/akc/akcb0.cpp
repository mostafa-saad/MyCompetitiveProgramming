/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: AKC (Akcja Komandosów)                         *
 *   Plik:                akcb0.cpp                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie niepoprawne                        *
 *                        Polega ono na sprawdzaniu, czy kazda para kó³  *
 *                        sie przecina, co w oczywisty sposób jest b³êdne*
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

const int MAXN = 2000;          //maksymalna liczba kol
const double epsilon = 1E-5;

struct punkt {
  double x, y;
};

struct kolo {
  int x, y, r;                  //polozenie i promien
} kola[MAXN];

int n;                          //liczba kol

//wczytywanie polozenia i promieni kolejnych kol
void czytaj()
{
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d %d %d", &kola[i].x, &kola[i].y, &kola[i].r);
}

int sqr(int x)
{
  return x * x;
}

//funkcja ta sprawdza, czy kola o numerach i oraz j sie przecinaja
bool puste_przeciecie(int i, int j)
{
  return sqr(kola[i].x - kola[j].x) + sqr(kola[i].y - kola[j].y) >
      sqr(kola[i].r + kola[j].r);
}

//glowna procedura programu
void rozwiaz()
{
  bool koniec = false;
  int i = 1;
  while (!koniec && i < n) {
    for (int j = 0; j < i; ++j)
      if (puste_przeciecie(j, i))
        koniec = true;
    ++i;
  }
  if (!koniec)
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
