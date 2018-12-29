/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n * log(max{x_i}) * log(n))                    *
 *   Opis:              Rozwiazanie wolniejsze                           *
 *                      Uzycie drzewa przedzialowego                     *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<iostream>
using namespace std;

const int MAXN = 1000000;

class tree {
  public:
    void init(int s) {
      for(size=1;size<s;size<<=1);
      t = new long long[2*size];
      clear();
    }
    void clear() {
      for(int i=0;i<2*size;++i)
        t[i] = 0;
    }
    void add(int p, int q, int v) { // [p; q)
      if(q <= p)
        return;
      _add(size+p, size+q, v);
    }
    long long query(int x) {
      long long ret = 0;
      for(x+=size;x;x>>=1)
        ret += t[x];
      return ret;
    }
  private:
    int size;
    long long *t;

    void _add(int p, int q, int v) {
      if(p + 1 == q) {
        t[p] += v;
        return;
      }
      if(p&1) {
        t[p] += v;
        _add(p+1, q, v);
        return;
      }
      if(q&1) {
        t[q-1] += v;
        _add(p, q-1, v);
        return;
      }
      _add(p>>1, q>>1, v);
    }
};

int x[MAXN+1]; // grubosc warstwy piasku, dane z wejscia
int pom[MAXN+1]; // pomocniczna tablica z grubosciami warstw piasku, na ktorej beda wykonywane obliczenia

tree lewa, prawa;

int n;
long long m; // liczba ruchow lopaty, na ktore Bajtazar ma sile

/* Funkcja rozwiazujaca podproblem wyrownania koryta rzeki bez dokopywania sie do wody,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p.
 * Zwraca potrzebna liczbe ruchow lopaty do osiagniecia tego celu */

long long wyrownaj(int p) {
  long long ruchy = 0; // liczba potrzebnych ruchow
  for(int i=1;i<=n-1;++i) // wyrownanie terenu od lewej do prawej
  {
    if(pom[i] + p < pom[i+1]) {
      ruchy += pom[i+1] - (pom[i] + p);
      pom[i+1] = pom[i] + p;
    }
  }
  for(int i=n;i>=2;--i) // i od prawej do lewej
  {
    if(pom[i] + p < pom[i-1]) {
      ruchy += pom[i-1] - (pom[i] + p);
      pom[i-1] = pom[i] + p;
    }
  }
  return ruchy;
}

/* Funkcja zwraca miejsce, w ktorym uda sie dokopac do poziomu 0,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p,
 * badz -1 jesli takiego miejsca nie ma. */

int gdzie_kopac(int p) {
  for(int i=1;i<=n;++i) // przygotowanie tablicy pomocniczej
    pom[i] = x[i];

  long long ruchy = wyrownaj(p);

  /* jesli Bajtazar nie ma wystarczajaco sily na wyrownanie terenu,
   * to tym bardziej na dokopanie sie do wody */
  if(ruchy > m)
    return -1;

  prawa.clear();
  lewa.clear();
  for(int i=1;i<=n;++i)
  {
    lewa.add(i, min(n+1, i + pom[i]/p), p);
    lewa.add(min(n+1, i + pom[i]/p), min(n+1, i + pom[i]/p + 1), pom[i] % p);

    prawa.add(max(1, i - pom[i]/p + 1), i+1, p);
    prawa.add(max(0, i - pom[i]/p), max(0, i - pom[i]/p + 1), pom[i] % p);
  }

  // wyliczenie kosztu dokopania sie do wody w punkcie 1
  for(int i=1;i<=n;++i)
  {
    if(pom[i] <= p*(i-1))
      break;
    else
      ruchy += (pom[i] - p*(i-1));
  }
  if(ruchy <= m)
    return 1;

  for(int i=2;i<=n;++i)
  {
    /* Aktualizacja kosztu dokopania sie do wody w miejscu i
     * na podstawie poprzedniego kosztu oraz podanego wzoru */
    ruchy = ruchy - lewa.query(i-1) + prawa.query(i);
    if(ruchy <= m)
      return i;
  }

  return -1;
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(0);
  int h = 0; // najgrubsza warstwa piasku
  long long sumx = 0;
  cin >> n >> m;
  lewa.init(n+4);
  prawa.init(n+4);
  for(int i=1;i<=n;++i)
  {
    cin >> x[i];
    sumx += x[i];
    h = max(h, x[i]);
  }
  if(sumx <= m) {
    cout << 1 << ' ' << 0 << '\n';
    return 0;
  }
  int p = 1, q = h;
  while(p < q) // wyszukiwanie binarne po wyniku
  {
    int r = (p+q)/2;
    if(gdzie_kopac(r) != -1)
      q = r;
    else
      p = r + 1;
  }
  cout << gdzie_kopac(p) << ' ' << p << '\n';
  return 0;
}
