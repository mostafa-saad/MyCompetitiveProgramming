/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Prefiksufiks                                     *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define INFTY 100000000

// Promienie palindromow parzystych w czasie O(n).
// R[i] - promien palindromu o srodku miedzy i a (i+1) litera.
vector<int> Manacher(string s) {
  s = '$' + s + '#';
  vector<int> R;
  R.push_back(0);
  int i = 1, j = 0;
  while (i < (int)s.size()) {
    while (s[i - j] == s[i + j + 1]) ++j;
    R.push_back(j);
    int k = 1;
    while (R[i - k] != R[i] - k && k <= j) {
      R.push_back(min(R[i - k], R[i] - k));
      ++k;
    }
    j = max(j - k, 0);
    i += k;
  }
  R.erase(R.begin()); R.pop_back();
  return R;
}

#define MAX_N 1000010

int n;
char napis[MAX_N];
string przeplot; 
vector<int> manacher;

// najblizszy[i] = najblizsza kolejna pozycja, na ktorej konczy sie palindrom
// bedacy prefiksem.
int najblizszy[MAX_N];

void oblicz_najblizszy() {
  for (int i = 0; i <= n; ++i)
    najblizszy[i] = INFTY;
  for (int i = 0; i < n; ++i)
    if (manacher[i] == i + 1)
      najblizszy[2 * i + 1] = 2 * i + 1;
  for (int i = n - 1; i >= 0; --i)
    najblizszy[i] = min(najblizszy[i], najblizszy[i + 1]);
}

int main() {
  scanf("%d%s", &n, napis);

  for (int i = 0; i < n / 2; ++i) {
    przeplot += napis[i];
    przeplot += napis[n - 1 - i];
  }
  n = przeplot.size();

  manacher = Manacher(przeplot);

  oblicz_najblizszy();

  // Oblicza wynik jako sklejenie dwoch palindromow w przeplocie;
  // potencjalnie jeden z palindromow moze byc pusty.
  int wynik = 0;
  for (int i = 0; i < n; ++i) {
    int pierwszy_palindrom = najblizszy[i - manacher[i]];
    if (pierwszy_palindrom <= i)
      wynik = max(wynik, 2 * i - pierwszy_palindrom);
  }
  printf("%d\n", (wynik + 1) / 2);
  return 0;
}
