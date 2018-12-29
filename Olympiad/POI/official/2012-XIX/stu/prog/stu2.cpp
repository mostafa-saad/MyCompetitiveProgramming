/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n * log(max{x_i}))                             *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<iostream>
using namespace std;

const int MAXN = 1000000;

/* Struktura zwyklej kolejki z dodatkowa mozliwoscia
 * zapytania sie o najmniejszy element w kolejce
 * w czasie stalym. */

class min_queue {
  public:
    void clear() {
      front = back = Smintop = Sminbot = 0;
      sum = 0;
    }
    void push(long long x) {
      sum += x;
      T[back++] = x;
      while(Smintop != Sminbot && Smin[Smintop-1] > x)
        --Smintop;
      Smin[Smintop++] = x;
    }
    long long pop() {
      sum -= T[front];
      if(Smin[Sminbot] == T[front])
        ++Sminbot;
      return T[front++];
    }
    long long getMin() {
      return Smin[Sminbot];
    }
    int getSize() {
      return back - front;
    }
    long long getSum() {
      return sum;
    }
  private:
    long long T[MAXN];
    int front, back;
    long long Smin[MAXN];
    int Smintop, Sminbot;
    long long sum;
};

int x[MAXN+1]; // grubosc warstwy piasku, dane z wejscia
int pom[MAXN+1]; // pomocniczna tablica z grubosciami warstw piasku, na ktorej beda wykonywane obliczenia

long long lewa[MAXN+2];
long long prawa[MAXN+2];

int n;
long long m; // liczba ruchow lopaty, na ktore Bajtazar ma sile

/* Funkcja wylicza dla kazdego miejsca koszt dokopania sie do poziomu 0
   oraz wyrownania terenu od lewego konca do tego miejsca. */

min_queue Q;

void kop(int p, long long t[]) {
  Q.clear();
  long long ruchy = 0;
  long long b = 0;
  for(int i=1;i<=n;++i)
  {
    if(i != 1 && pom[i-1] + p < pom[i]) { // wyrownanie aktualnego miejsca wzgledem sasiada po lewej
      ruchy += pom[i] - (pom[i-1] + p);
      pom[i] = pom[i-1] + p;
    }
    Q.push(b + pom[i]);
    while(Q.getMin() < b)
    {
      ruchy -= Q.getMin();
      ruchy += Q.pop();
    }
    t[i] = ruchy - b*Q.getSize() + Q.getSum(); // zapamietanie kosztu
    b += p;
  }
}

/* Funkcja zwraca miejsce, w ktorym uda sie dokopac do poziomu 0,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p,
 * badz -1 jesli takiego miejsca nie ma. */

int gdzie_kopac(int p) {
  for(int i=1;i<=n;++i) // przygotowanie tablicy pomocniczej
    pom[i] = x[i];
  kop(p, lewa); // liczenie kosztow od lewej
  for(int i=1;i<=n;++i)
    pom[i] = x[n-i+1];
  kop(p, prawa); // liczenie kosztow od prawej
  for(int i=n;i>=1;--i)
  {
    if(lewa[i] + prawa[n-i+1] - x[i] <= m)
      return i;
  }
  return -1;
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(0);
  int h = 0; // najgrubsza warstwa piasku
  cin >> n >> m;
  for(int i=1;i<=n;++i)
  {
    cin >> x[i];
    h = max(h, x[i]);
  }
  int p = 0, q = h;
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
