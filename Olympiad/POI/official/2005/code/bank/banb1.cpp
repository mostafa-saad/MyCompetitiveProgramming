/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: BAN (Bankomat)                                 *
 *   Plik:                banb1.cpp                                      *
 *   Autor:               Rafa³ Rusin (r.rusin@students.mimuw.edu.pl)    *
 *   Opis:                Rozwi±zanie niepoprawne zadania Bankomat       *
 *                                                                       *
 *************************************************************************/
#include <algorithm>
#include <iostream>
using namespace std;
#define FOR(i,n) for(int (i)=0;(i)<(n);(i)++)

const int MAXN = 1000,                //Maksymalna ilo¶æ scen
          MAXS = 10000;               //Maksymalna sekwencja ruchów

struct Slowo {
  int *cyfry;
  int dlugosc;

  bool operator <(const Slowo & b) const {
    return dlugosc < b.dlugosc;
}};

Slowo slowa[MAXN];

//sprawdzenie pinu od koñca
bool sprawdzPin(int pin, Slowo * s)
{
  //znajdowanie pinu w slowie
  int pinPoz = 0, sPoz = 0;
  int cyfra = pin % 10;
  while (pinPoz < 4 && sPoz < s->dlugosc && sPoz < 50) {
    if (cyfra == s->cyfry[sPoz]) {
      pin = pin / 10;
      cyfra = pin % 10;
      pinPoz++;
    }
    else
      sPoz++;
  }

  return pinPoz == 4;
}

int main()
{
  int n;
  cin >> n;
  FOR(i, n) {
    int dl;
    cin >> dl;
    slowa[i].cyfry = new int[dl];
    slowa[i].dlugosc = dl;
    cin.get();
    FOR(j, dl) slowa[i].cyfry[j] = cin.get() - '0';
  }

  sort(slowa, slowa + n);

  int wynik = 0;
  FOR(pin, 10000) {
    int czyOk = 1;
    FOR(k, n) {
      if (sprawdzPin(pin, slowa + k) == 0) {
        czyOk = 0;
        break;
      }
    }
    wynik += czyOk;
  }
  cout << wynik << "\n";
}
