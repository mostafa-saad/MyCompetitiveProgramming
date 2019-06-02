/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: AUT (Autobus)                                  *
 *   Plik:                aut0.cpp                                       *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie wzorcowe (bez uzycia STL)          *
 *                        zamiast struktur slownikowych uzyto            *
 *                        statycznego drzewa binarnego.                  *
 *                        Zlozonosc obliczeniowa O(k*log k),             *
 *                        a pamieciowa O(k).                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
const int MAXK = 100000;
const int BASE = 1024 * 128;    //liczba lisci w drzewie (musi bys >=MAXK)

int n, m, k;                    //wymiary miasta oraz liczba przystankow
int drzewo[2 * BASE];           //tablica w ktorej przechowywane jest statyczne drzewo

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
bool kryt(przystanek a, przystanek b)
{
  return (a.x != b.x ? a.x < b.x : a.y < b.y);
}

//obliczanie wartosci w danym lisciu,
//wiaze sie to z przejsciem sciezki od 
//liscia do korzenia drzewa
int val(int x)
{
  x += BASE;
  int wynik = drzewo[x];
  while (x > 1)
    wynik >?= (drzewo[x >>= 1]);
  return wynik;
}

int t[MAXK];                    //tablica pomocnicza do przenumerowania wspolrzednych
int ile;                        //liczba elementow tablicy t

//wyszukiwanie binarne
int szukaj(int l, int r, int x)
{
  if (l == r)
    return l;
  int m = (l + r) / 2;
  if (x <= t[m])
    return szukaj(l, m, x);
  return szukaj(m + 1, r, x);
}

//usuwanie powtorzen z posortowanej tablicy t majacej ile elementow
void usun_powtorzenia()
{
  int noweile = 0, last = -1;
  for (int i = 0; i < ile; ++i)
    if (t[i] != last) {
      last = t[i];
      t[noweile++] = t[i];
    }
  ile = noweile;
}

//przeskalowanie wspolrzednych przystankow
void przenumeruj_wspolrzedne(int &n, int &rzutuj(przystanek &))
{
  ile = k;
  for (int i = 0; i < k; ++i)
    t[i] = rzutuj(przys[i]);
  sort(t, t + k);
  usun_powtorzenia();
  n = ile;
  for (int i = 0; i < k; ++i)
    rzutuj(przys[i]) = szukaj(0, ile - 1, rzutuj(przys[i]));
}

//poprawianie wartosci w wezlach
void przerob(int wezel, int l, int r, int a, int b, int x)
{
  if (a <= l && r <= b) {
    drzewo[wezel] >?= x;
    return;
  }
  drzewo[wezel << 1] >?= drzewo[wezel];
  drzewo[(wezel << 1) + 1] >?= drzewo[wezel];
  int m = (l + (r - l) / 2);
  //sprawdzam czy trzeba poprawic lewe poddrzewo
  if (a <= m)
    przerob(2 * wezel, l, m, a, b, x);
  //sprawdzam czy trzeba poprawic prawe poddrzewo
  if (b > m)
    przerob(2 * wezel + 1, m + 1, r, a, b, x);
}

//uaktualniam wartosci na przedziale [a,b]
//biorac dla kazdego punktu z tego przedzialu
//maksimum z wartosci dotychczasowej oraz x
void zamien(int a, int b, int x)
{
  przerob(1, 0, BASE - 1, a, b, x);
}

int &rzutx(przystanek & a)
{
  return a.x;
}

int &rzuty(przystanek & a)
{
  return a.y;
}

void licz()
{
  sort(przys, przys + k, kryt); //sortuje przystanki
  przenumeruj_wspolrzedne(n, rzutx);
  przenumeruj_wspolrzedne(m, rzuty);
  for (int i = 0; i < k; ++i) {
    int ilu = val(przys[i].y) + przys[i].p;
    zamien(przys[i].y, m - 1, ilu);
  }
  printf("%d\n", val(m - 1));
}

int main()
{
  czytaj();
  licz();
  return 0;
}
