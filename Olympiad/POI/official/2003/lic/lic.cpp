/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Liczby Przesmyków                              *
 *   Plik:                lic.cpp                                        *
 *   Autor:               Krzysztof Onak                                 *
 *************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

class DuzaLiczba {
// klasa du¿ych dodatnich liczb ca³kowitych
public:

  DuzaLiczba(int malaLiczba = 0) : cyfry(0)
  // konstruktor, inicjacja zwyk³± liczb± ca³kowit±
  {
    // dodajemy kolejne cyfry naszej liczby
    while (malaLiczba != 0) {
      cyfry.push_back(malaLiczba % PODSTAWA);
      malaLiczba /= PODSTAWA;
    }
  }
  
  const DuzaLiczba& operator+=(const DuzaLiczba &skladnik)
  // zwiêkszenie liczby o podan± warto¶æ
  {
    int przeniesienie = 0;
    int stop = max(cyfry.size(), skladnik.cyfry.size()); // wiêksza z d³ugo¶ci
    // zwyk³e dodawanie kolejnych cyfr w pêtli
    for (int i = 0; i < stop; ++i) {
      przeniesienie += cyfra(i) + skladnik.cyfra(i);
      zmienCyfre(i, przeniesienie % PODSTAWA);
      przeniesienie /= PODSTAWA;
    }
    // sprawdzenie czy nie nast±pi³o przepe³nienie
    if (przeniesienie != 0) zmienCyfre(stop, przeniesienie);
    return *this;
  }

  const DuzaLiczba& operator-=(const DuzaLiczba &odjemnik)
  // zmiejszenie liczby o podan± warto¶æ;
  // zak³adamy, ¿e wynik odejmowania jest nieujemny
  {
    int przeniesienie = 0, stop = cyfry.size();
    // w pêtli odejmujemy kolejne cyfry
    for (int i = 0; i < stop; ++i) {
      int roznica = przeniesienie + cyfra(i) - odjemnik.cyfra(i);
      if (roznica < 0) {
        przeniesienie = -1;
	roznica += PODSTAWA;
      } else {
        przeniesienie = 0;
      }
      zmienCyfre(i, roznica);
    }
    // je¶li jakie¶ pocz±tkowe cyfry siê wyzerowa³y,
    // to je usuwamy
    while (!cyfry.empty() && cyfry.back() == 0)
      cyfry.pop_back();
    return *this;
  }
  
  bool operator<(const DuzaLiczba& druga) const
  // porównanie dwóch du¿ych liczb
  {
    // je¶li druga liczba jest d³u¿sza, to na pewno jest wiêksza
    if (druga.cyfry.size() > cyfry.size()) return true;
    // w pêtli porównujemy kolejne cyfry
    for (int i = cyfry.size() - 1; i >= 0; --i) {
      int a = cyfra(i), b = druga.cyfra(i);
      if (a < b) return true;
      if (a > b) return false;
    }
    // liczby s± równe
    return false;
  }
  
private:

  // podstawa systemu, w którym wykonujemy dzia³ania
  static const int PODSTAWA = 1024*1024*1024; // = 2^30
  
  // kolejne cyfry liczby w systemie o podstawie PODSTAWA;
  // zak³adamy, ¿e najbardziej znacz±ca cyfra (o ile istnieje)
  // jest ró¿na od zera
  vector<int> cyfry;
  
  int cyfra(int pos) const
  // zwraca podan± cyfrê z reprezentacji lub zero,
  // je¶li cyfra wykracza poza reprezentacjê
  {
    return (pos < (int)cyfry.size()) ? cyfry[pos] : 0;
  }

  void zmienCyfre(int pos, int wart)
  // je¶li istnieje cyfra o numerze pos w reprezentacji,
  // to jest ona zamieniana na wart,
  // wpp. zak³adamy, ¿e powstaje nowa cyfra
  // rozszerzaj±ca dotychczasow± reprezentacjê
  {
    if (pos < (int)cyfry.size())
      cyfry[pos] = wart;
    else
      cyfry.push_back(wart);
  }

};

// przydatne sta³e
const DuzaLiczba ZERO(0);
const DuzaLiczba JEDEN(1);

class LiczbyCiagow {
// podaje liczby ci±gów o zadanej d³ugo¶ci przy ustalonej
// warto¶ci m (maksymalna liczba minusów pod rz±d)
public:

  // inicjacja warto¶ci± m
  LiczbyCiagow(int mm) : m(mm) {liczby.push_back(JEDEN);}
  
  const DuzaLiczba& operator[](int indeks) const
  // zwraca liczbê ci±gów o d³ugo¶ci indeks
  {
    // warto¶ci wynikaj±ce z umowy
    if (indeks < -1) return ZERO;
    if (indeks == -1) return JEDEN;
    // ewentualne doliczenie brakuj±cych warto¶ci
    for (int i = liczby.size(); i <= indeks; ++i) {
      liczby.push_back(liczby[i - 1]);
      liczby[i] += liczby[i - 1];
      liczby[i] -= (*this)[i - m - 2];
    }
    return liczby[indeks];
  }
  
  // zwraca warto¶æ m
  int podajM() const {return m;}
  
private:
  // liczba m - ograniczenie na liczbê minusów pod rz±d
  int m;
  // wektor dotychczas obliczonych warto¶ci
  mutable vector<DuzaLiczba> liczby;
};

void odkoduj(const string &zakodowana, DuzaLiczba &odkodowana,
             const LiczbyCiagow &L)
// odkodowuje ci±g plusów i minusów zakodowana,
// wynik zapisuje w odkodowana,
// korzysta ze struktury podaj±cej liczby ci±gów L
{
  int rozmiar = zakodowana.size(), m = L.podajM();
  odkodowana = ZERO;
  // uwzglêdniamy krótsze ci±gi
  for (int i = 1; i < rozmiar; ++i)
    odkodowana += L[i];
  for (int i = 0; i < rozmiar; ++i) {
    // niezmiennik: wynik = odkodowana + (numer ci±gu zakodowana[i..rozmiar-1]
    //                                    w¶ród ci±gów tej samej d³ugo¶ci)
    int rozmiarPodciagu = rozmiar - i;
    odkodowana -= L[rozmiarPodciagu - m - 2];
    if (zakodowana[i] == '+') odkodowana += L[rozmiarPodciagu - 1];
  }
}

void wypiszZakodowana(const DuzaLiczba &odkodowana, ostream &strumien,
                      const LiczbyCiagow &L)
// koduje liczbe odkodowana,
// wynik zapisuje bezpo¶rednio w strumieniu strumien,
// korzysta ze struktury podaj±cej liczby ci±gów L
{
  DuzaLiczba liczba = odkodowana;
  int m = L.podajM();
  int rozmiar;
  // ustalamy d³ugo¶æ ci±gu
  for (rozmiar = 1; !(liczba < L[rozmiar]); ++rozmiar)
    liczba -= L[rozmiar];
  // wypisujemy kolejne cyfry
  for (int i = rozmiar; i > 0; --i) {
    // w tej chwili pozostaje wypisaæ ci±g d³ugo¶ci i
    // o numerze liczba w¶ród ci±gów tej d³ugo¶ci
    liczba += L[i - m - 2]; // krótsze ci±gi psute przez pocz±tkowy minus
    // decyzja '+' czy '-'
    if (liczba < L[i - 1]) {
      strumien << '-';
    } else {
      strumien << '+';
      liczba -= L[i - 1];
    }
  }
}

int main()
// g³ówny program
{
  int m1, m2, n;
  cin >> m1 >> m2 >> n;
  LiczbyCiagow ciagiWejsciowe(m1), ciagiWyjsciowe(m2);
  // w pêtli przetwarzamy kolejne ci±gi wej¶ciowe
  for (int i = 0; i < n; ++i) {
    string staraLiczba;
    // wczytanie ci±gu
    cin >> staraLiczba;
    DuzaLiczba odkodowana;
    // odkodowanie
    odkoduj(staraLiczba, odkodowana, ciagiWejsciowe);
    // zakodowanie i zapisanie
    wypiszZakodowana(odkodowana, cout, ciagiWyjsciowe);
    cout << '\n';
  }
}
