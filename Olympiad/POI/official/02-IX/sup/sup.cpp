/*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Superskoczek                                   *
 *   Plik:                sup.pas                                        *
 *   Autor:               Krzysztof Onak                                 *
 *************************************************************************/
#include <fstream>
using namespace std;

int ABS(int a)
/* Modul liczby calkowitej */
{
  return a < 0 ? -a : a;
}

void NWD(int a, int b, int &x, int &y)
/* Zwraca x i y takie, ze NWD(a,b) = ax + by. *
 * Dziala dla nieujemnych a i b.              *
 * Przyjmujemy, ze NWD(0,0) = 0.              */
{
  if (b == 0) {
    x = 1;
    y = 0;
  } else {
    int x2, y2;
    NWD(b, a % b, x2, y2);
    x = y2;
    y = x2 - a / b * y2;
  }
}

int NWD(int a, int b)
/* Zwraca NWD(a,b). Przyjmujemy, ze NWD(0,0) = 0. */
{
  a = ABS(a);  // bierzemy wartosci dodatnie
  b = ABS(b);
  int x, y;
  NWD(a, b, x, y);  // korzystamy z wczesniejszej funkcji
  return a * x + b * y;
}

int NWW(int a, int b)
/* Zwraca NWW(a,b). Zakladamy, ze a lub b jest rozne od zera. */
{
  return ABS(a) / NWD(a, b) * ABS(b);
}

/* Wektor wraz z najprostszymi przydatnymi w zadaniu operacjami. */
struct Wektor {
  // wspolrzedne
  int x, y;
  
  // konstruktory
  Wektor(int X, int Y) : x(X), y(Y) {}
  Wektor() : x(0), y(0) {}
  
  // mnozenie przez skalar i dodawanie wektorow
  Wektor operator*(int z) const {return Wektor(z * x, z * y);}
  Wektor operator+(const Wektor &w) const {return Wektor(x + w.x, y + w.y);}
  
  // symetria wzgledem osi OX oraz obrot o 90 stopni
  Wektor symetriaOX() const {return Wektor(x, -y);}
  Wektor obrot90() const {return Wektor(-y, x);}
};

istream& operator>>(istream &s, Wektor &w)
/* wczytywanie wektora, format: para liczb calkowitych */
{
  s >> w.x >> w.y;
  return s;
}

/* Siatka rozpinana przez zbior wektorow. */
class Siatka {
  // wektory bazowe
  Wektor alfa, beta;
public:
  // dodanie nowego wektora i ewentualna zmiana bazy
  void DodajWektor(Wektor gamma)
  {
    if (gamma.y < 0) gamma = gamma * -1;
    if (gamma.y == 0) {
      alfa.x = NWD(alfa.x, gamma.x);
    } else {
      if (beta.y != 0) {
        int nww = NWW(beta.y, gamma.y);
	alfa.x = NWD(alfa.x,
	             (nww / beta.y) * beta.x - (nww / gamma.y) * gamma.x);
      }
      int a, b;
      NWD(gamma.y, beta.y, a, b);
      beta = gamma * a + beta * b;
    }
    if (alfa.x != 0) {
      if (beta.x < 0) beta.x += (-beta.x / alfa.x + 1) * alfa.x;
      beta.x -= beta.x / alfa.x * alfa.x;
    }
  }
  // czy siatka pozwala na dotacie do wszystkich punktow kratowych
  bool Zupelna()
  {
    return alfa.x == 1 && beta.y == 1;
  }
};

/* Wybiera najbardziej skierowany na prawo wektor *
 * z polplaszczyzny y >= 0.                       */
class NajbardziejWPrawo {
  // aktualny zwyciezca
  Wektor w;
public:
  // konstruktor
  NajbardziejWPrawo() : w(-1, 0) {}
  // dostawienie nowego wektora
  void NowyWektor(Wektor nowy) {
    if (nowy.y == 0) {
      if (nowy.x > 0) w = nowy;
    } else {
      if (-nowy.y * w.x + nowy.x * w.y > 0) w = nowy;
    }
  }
  // podaje najbardziej w prawo zwrocony wektor
  Wektor Podaj() {return w;}
};

/* Sprawdza, czy mo¿na doj¶æ za pomoca dostarczonych wektorów *
 * na dodatnia czesc osi OX.                                  */
class DojscieNaPolos {
  // najbardziej wychylone w prawo wektory dla obu polplaszczyzn
  NajbardziejWPrawo dodatnie, ujemne;
public:
  // dodanie nowego wektora
  void NowyWektor(Wektor nowy) {
    if (nowy.y >= 0) dodatnie.NowyWektor(nowy);
    if (nowy.y <= 0) ujemne.NowyWektor(nowy.symetriaOX());
  }
  // stwierdzenie, czy mozna dojsc do polosi
  bool CzyMozna() {
    Wektor w1 = dodatnie.Podaj(), w2 = ujemne.Podaj().symetriaOX();
    if (w1.y == 0) {
      return w1.x > 0;
    } else {
      return -w2.y * w1.x + w1.y * w2.x > 0;
    }
  }
};

bool SprawdzSkoczka(istream &s)
/* Wczytuje ze strumienia s opis skoczka i odpowiada, czy skoczek *
 * moze dojsc do kazdego pola.                                    */
{
  int n;
  s >> n;
  Siatka siatka;          // siatka ruchow
  DojscieNaPolos osie[4]; // obiekty sprawdzajace mozliwosc dojscia do osi
  for (int i = 0; i < n; ++i) {
    Wektor nowy;
    s >> nowy;
    siatka.DodajWektor(nowy);
    for (int j = 0; j < 4; ++j) {
      osie[j].NowyWektor(nowy);
      nowy = nowy.obrot90();
    }
  }
  // koncowe rozstrzygniecie 
  for (int j = 0; j < 4; ++j)
    if (!osie[j].CzyMozna())
      return false;
  return siatka.Zupelna();
}

int main()
{
  ifstream wejscie("sup.in");
  ofstream wyjscie("sup.out");
  int k;
  wejscie >> k;
  for (int i = 0; i < k; ++i) {
    wyjscie << (SprawdzSkoczka(wejscie) ? "TAK" : "NIE") << "\n";
  }
}
