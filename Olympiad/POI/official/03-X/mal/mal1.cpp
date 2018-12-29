/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Ma³pki                                         *
 *   Plik:                mal1.cpp                                       *
 *   Autor:               Krzysztof Onak                                 *
 *************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

// ograniczenia
const int MAXN = 200000;
const int MAXM = 2 * MAXN;

// oznacza, ¿e ma³pka nic nie trzyma w danej rêce
const int PUSZCZONA = -1;

// ma³pka na drzewie, nigdy nie spad³a
const int NIGDY = -1;
// ma³pka le¿y na ziemi
const int ZIEMIA = -2;

int n, m;
int lapki[MAXN][2];  // opisuje, kogo trzymaj± ³apki ma³pki
int uchwyt[MAXM][2]; // opisuje kto kogo pu¶ci³ w danej chwili czasu

void wczytaj()
{
  cin >> n >> m;
  // wczytujemy stan ³apek ma³pek
  for(int i = 0; i < n; ++i) {
    int l, p;
    cin >> l >> p;
    lapki[i][0] = l == PUSZCZONA ? l : l - 1;
    lapki[i][1] = p == PUSZCZONA ? p : p - 1;
  }
  // wczytujemy kto kogo pu¶ci³ i uaktualniamy odpowiednio stan ³apek
  for(int i = 0; i < m; ++i) {
    int malpa, lapka;
    cin >> malpa >> lapka;
    uchwyt[i][0] = lapki[--malpa][--lapka];
    uchwyt[i][1] = malpa;
    lapki[malpa][lapka] = PUSZCZONA;
  }
}

vector<int> krawedzie[MAXN];  // krawedzie grafu ma³pek
int czas[MAXN];  // czas, w którym spad³a dana ma³pka

// startujemy od ma³pki v i nadajemy wszystkim ma³pkom, z którymi
// jest ona zwi±zana i które le¿± na ziemi, czas odwiedzin t
void dfs(int v, int t)
{
  if (czas[v] != ZIEMIA) return;
  czas[v] = t;
  int sasiadow = krawedzie[v].size();
  for(int i = 0; i < sasiadow; ++i)
    dfs(krawedzie[v][i], t);
}

// przygotowujemy krawêdzie grafu ma³pek
// i inicjalizujemy czas upadku
void przygotuj()
{
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < 2; ++j)
      if (lapki[i][j] != PUSZCZONA) {
        krawedzie[lapki[i][j]].push_back(i);
	krawedzie[i].push_back(lapki[i][j]);
      }
  for(int i = 0; i < n; ++i)
    czas[i] = ZIEMIA;
}

// obliczamy czasy upadku
void przetworz()
{
  // ma³pki, które w ogóle nie spad³y
  dfs(0, NIGDY);
  // dodajemy kolejne uchwyty
  for(int i = m - 1; i >= 0; --i) {
    int v = uchwyt[i][0], w = uchwyt[i][1];
    // czy¿by nowe ma³pki po³±czy³y siê z drzewem?
    if (czas[v] == ZIEMIA && czas[w] != ZIEMIA) {
      dfs(v, i);
    } else if (czas[w] == ZIEMIA && czas[v] != ZIEMIA) {
      dfs(w, i);
    }
    // nowe krawêdzie w grafie
    krawedzie[v].push_back(w);
    krawedzie[w].push_back(v);
  }
}

// wypisujemy wynik
void wypisz()
{
  for(int i = 0; i < n; ++i)
    cout << czas[i] << '\n';
}

int main()
{
  wczytaj();
  przygotuj();
  przetworz();
  wypisz();
}
