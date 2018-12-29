/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Bezpieczenstwo minimalistyczne                   *
 *   Autor:             Marek Cygan                                      *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *   Opis:              Rozwiazanie autorskie                            *
 *                                                                       *
 *************************************************************************/

#include <vector>
#include <utility>
#include <cstdio>

using namespace std;

const int MAXN = 500000;
int n, m; //liczba wierzcholkow i krawedzi
int p[MAXN]; //poczatkowa liczba policjantow

/* Reprezentacja funkcji liniowej. */
struct Flin{
  int a;
  long long b;
  Flin(int _a = 0, long long _b = 0) {
    a = _a; b = _b;
  }
} f[MAXN];

vector<pair<int,int> > kraw[MAXN]; // wektor krawedzi incydentnych (wierzcholek, b)

int odwiedzony[MAXN];
vector<int> skladowa;

/* 
   Przeszukiwanie grafu metoda DFS. Wierzcholki spojnej skladowej
   sa dodawane do wektora skladowa. Procedura wyznacza tez
   docelowa liczbe policjantow jako funkcje liczby policjantow
   w wierzcholku danej spojnej skladowej o najmniejszym numerze.
 */
void dfs(int v) {
  odwiedzony[v] = 1;
  skladowa.push_back(v);
  for (int i = 0; i < (int)kraw[v].size(); ++i) {
    int x = kraw[v][i].first;
    if (!odwiedzony[x]) {
      f[x] = Flin(-f[v].a, kraw[v][i].second-f[v].b);
      dfs(x);
    }
  }
}

/* 
   Procedura oblicza minimalna oraz maksymalna liczbe zwolnionych
   skladowych dla spojnej skladowej, ktorej wierzcholki znajduja
   sie w wektorze spojna.
*/
int oblicz_skladowa(long long &wynik_min, long long &wynik_max) {
  /* Ograniczenie dolne oraz gorne dla zmiennej w rowazanej skladowej. */
  long long min_wartosc = 0, max_wartosc = p[skladowa[0]]; 
  
  /* Sprawdzenie rownan dla wszystkich krawedzi. */
  for (int i = 0; i < (int)skladowa.size(); ++i) {
    int v = skladowa[i];
    for (int j = 0; j < (int)kraw[v].size(); ++j) {
      int x = kraw[v][j].first;
      int b = kraw[v][j].second;
      if (f[v].a != f[x].a) {
        if (f[v].b + f[x].b != b) {
          /* sprzeczne rownanie */
          return 0;
        }
      } else {
        long long w = b - (f[v].b + f[x].b);
        if (f[v].a < 0) w = -w;
        if (w < 0 || w % 2) return 0;
        w /= 2;

        min_wartosc = max(min_wartosc, w);
        max_wartosc = min(max_wartosc, w);
      }
    }
  }

  Flin suma;
  long long suma_pracujacych = 0;

  /* Sprawdzenie ograniczen dla wszystkich wierzcholkow. */
  for (int i = 0; i < (int)skladowa.size(); ++i) {
    int v = skladowa[i];
    suma_pracujacych += p[v];
    /* 0 <= f[v].a * x + f[v].b <= p[v] */
    if (f[v].a == 1){
      min_wartosc = max(min_wartosc, -f[v].b);
      max_wartosc = min(max_wartosc, p[v] - f[v].b);
    } else {
      max_wartosc = min(max_wartosc, f[v].b);
      min_wartosc = max(min_wartosc, f[v].b - p[v]);
    }
    suma.a += f[v].a;
    suma.b += f[v].b;
  }

  if (min_wartosc > max_wartosc) return 0;
  long long wmin = suma_pracujacych - (suma.a * min_wartosc + suma.b);
  long long wmax = suma_pracujacych - (suma.a * max_wartosc + suma.b);

  if (wmin > wmax) swap(wmin, wmax);
  wynik_min += wmin;
  wynik_max += wmax;
  return 1;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%d", p+i);
  for (int i = 0; i < m; ++i) {
    int u, v, b;
    scanf("%d %d %d", &u, &v, &b);
    u--; v--;
    kraw[u].push_back(make_pair(v,b));
    kraw[v].push_back(make_pair(u,b));
  }

  /* Minimalna i maksymalna liczba zwalnianych policjantow. */
  long long wynik_min = 0, wynik_max = 0;

  for (int i = 0; i < n; ++i) if (!odwiedzony[i]) {
    skladowa.clear();
    f[i] = Flin(1, 0);
    dfs(i);
    if (!oblicz_skladowa(wynik_min, wynik_max)) {
      puts("NIE");
      return 0;
    }
  }
  printf("%lld %lld\n", wynik_min, wynik_max);
  return 0;
}
