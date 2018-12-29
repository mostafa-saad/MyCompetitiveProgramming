/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Tasowanie                                      *
 *   Plik:                tas.cpp                                        *
 *   Autor:               Krzysztof Onak                                 *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <cstdlib>
using namespace std;

const int MAXN = 1000000;

// liczby z pliku wej¶ciowego
int n, l;
int b[MAXN];

bool odwiedzone[MAXN];       // tablica odwiedzeñ 
vector<int> cykle[MAXN + 1]; // tablica wektorów pocz±tków cykli

// wyszukiwanie i zliczanie cykli
void zliczaj_cykle() {
  for(int i = 0; i < n; ++i) odwiedzone[i] = false;
  for(int i = 0; i < n; ++i)
    if (!odwiedzone[i]) {
      int k = i;
      int dl = 0;
      while (!odwiedzone[k]) {
        ++dl;
	odwiedzone[k] = true;
	k = b[k];
      }
      cykle[dl].push_back(i);
    }
}

// najmniejszy wspólny dzielnik
int nwd(int a, int b) {
  return (b == 0) ? a : nwd(b, a % b);
}

// oblicza najmniejszy upierwszacz a wzglêdem b (definicja w opracowaniu)
int upierwszacz(int a, int b) {
  int dz = 1, k = 1;
  do {
    a /= k;
    k = nwd(a, b);
    dz *= k;
  } while (k != 1);
  return dz;
}

// podnosi cykl do zadanej potêgi
void cykl_potega(int start, int pot) {
  vector<int> cykl;
  int teraz = start;
  do {
    cykl.push_back(teraz);
    teraz = b[teraz];
  } while(teraz != start);
  int dl = cykl.size();
  for(int i = 0; i < dl; ++i)
    b[cykl[i]] = cykl[(i + pot) % dl];
}

// przeplata u cykli dlugosci dl o pocz±tkach cykle_dl[start..start+u-1]
void nawlecz(vector<int> &cykle_dl, int start, int u, int dl) {
  vector<int> w;
  for(int i = 0; i < dl; ++i)
    for(int j = start; j < start + u; ++j) {
      w.push_back(cykle_dl[j]);
      cykle_dl[j] = b[cykle_dl[j]];
    }
  int ile = w.size();;
  for(int i = 0; i < ile; ++i)
    b[w[i]] = w[(i + 1) % ile];
}

// oblicza odwrotno¶ci
void odwroc() {
  for(int i = 1; i <= n; ++i) if (!cykle[i].empty()) {
    int u = upierwszacz(l, i);
    int lu = l / u;
    int odwr_lu = 0;
    while ((long long)odwr_lu * lu % i != 1 % i) ++odwr_lu;
    int ile = cykle[i].size();
    if (ile % u != 0) {
      // to nie powinno siê zdarzyæ dla poprawnych danych
      fprintf(stderr, "Zadanie nie ma rozwi±zania\n");
      exit(1);
    }
    for(int j = 0; j < ile; ++j) cykl_potega(cykle[i][j], odwr_lu);
    for(int j = 0; j < ile; j += u) nawlecz(cykle[i], j, u, i);
  }
}

int main() {
  scanf("%d%d", &n, &l);
  for(int i = 0; i < n; ++i) {
    scanf("%d", &b[i]);
    --b[i];
  }
  zliczaj_cykle();
  odwroc();
  for(int i = 0; i < n; ++i)
    printf("%d\n", b[i] + 1);
}
