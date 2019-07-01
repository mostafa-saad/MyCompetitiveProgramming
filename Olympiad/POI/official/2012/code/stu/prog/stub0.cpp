/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n * log(max{x_i}))                             *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Brak wyrownania calego terenu, tylko w okolicy   *
 *                      miejsca dokopania sie do wody                    *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<iostream>
using namespace std;

const int MAXN = 1000000;

int x[MAXN+1]; // grubosc warstwy piasku, dane z wejscia
int pom[MAXN+1]; // pomocniczna tablica z grubosciami warstw piasku, na ktorej beda wykonywane obliczenia

long long lewa[MAXN+2];
long long prawa[MAXN+2];

int n;
long long m; // liczba ruchow lopaty, na ktore Bajtazar ma sile

/* Funkcja zwraca miejsce, w ktorym uda sie dokopac do poziomu 0,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p,
 * badz -1 jesli takiego miejsca nie ma. */

int gdzie_kopac(int p) {
  for(int i=1;i<=n;++i) // przygotowanie tablicy pomocniczej
    pom[i] = x[i];

  long long ruchy = 0;

  for(int i=0;i<=n+1;++i)
    lewa[i] = prawa[i] = 0;
  for(int i=1;i<=n;++i)
  {
    lewa[i] += p;
    lewa[min(n+1, i + pom[i]/p)] -= p;
    lewa[min(n+1, i + pom[i]/p)] += (pom[i] % p);
    if(i + pom[i]/p <= n)
      lewa[i + pom[i]/p + 1] -= (pom[i] % p);

    prawa[max(1, i - pom[i]/p + 1)] += p;
    prawa[i+1] -= p;
    prawa[max(0, i - pom[i]/p)] += (pom[i] % p);
    if(i - pom[i]/p >= 1)
      prawa[i - pom[i]/p + 1] -= (pom[i] % p);
  }

  // wyliczenie kosztu dokopania sie do wody w punkcie 1
  for(int i=1;i<=n;++i)
  {
    if(pom[i] <= (long long)p*(i-1))
      break;
    else
      ruchy += (pom[i] - (long long)p*(i-1));
  }
  if(ruchy <= m)
    return 1;

  long long sl = lewa[1];
  long long sp = prawa[1];
  for(int i=2;i<=n;++i)
  {
    /* Aktualizacja kosztu dokopania sie do wody w miejscu i
     * na podstawie poprzedniego kosztu oraz podanego wzoru */
    sp += prawa[i];
    ruchy = ruchy - sl + sp;
    sl += lewa[i];
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
