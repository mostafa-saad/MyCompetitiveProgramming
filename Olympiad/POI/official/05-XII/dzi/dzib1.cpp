/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DZI (Dziuple)                                  *
 *   Plik:                dzib1.cpp                                      *
 *   Autor:               Wojciech Dudek                                 *
 *   Opis:                Rozwiazanie niepoprawne                        *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <vector>
#include <list>
using namespace std;

#define IZOLOWANY 0
    // wierzcho³ek który ma conajmniej jedego sasiada stopnia 1 i stopnia > 1   
#define W2 2
    // inne wierzcho³ki
#define W1 1

int n, m, k;

class Int {                     // liczby calkowite modulo k
  int x;
public:
  Int(int y):x(y) {
  }

  int toint() {
    return x;
  }

  Int operator*=(const Int & y) {
    x = (((long long) x) * y.x) % k;
    return *this;
  }

  Int operator*(const Int & y) const {
    return Int(((long long) x) * y.x % k);
  }
  
  bool operator==(const Int & y) const {
    return x == y.x;
  }
  
  // mnozy przez liczby: s+0 ... s+y
  Int mulXFrom(int s, int y) {
    for (int i = 0; i < y; i++)
      this->operator*=(i + s);
    return *this;
  }
  Int perm(int n) {
    return mulXFrom(1, n);
  }
};

typedef list < int > ListaWierz;

class Tree {
  vector < ListaWierz > tab;
  vector < int >stopien;
   vector < bool > byl;
  int typ;
public:
  Tree(int x) {
    tab.resize(x);
    stopien.resize(x);
    byl.resize(x);
  }

  void dodaj(int a, int b) {
    tab[a].push_back(b);
    ++stopien[a];
    tab[b].push_back(a);
    ++stopien[b];
  }

  Int dfs(int x, int father, int *typ) {
    if (byl[x])                 //jezeli mamy cykl
      return 0;
    byl[x] = true;              //odwiedzony
    Int wynik = 1;
    if (stopien[x] == 0)
      *typ |= IZOLOWANY;
    else {
      int wierz2 = 0;
      for (ListaWierz::iterator i = tab[x].begin(); i != tab[x].end(); ++i) {
        if (stopien[*i] >= 2)
          ++wierz2;
        if (wierz2 > 2)
          return 0;
        if ((*i) != father)     // sprawdzamy wszystkich oprocz ojca
          wynik *= dfs(*i, x, typ);
        if (wynik == 0)
          return 0;
      }
      wynik.perm(stopien[x] - wierz2);  // permutacja lisci
      if ((wierz2 > 0) && (stopien[x] - wierz2 > 0))
        *typ |= W2;
      else
        *typ |= W1;
    }
    return wynik;
  }

  int count() {
    int skladowe = 0;
    int izolowane = 0;
    Int wynik = 1;
    for (int i = 1; i <= n; ++i) {
      typ = IZOLOWANY;
      if (!byl[i]) {
        ++skladowe;
        Int p = dfs(i, 0, &typ);
        if (p == 0)
          return 0;
        if (typ == IZOLOWANY)   // wierzcholek izolowany
          ++izolowane;
        else {
          if (typ >= W2)        // odbicie lustrzane w poziomie
            p *= 2;
          p *= 2;               // odbicie lustrzne w pionie
        }
        wynik *= p;
      }
    }
    wynik.perm(skladowe - izolowane); // mieszamy skladowe
    wynik.mulXFrom((n - izolowane) + 2, izolowane); //wciskamy izolowane
    return wynik.toint();
  }
};

int main()
{
  scanf("%d %d %d\n", &n, &m, &k);

  if (n <= m) {
    printf("0\n");
    return 0;
  }

  Tree *las = new Tree(n + 1);

  for (int i = 1; i <= m; i++) {
    int a, b;
    scanf("%d %d\n", &a, &b);
    las->dodaj(a, b);
  }

  printf("%d\n", las->count());

}
