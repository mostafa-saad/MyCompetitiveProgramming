/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DZI (Dziuple)                                  *
 *   Plik:                dzib2.cpp                                      *
 *   Autor:               Wojciech Dudek                                 *
 *   Opis:                Rozwiazanie niepoprawne                        *
 *                        modyfikacja dzib1.cpp - brak sprawdzania kiedy *
 *                        mozna zrobic odbicie lustrzne                  *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <vector>
#include <list>
using namespace std;

#define IZOLOWANY 0
#define W1 1

#define VAR(i,e) __typeof(e) i = (e)
#define FOREACH(i,c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define FOR(i,n) for(int i=1; i <= (int)(n); ++i)

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
  } bool operator==(const Int & y) const {
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

  bool pladzielna(int x, int father) {
    if (byl[x])
      return 0;                 //czy mamy cykl
    byl[x] = true;
    int w2 = 0;
    FOREACH(i, tab[x]) {
      if (*i != father)
        if (!pladzielna(*i, x))
          return false;
      if (stopien[*i] > 2)
        ++w2;
      if (w2 > 2)
        return false;
    }
    return true;
  }

  bool pladzielny() {
    FOR(i, n)
        if (!byl[i])
      if (!pladzielna(i, 0))
        return false;
    return true;
  }

  void dfs(int x, int father, int *typ, Int * wynik) {
    byl[x] = true;

    if (stopien[x] == 0)
      *typ |= IZOLOWANY;
    else {
      int pojedyncze = 0;
      FOREACH(i, tab[x]) {
        if (stopien[*i] == 1)
          ++pojedyncze;
        if (*i != father)       // sprawdzamy wszystkich oprocz ojca
          dfs(*i, x, typ, wynik);
      }
      wynik->perm(pojedyncze);  // permutacja lisci
      *typ |= W1;
    }
  }

  int count() {
    int skladowe = 0;
    int izolowane = 0;
    Int wynik = 1;
    FOR(i, n) byl[i] = false;
    FOR(i, n) {
      typ = IZOLOWANY;
      if (!byl[i]) {
        ++skladowe;
        dfs(i, 0, &typ, &wynik);
        if (typ == IZOLOWANY)   // wierzcholek izolowany
          ++izolowane;
        else
          wynik *= 4;           // odbicie lustrzne w pionie(przekoloraownie) i poziomie
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
  k = 100000;

  Tree *las = new Tree(n + 1);

  FOR(i, m) {
    int a, b;
    scanf("%d %d\n", &a, &b);
    las->dodaj(a, b);
  }

  if (!las->pladzielny())
    printf("0\n");
  else
    printf("%d\n", las->count());
}
