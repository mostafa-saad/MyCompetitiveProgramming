/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Straz pozarna (STR)                                       *
 *   Plik:     str3.cpp                                                  *
 *   Autor:    Marek Sygan                                               *
 *   Opis:     Rozwiazanie wzorcowe O((p+z)*log(p+z))                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
#include <cstring>

#define FOREACH(it,X) for (__typeof((X).begin()) it = (X).begin(); it != (X).end(); ++it)

using namespace std;

typedef long long LL;

const int MAX_P = 100000; // maksymalna liczba projektow
const int MAX_Z = 100000; // maksymalna liczba zabytkow
int z, p; //liczba zabytkow i projektow

enum ObszarEnum{
  OBSZAR_NIC,
  OBSZAR_WSZYSTKIE,
  OBSZAR_SKOSWDOL_NAD,
  OBSZAR_SKOSWDOL_POD,
  OBSZAR_SKOSWGORE_NAD,
  OBSZAR_SKOSWGORE_POD,
  OBSZAR_POZIOM_POD,
  OBSZAR_POZIOM_NAD
};

struct KawalekLamanej {
  ObszarEnum obszar;
  LL y; // dla skosu lub poziomu jego wysokosc poczatkowa
  LL x_start; // od jakies wartosci x zaczyna sie ten fragment
};

struct Projekt {
  LL x1, y1, x2, y2;
  vector<KawalekLamanej> lamana; // lamana wyznaczajaca linie podzialu
                                 // na 2 obszary
  int zab_pocz;                  // zmienna pomocnicza dla zamiatania                                 
} projekty[MAX_P];

struct Zabytek {
  LL x, y;
  int poziom, skosWGore, skosWDol; //przenumerowane wspolrzedne
} zabytki[MAX_Z];

class DrzewoLicznikowe {
  int* drzewo;
  int rozmiar;
  void dodaj(int y, int krotnosc) {
    y += rozmiar;
    while (y >= 1) {
      drzewo[y] += krotnosc;
      y >>= 1;
    }
  }
  public:
  DrzewoLicznikowe(int _rozmiar) {
    rozmiar = 4;
    while (rozmiar < _rozmiar) {
      rozmiar <<= 1;
    }
    drzewo = new int[2*rozmiar];
    for (int i = 0; i < 2*rozmiar; ++i) {
      drzewo[i] = 0;
    }
  }
  ~DrzewoLicznikowe() {
    delete[] drzewo;
  }
  void dodaj(int y) {
    dodaj(y, 1);
  }
  void usun(int y) {
    dodaj(y, -1);
  }
  int ileNiemniejszych(int y) {
    return drzewo[1]-ileNiewiekszych(y-1);
  }
  int ileNiewiekszych(int y) {
    if (y < 0) return 0;
    y += rozmiar;
    int wynik = drzewo[y];
    while (y > 1) {
      if (y%2 == 1) {
        wynik += drzewo[y-1];
      }
      y >>= 1;
    }
    return wynik;
  }
};

//Kolejka do zamiatania.
priority_queue<pair<LL,int>, vector<pair<LL,int> >, greater<pair<LL,int> >  > kolejka; 
DrzewoLicznikowe* drzewoPoziom;
DrzewoLicznikowe* drzewoSkosWDol;
DrzewoLicznikowe* drzewoSkosWGore;

void wczytajDane() {
  int n, m;
  scanf("%d %d %d %d", &n, &m, &z, &p);
  for (int i = 0; i < z; ++i) {
    scanf("%lld %lld", &zabytki[i].x, &zabytki[i].y);
    zabytki[i].x *= 2; zabytki[i].y *= 2;
  }
  for (int i = 0; i < p; ++i) {
    scanf("%lld %lld %lld %lld", &projekty[i].x1, &projekty[i].y1, 
        &projekty[i].x2, &projekty[i].y2);
    projekty[i].x1 *= 2; projekty[i].y1 *= 2;
    projekty[i].x2 *= 2; projekty[i].y2 *= 2;
  }
}

//Zamiana kolejnosci posterunkow w projektach.
void zamienWParach() {
  for (int i = 0; i < p; ++i) {
    swap(projekty[i].x1, projekty[i].x2);
    swap(projekty[i].y1, projekty[i].y2);
  }
}

int wszystkieZabytki;

//Znajduje liczbe zabytkow dla danego obszaru.
int policzWczesniejszeZabytki(int i) {
  KawalekLamanej k = projekty[i].lamana.back();
  int ile = 0;
  switch (k.obszar) {
    case OBSZAR_WSZYSTKIE:
      ile = wszystkieZabytki;
      break;
    case OBSZAR_POZIOM_POD:
      ile = drzewoPoziom->ileNiewiekszych(k.y);
      break;
    case OBSZAR_POZIOM_NAD:
      ile = drzewoPoziom->ileNiemniejszych(k.y);
      break;
    case OBSZAR_SKOSWDOL_POD:
      ile = drzewoSkosWDol->ileNiewiekszych(k.y);
      break;
    case OBSZAR_SKOSWDOL_NAD:
      ile = drzewoSkosWDol->ileNiemniejszych(k.y);
      break;
    case OBSZAR_SKOSWGORE_POD:
      ile = drzewoSkosWGore->ileNiewiekszych(k.y);
      break;
    case OBSZAR_SKOSWGORE_NAD:
      ile = drzewoSkosWGore->ileNiemniejszych(k.y);
      break;
    default:
      break;
  }
  return ile;
}

void dodajZabytej(const Zabytek &zab) {
  wszystkieZabytki++;
  drzewoPoziom->dodaj(zab.poziom);
  drzewoSkosWDol->dodaj(zab.skosWDol);
  drzewoSkosWGore->dodaj(zab.skosWGore);
}

void dodajFragmentLamanej(int i) {
  int ile = policzWczesniejszeZabytki(i);
  int rozmiar = projekty[i].lamana.size();
  projekty[i].zab_pocz = ile;
  if (rozmiar > 1) {
    kolejka.push(make_pair(projekty[i].lamana[rozmiar-2].x_start, i));
  }
}

void usunFragmentLamanej(int i, int* wynik) {
  int ile = policzWczesniejszeZabytki(i);
  projekty[i].lamana.pop_back();
//  printf("faza dla i=%d dodala %d, bylo %d\n",i, ile-projekty[i].zab_pocz, projekty[i].zab_pocz);
  wynik[i] += ile - projekty[i].zab_pocz;
}

void zamiataj(int* wynik) {
  int poz_zabytki = 0; // pozycja w tablicy zabytkow
  wszystkieZabytki = 0;
  for (int i = 0; i < p; ++i) {
    dodajFragmentLamanej(i);
  }
  while (poz_zabytki < z) {
    int x = zabytki[poz_zabytki].x;
    while (!kolejka.empty() && kolejka.top().first <= x) {
      int i = kolejka.top().second;
      kolejka.pop();
      usunFragmentLamanej(i, wynik);
      if (!projekty[i].lamana.empty()) {
        dodajFragmentLamanej(i);
      }
    }
    dodajZabytej(zabytki[poz_zabytki]);
    poz_zabytki++;
  }
  for (int i = 0; i < p; ++i) {
    if (!projekty[i].lamana.empty()) {
      usunFragmentLamanej(i, wynik);
    }
  }
  while (!kolejka.empty()) {
    kolejka.pop();
  }
}

void dodajDoLamanej(vector<KawalekLamanej> &lamana, ObszarEnum obszar, 
    LL y, LL x_start) {
  KawalekLamanej k;
  k.obszar = obszar; k.y = y; k.x_start = x_start;
  lamana.push_back(k);
}

// Dla kazdego projektu znajduje liczbe zabytkow, ktore maja nie dalej do
// pierwszego posterunku niz do drugiego, wartosci zapisywane w tablicy wynik.
void pokrywaPierwszy(int* wynik) {
  vector<LL> y_zap;
  for (int i = 0; i < p; ++i) {
    LL x1 = projekty[i].x1, y1 = projekty[i].y1;
    LL x2 = projekty[i].x2, y2 = projekty[i].y2;
    LL dx = llabs((LL)x2 - x1);
    LL dy = llabs((LL)y2 - y1);
    vector<KawalekLamanej>& lamana = projekty[i].lamana;
    lamana.clear();
    if (dx == dy) {
      if (x1 < x2 && y1 < y2) {
        dodajDoLamanej(lamana, OBSZAR_WSZYSTKIE, 0, 0);
        dodajDoLamanej(lamana, OBSZAR_SKOSWDOL_POD, x1+y2, x1+1);
        dodajDoLamanej(lamana, OBSZAR_POZIOM_POD, y1, x2);
      } else if (x1 < x2 && y1 > y2) {
        dodajDoLamanej(lamana, OBSZAR_WSZYSTKIE, 0, 0);
        dodajDoLamanej(lamana, OBSZAR_SKOSWGORE_NAD, y2-x1, x1+1);
        dodajDoLamanej(lamana, OBSZAR_POZIOM_NAD, y1, x2);
      } else if (x1 > x2 && y1 < y2) {
        dodajDoLamanej(lamana, OBSZAR_POZIOM_POD, y1, 0);
        dodajDoLamanej(lamana, OBSZAR_SKOSWGORE_POD, y1-x2, x2);
        dodajDoLamanej(lamana, OBSZAR_WSZYSTKIE, 0, x1);
      } else {
        // x1 > x2 && y1 > y2
        dodajDoLamanej(lamana, OBSZAR_POZIOM_NAD, y1, 0);
        dodajDoLamanej(lamana, OBSZAR_SKOSWDOL_NAD, x2+y1, x2);
        dodajDoLamanej(lamana, OBSZAR_WSZYSTKIE, 0, x1);
      }
    } else if (dx < dy) {
      if (x1 == x2){
        if (y1 < y2) {
          dodajDoLamanej(lamana, OBSZAR_POZIOM_POD, (y1+y2)/2LL, 0);
        } else {
          dodajDoLamanej(lamana, OBSZAR_POZIOM_NAD, (y1+y2)/2LL, 0);
        }
      } else if (x1 < x2){
        if (y1 < y2) {
          dodajDoLamanej(lamana, OBSZAR_POZIOM_POD, y1+(dx+dy)/2, 0);
          dodajDoLamanej(lamana, OBSZAR_SKOSWDOL_POD, x1+(y1+(dx+dy)/2), x1);
          dodajDoLamanej(lamana, OBSZAR_POZIOM_POD, y1+(dx+dy)/2-dx, x2);
        } else {
          // y1 > y2
          dodajDoLamanej(lamana, OBSZAR_POZIOM_NAD, y1-(dx+dy)/2, 0);
          dodajDoLamanej(lamana, OBSZAR_SKOSWGORE_NAD, (y1-(dx+dy)/2)-x1, x1);
          dodajDoLamanej(lamana, OBSZAR_POZIOM_NAD, y1-((dx+dy)/2-dx), x2);
        }
      } else {
        //x1 > x2
        if (y1 < y2) {
          dodajDoLamanej(lamana,OBSZAR_POZIOM_POD, y1+((dx+dy)/2-dx), 0);
          dodajDoLamanej(lamana,OBSZAR_SKOSWGORE_POD, (y1+((dx+dy)/2-dx))-x2, x2);
          dodajDoLamanej(lamana,OBSZAR_POZIOM_POD, y1+(dx+dy)/2, x1);
        } else {
          //y1 > y2
          dodajDoLamanej(lamana, OBSZAR_POZIOM_NAD, y2+(dx+dy)/2, 0);
          dodajDoLamanej(lamana, OBSZAR_SKOSWDOL_NAD, x2+y2+(dx+dy)/2, x2);
          dodajDoLamanej(lamana, OBSZAR_POZIOM_NAD, y1-(dx+dy)/2, x1);
        }
      }
    } else {
      //dx > dy
      if (y1 == y2) {
        if (x1 < x2) {
          dodajDoLamanej(lamana, OBSZAR_WSZYSTKIE, 0, 0);
          dodajDoLamanej(lamana, OBSZAR_NIC, 0, ((LL)x1+x2)/2LL+1);
        } else {
          dodajDoLamanej(lamana, OBSZAR_NIC, 0, 0);
          dodajDoLamanej(lamana, OBSZAR_WSZYSTKIE, 0, ((LL)x1+x2)/2LL);
        }
      } else if (y1 < y2) {
        if (x1 < x2) {
          dodajDoLamanej(lamana, OBSZAR_WSZYSTKIE, 0, 0);
          dodajDoLamanej(lamana, OBSZAR_SKOSWDOL_POD, (x2-(dx+dy)/2)+y2, x2-(dx+dy)/2+1);
          dodajDoLamanej(lamana, OBSZAR_NIC, 0, x1+(dx+dy)/2+1);
        } else {
          //x1 > x2
          dodajDoLamanej(lamana, OBSZAR_NIC, 0, 0);
          dodajDoLamanej(lamana, OBSZAR_SKOSWGORE_POD, y1-(x1-(dx+dy)/2), x1-(dx+dy)/2);
          dodajDoLamanej(lamana, OBSZAR_WSZYSTKIE, 0, x2+(dx+dy)/2);
        }
      } else {
        //y1 > y2
        if (x1 < x2) {
          dodajDoLamanej(lamana, OBSZAR_WSZYSTKIE, 0, 0);
          dodajDoLamanej(lamana, OBSZAR_SKOSWGORE_NAD, y2-(x2-(dx+dy)/2), x2-(dx+dy)/2+1);
          dodajDoLamanej(lamana, OBSZAR_NIC, 0, x1+(dx+dy)/2+1);
        } else {
          //x1 > x2
          dodajDoLamanej(lamana, OBSZAR_NIC, 0, 0);
          dodajDoLamanej(lamana, OBSZAR_SKOSWDOL_NAD, x1-(dx+dy)/2+y1, x1-(dx+dy)/2);
          dodajDoLamanej(lamana, OBSZAR_WSZYSTKIE, 0, x2+(dx+dy)/2);
        }
      }
    }
    for (int j = 0; j < (int)lamana.size(); ++j) {
      y_zap.push_back(lamana[j].y);
    }
    reverse(lamana.begin(), lamana.end());
  }
  for (int i = 0; i < z; ++i) {
    y_zap.push_back(zabytki[i].y);
    y_zap.push_back(zabytki[i].x+zabytki[i].y);
    y_zap.push_back(zabytki[i].y-zabytki[i].x);
  }
  // zamiana wspolrzednych
  sort(y_zap.begin(), y_zap.end());
  y_zap.erase(unique(y_zap.begin(), y_zap.end()), y_zap.end());
  for (int i = 0; i < p; ++i) {
    FOREACH(it, projekty[i].lamana) {
      it->y = lower_bound(y_zap.begin(), y_zap.end(), it->y) - y_zap.begin();
    }
  }
  for (int i = 0; i < z; ++i) {
    zabytki[i].poziom = lower_bound(y_zap.begin(), y_zap.end(), zabytki[i].y) - y_zap.begin();
    zabytki[i].skosWGore = lower_bound(y_zap.begin(), y_zap.end(), zabytki[i].y - zabytki[i].x) - y_zap.begin();
    zabytki[i].skosWDol = lower_bound(y_zap.begin(), y_zap.end(), zabytki[i].x + zabytki[i].y) - y_zap.begin();
  }
  // Dodajemy element wiekszy od wszystkiego.
  drzewoPoziom = new DrzewoLicznikowe(y_zap.size()+1);
  drzewoSkosWDol = new DrzewoLicznikowe(y_zap.size()+1);
  drzewoSkosWGore = new DrzewoLicznikowe(y_zap.size()+1);
  zamiataj(wynik);
  delete drzewoPoziom;
  delete drzewoSkosWDol;
  delete drzewoSkosWGore;
}

bool porownajZabytki(const Zabytek& a, const Zabytek& b) {
  return a.x != b.x ? a.x < b.x : a.y < b.y;
}

void znajdzWynik() {
  int* a = new int[p];
  int* b = new int[p];
  sort(zabytki, zabytki+z, porownajZabytki);
  pokrywaPierwszy(a);
  zamienWParach();
  pokrywaPierwszy(b);
  for (int i = 0; i < p; ++i) {
    int oba = a[i] + b[i] - z;
    printf("%d %d %d\n", a[i]-oba, b[i]-oba, oba);
  }
}

int main() {
  wczytajDane();
  znajdzWynik();
  return 0;
}
