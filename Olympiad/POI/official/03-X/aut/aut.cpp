/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Autostrady                                     *
 *   Plik:                aut.cpp                                        *
 *   Autor:               Arkadiusz Paterek                              *
 *************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Odcinek {
public:
  int a, b;
  bool na_gorze;
  
  Odcinek(int a, int b, bool na_gorze = true) {
    this->a = a;
    this->b = b;
  }
  
  Odcinek() {
    Odcinek(0, 0);
  }

  bool wewnatrz(int x) {
    return x > a && x < b;
  }
  
  Odcinek odwrotnosc() {
    return Odcinek(-b, -a, na_gorze);
  }
  
  static const int minusInf;
  static const int plusInf;
};

const int Odcinek::minusInf = -100000;
const int Odcinek::plusInf = 100000;

bool operator<(const Odcinek &o1, const Odcinek &o2) {
  if (o1.a == o2.a)
    return o1.b < o2.b;
  else
    return o1.a < o2.a;
}

bool operator==(const Odcinek &o1, const Odcinek &o2) {
  return o1.a == o2.a && o1.b == o2.b;
}

class Dowiazanie {
public:
  Odcinek odcinek;
  int ile; // ile jednakowych odcinkow jest w tym dowiazaniu
  int max_b; // maksymalne b w poddrzewie
  Dowiazanie *lewySyn, *prawySyn, *ojciec;
  
  Dowiazanie(Odcinek odcinek) {
    this->odcinek = odcinek;
    ile = 1;
    max_b = odcinek.b;
    lewySyn = prawySyn = ojciec = NULL;
  }

  Dowiazanie() {
    odcinek = Odcinek(0,0);
    ile = 0;
    max_b = 0;
    lewySyn = prawySyn = ojciec = NULL;    
  }
  
  void usynow(Dowiazanie *lewy, Dowiazanie *prawy) {
    lewySyn = lewy;
    prawySyn = prawy;
    poprawMaxB();
  }
  
  void poprawMaxB() {
    max_b = odcinek.b;
    if (lewySyn)
      max_b = max(max_b, lewySyn->max_b);
    if (prawySyn)
      max_b = max(max_b, prawySyn->max_b);
  }
  
  static void wypiszPuste(ostream &os, int wciecie) {
    for (int i = 0; i < wciecie; ++i)
      os << " ";
    os << "0\n";
  }
  
  void wypisz(ostream &os, int wciecie) {
    for (int i = 0; i < wciecie; ++i)
      os << " ";
    os << "(" << odcinek.a << "," << odcinek.b << ")  ile=" << ile << "  max_b=" << max_b << "\n";
    
    if (lewySyn)
      lewySyn->wypisz(os, wciecie + 2);
    else
      wypiszPuste(os, wciecie + 2);
    if (prawySyn)
      prawySyn->wypisz(os, wciecie + 2);
    else
      wypiszPuste(os, wciecie + 2);
  }
};

typedef vector<Dowiazanie *> Sciezka;

class ZbiorOdcinkow {
public:
  Dowiazanie *korzen;

private:  
  inline void splay(Odcinek klucz, Dowiazanie *&korzen_poddrzewa) {
    static Sciezka sciezka;
    static Dowiazanie *d;
    
    if (!korzen_poddrzewa)
      return;
    
    sciezka.clear();
    d = korzen_poddrzewa;
    while(d) {
      sciezka.push_back(d);
      
      if (d->odcinek == klucz)
        break;
      else if (d->odcinek > klucz)
        d = d->lewySyn;
      else
        d = d->prawySyn;
    }
    
    Dowiazanie *x, *y, *z, *A, *B, *C, *D;
    x = sciezka.back(); sciezka.pop_back();
    while (sciezka.size() >= 2) {
      y = sciezka.back(); sciezka.pop_back();
      z = sciezka.back(); sciezka.pop_back();
      
      if (z->lewySyn == y)
        if (y->lewySyn == x) { // rotacja
          A = x->lewySyn;  //    z         x
          B = x->prawySyn; //   y D   ->  A y
          C = y->prawySyn; //  x C         B z
          D = z->prawySyn; // A B           C D
          z->usynow(C, D);
          y->usynow(B, z);
          x->usynow(A, y);
        } else { // krok rozchylaj±cy
          A = y->lewySyn;  //    z          x
          B = x->lewySyn;  //   y D   ->  y   z
          C = x->prawySyn; //  A x       A B C D
          D = z->prawySyn; //   B C         
          z->usynow(C, D);
          y->usynow(A, B);
          x->usynow(y, z);
        }
      else
        if (y->lewySyn == x) { // krok rozchylaj±cy
          A = z->lewySyn;  //    z           x
          B = x->lewySyn;  //   A y   ->   z   y
          C = x->prawySyn; //    x D      A B C D
          D = y->prawySyn; //   B C         
          z->usynow(A, B);
          y->usynow(C, D);
          x->usynow(z, y);
        } else { // rotacja
          A = z->lewySyn;  //  z            x
          B = y->lewySyn;  // A y   ->     y D
          C = x->lewySyn;  //  B x        z C
          D = x->prawySyn; //   C D      A B
          z->usynow(A, B);
          y->usynow(z, C);
          x->usynow(y, D);
        }
      
      if (sciezka.size() >= 1) {
        d = sciezka.back();
        if (d->lewySyn == z)
          d->lewySyn = x;
        else
          d->prawySyn = x;
      }
    }
    
    if (sciezka.size() == 1) { // rotacja pojedyncza
      y = sciezka.back(); sciezka.pop_back();
      if (y->lewySyn == x) {
        A = x->lewySyn;  //   y          x
        B = x->prawySyn; //  x C   ->   A y
        C = y->prawySyn; // A B          B C
        y->usynow(B, C);
        x->usynow(A, y);
      } else {
        A = y->lewySyn;  //  y          x
        B = x->lewySyn;  // A x   ->   y C
        C = x->prawySyn; //  B C      A B
        y->usynow(A, B);
        x->usynow(y, C);
      }
    }
    
    korzen_poddrzewa = x;
  }

  // znajduje w odcinek ze wspó³rzêdn± a nale¿±c± do przedzialA,
  // oraz b nalezaca do przedzialB
  Dowiazanie *znajdz(Odcinek przedzialA, Odcinek przedzialB) {
    Dowiazanie *d, *start;
//    cout << "przed:\n" << *this << "\n";
//    splay(Odcinek((przedzialA.a + przedzialA.b)/2, przedzialB.a), korzen);
//    cout << "po:\n" << *this << "\n";

    start = korzen;
    while (start) { // szuka odcinka z pocz±tkiem w przedzialA
      if (start->odcinek.a <= przedzialA.a)
        start = start->prawySyn;
      else if (start->odcinek.a >= przedzialA.b)
        start = start->lewySyn;
      else
        break;
    }
    if (!start)
      return NULL;
    
    // sprawdzam korzeñ
    if (przedzialB.wewnatrz(start->odcinek.b))
      return start;
    
    // sprawdzam praw± ¶cie¿kê bez pierwszego elementu
    d = start->prawySyn;
    while(d) {
      if (!przedzialB.wewnatrz(d->max_b))
        break;
      if (d->odcinek.a < przedzialA.b) {
        if (przedzialB.wewnatrz(d->odcinek.b))
          return d;
        if (d->lewySyn && przedzialB.wewnatrz(d->lewySyn->max_b)) {
          d = d->lewySyn;
          break;
        }
      }
      if (d->prawySyn && d->odcinek.a < przedzialA.b)
        d = d->prawySyn;
      else
        d = d->lewySyn;
    }
    
    // je¶li znalaz³em odga³êzienie z dobrym b, przeszukujê je
    // (mam gwarancjê, ¿e a jest dobre w ca³ym poddrzewie d)
    while (d && przedzialB.wewnatrz(d->max_b)) {
      if (przedzialB.wewnatrz(d->odcinek.b))
        return d;      
      if (d->lewySyn && przedzialB.wewnatrz(d->lewySyn->max_b))
        d = d->lewySyn;
      else
        d = d->prawySyn;
    }

    // to samo dla lewej ¶cie¿ki
    d = start->lewySyn;
    while(d) {
      if (!przedzialB.wewnatrz(d->max_b))
        break;
      if (d->odcinek.a > przedzialA.a) {
        if (przedzialB.wewnatrz(d->odcinek.b))
          return d;
        if (d->prawySyn && przedzialB.wewnatrz(d->prawySyn->max_b)) {
          d = d->prawySyn;
          break;
        }
      }
      if (d->lewySyn && d->odcinek.a > przedzialA.a)
        d = d->lewySyn;
      else
        d = d->prawySyn;
    }
    
    while (d && przedzialB.wewnatrz(d->max_b)) {
      if (przedzialB.wewnatrz(d->odcinek.b))
        return d;      
      if (d->lewySyn && przedzialB.wewnatrz(d->lewySyn->max_b))
        d = d->lewySyn;
      else
        d = d->prawySyn;
    }
    
    
    return NULL;
  }

public:
  ZbiorOdcinkow() {
    korzen = NULL;
  }

  void wstaw(Odcinek odcinek) {
    if (!korzen) {
      korzen = new Dowiazanie(odcinek);
      return;
    }
    
    splay(odcinek, korzen);
    if (korzen->odcinek == odcinek)
      ++korzen->ile;
    else {
      Dowiazanie *nowy = new Dowiazanie(odcinek);
      if (korzen->odcinek > nowy->odcinek) {
        nowy->lewySyn = korzen->lewySyn;
        nowy->prawySyn = korzen;
        korzen->lewySyn = NULL;
        korzen = nowy;
        korzen->prawySyn->poprawMaxB();
        korzen->poprawMaxB();
      } else {
        nowy->prawySyn = korzen->prawySyn;
        nowy->lewySyn = korzen;
        korzen->prawySyn = NULL;
        korzen = nowy;
        korzen->lewySyn->poprawMaxB();
        korzen->poprawMaxB();
      }
    }
  }
  
  void usun(Dowiazanie *d) {
    usun(d->odcinek);
  }
  
  void usun(Odcinek odcinek) {
    splay(odcinek, korzen);
    Dowiazanie *tmp = korzen;
    if (korzen->lewySyn) {
      splay(odcinek, korzen->lewySyn);
      korzen->lewySyn->prawySyn = korzen->prawySyn;
      korzen = korzen->lewySyn;
      korzen->poprawMaxB();
    } else
      korzen = korzen->prawySyn;
    delete tmp;
  }
  
  Dowiazanie *znajdzZachodzacy(Odcinek odcinek) {
    return znajdz(odcinek, Odcinek(odcinek.b, Odcinek::plusInf));
  }
  
  friend ostream& operator<<(ostream &os, const ZbiorOdcinkow &zbior);
};

ostream& operator<<(ostream &os, const ZbiorOdcinkow &zbior) {
  if (zbior.korzen)
    zbior.korzen->wypisz(os, 0);
  else
    os << "0\n";
  return os;
}

ZbiorOdcinkow zbior, zbiorOdw;
set<Odcinek> odwiedzone;

void dfs(Odcinek przedzial, bool na_gorze, int depth) {
  set<Odcinek>::iterator po;
  if ((po = odwiedzone.find(przedzial)) != odwiedzone.end()) {
    return;
  }
  przedzial.na_gorze = na_gorze;
  odwiedzone.insert(przedzial);

  Dowiazanie *d;
  vector<Odcinek> sasiedzi;

  while ((d = zbior.znajdzZachodzacy(przedzial))) {
    sasiedzi.push_back(d->odcinek);
    zbiorOdw.usun(d->odcinek.odwrotnosc());
    zbior.usun(d);
  }

  while ((d = zbiorOdw.znajdzZachodzacy(przedzial.odwrotnosc()))) {
    sasiedzi.push_back(d->odcinek.odwrotnosc());
    zbior.usun(d->odcinek.odwrotnosc());
    zbiorOdw.usun(d);
  }
  
  for (Odcinek *po = sasiedzi.begin(); po != sasiedzi.end(); ++po)  
    dfs(*po, !na_gorze, depth + 1);
}

void oblicz() {
  Odcinek odcinek;
  while (zbior.korzen) {
    odcinek = zbior.korzen->odcinek;
    zbiorOdw.usun(zbior.korzen->odcinek.odwrotnosc());
    zbior.usun(zbior.korzen);
    dfs(odcinek, true, 0);
  }
}

void wczytaj(vector<Odcinek> &dane) {
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= k; ++i) {
    int p, q;
    cin >> p >> q;
    dane.push_back(Odcinek(p, q));
    Odcinek odcinek(p,q);
    zbior.wstaw(odcinek);
    zbiorOdw.wstaw(odcinek.odwrotnosc());
  }
}


// sprawdza poprawno¶æ rozwi±zania
bool poprawne(set<Odcinek> zbior2) {
  ZbiorOdcinkow na_gorze, na_dole;
  vector<Odcinek> zbior;
  Odcinek *po;
  copy(zbior2.begin(), zbior2.end(), back_inserter(zbior));
  random_shuffle(zbior.begin(), zbior.end());
  
  for (po = zbior.begin(); po != zbior.end(); ++po) {
    if (po->na_gorze)
      na_gorze.wstaw(*po);
    else
      na_dole.wstaw(*po);
  }
  for (po = zbior.begin(); po != zbior.end(); ++po) {
    if (po->na_gorze)
      if (na_gorze.znajdzZachodzacy(*po))
        return false;
      else;
    else
      if (na_dole.znajdzZachodzacy(*po))
        return false;
      else;
  }
  return true;
}

void wypisz(vector<Odcinek> &dane) {
  if (poprawne(odwiedzone)) {
    for (Odcinek *po = dane.begin(); po != dane.end(); ++po) {
      set<Odcinek>::iterator po2 = odwiedzone.find(*po);
      if (po2 == odwiedzone.end())
        cout << "blad: odcinka nie ma w zbiorze odwiedzone\n";
      else
        if (po2->na_gorze)
          cout << "N\n";
        else
          cout << "S\n";
    }
  } else
    cout << "NIE\n";
}

int main() {
  vector<Odcinek> dane;

  wczytaj(dane);
  
  oblicz();
  
  wypisz(dane);
  
  return 0;
}
