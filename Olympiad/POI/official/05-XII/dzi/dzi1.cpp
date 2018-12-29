/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DZI (Dziuple)                                  *
 *   Plik:                dzi1.cpp                                       *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        Z³o¿ono¶æ obliczeniowa jak i pamiêciowa jest   *
 *                        liniowa. Przeszukiwanie grafu (DFS) jest       *
 *                        zrealizowane na wlasnym stosie (z powodu       *
 *                        potencjalnie du¿ej g³êboko¶ci rekursji).       *
 *                        Wykorzystywane sa struktury danych z STL.      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 1000000;       //maksymalna liczba wierzcholkow

vector < int >kraw[MAXN];       //graf reprezentowany przez "listy sasiedztwa"
int deg[MAXN], parent[MAXN];    /*stopnie oraz ojcowie wierzcho³ków
                                   w drzewie przeszukiwania w g³±b */
stack < int >stos;
long long k, r;
int n, m;                       //liczba wierzcholkow oraz liczba krawedzi

//wczytywanie danych
void czytaj()
{
  scanf("%d %d %lld", &n, &m, &k);
  if (m < n) {
    for (int i = 0; i < m; ++i) {
      int a, b;
      scanf("%d %d", &a, &b);
      //dodajemy krawedz do grafu
      kraw[--a].push_back(--b);
      kraw[b].push_back(a);
      deg[a]++;
      deg[b]++;
    }
  }
}

/*przeszukiwanie grafu w g³±b, zrealizowane na w³±snym stosie*/
void dfs(int x)
{
  stos.push(x);                 //wierzcho³ek x jest jedynym elementem stosu
  parent[x] = x;
  int wezly = 0;                //liczba wierzcho³ków tej spójnej sk³adowej o stopniu >=2
  while (!stos.empty()) {
    int v = stos.top();
    stos.pop();                 //zdejmujemy wierzcho³ek ze stosu
    wezly += (deg[v] >= 2);
    int liscie = 0, j = 0;

    for (int i = 0; i < (int) kraw[v].size(); ++i) {
      int u = kraw[v][i];
      if (parent[u] == -1) {
        //zaznaczamy wierzcho³ek jako odwiedzony i wrzucamy na stos
        parent[u] = v;
        stos.push(u);
      }
      else if (u != parent[v])
        r = 0;                  //skladowa nie jest drzewem

      if (deg[u] == 1)
        liscie++;
      else
        j++;
    }

    if (j > 2)
      r = 0;                    //graf nie jest pladzielny

    for (int i = 2; i <= liscie; ++i) //permutowanie wierzcho³ków stopnia 1
      r = (r * i) % k;
  }
  if (wezly >= 2)               //symetria wzgledem prostej poziomej
    r = (r * 2) % k;
}

//g³ówna procedura progamu, procedura ta zlicza liczbê rozstawieñ ptaszków
void licz()
{
  for (int i = 0; i < n; ++i)
    parent[i] = -1;             //wierzcho³ki nie s± odwiedzone
  int skladowe = 0;             //liczba spójnych sk³adowych
  int izolowane = 0;            //liczba wierzcho³ków izolowanych
  r = (m < n);
  for (int i = 0; i < n; ++i)
    if (parent[i] == -1)
      if (deg[i] > 0) {
        r = (r * (2 * (++skladowe))) % k;
        dfs(i);
      }
      else
        izolowane++;

  //trzeba uwzglêdniæ dowolne rozstawienie wierzcho³ków izolowanych
  for (int i = n + 1; i >= n + 2 - izolowane; --i)
    r = (r * i) % k;
  printf("%lld\n", r);
}

int main()
{
  czytaj();
  licz();
  return 0;
}
