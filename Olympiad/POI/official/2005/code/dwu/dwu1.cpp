/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DWU (Dwuszereg)                                *
 *   Plik:                dwu1.cpp                                       *
 *   Autor:               Marcin Stefaniak                               *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        (bez u¿ycia strumieni)                         *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

#define FOR(i,n) for (int i = 0; i < int(n); ++i)

const int MAX_N = 50000;
const int MAX_X = 100000;

vector < pair < int, int > > soldiers;  // dwuszereg - wzrost ¿o³nierzy
vector < bool > visited;        // visited[i] == pozycja i-ta zosta³a odwiedzona
vector < int >first;            // first[x] == pozycja pierwszego ¿o³nierza o numerze x
vector < int >second;           // second[x] == pozycja drugiego ¿o³nierza o numerze x

int main()
{
  int n;
  scanf("%d", &n);              // ZMIANA
  soldiers.resize(n);
  visited.resize(n, false);
  first.resize(MAX_X + 1, -1);
  second.resize(MAX_X + 1, -1);

  FOR(i, n) {
    int x;
    scanf("%d", &x);
    soldiers[i].first = x;
    if (first[x] == -1)
      first[x] = i;
    else
      second[x] = i;
  }

  FOR(i, n) {
    int x;
    cin >> x;
    soldiers[i].second = x;
    if (first[x] == -1)
      first[x] = i;
    else
      second[x] = i;
  }

  int sum = 0;
  FOR(i, n)
      if (!visited[i]) {
    visited[i] = true;
    // specjalny przypadek - dwóch ¿o³nierzy tego samego wzrostu w jednej kolumnie
    if (soldiers[i].first == soldiers[i].second)
      continue;

    int count = 0;              // liczba potrzebnych zamian, gdy nie zamieniamy pierwszej pary
    int count_rev = 1;          // liczba potrzebnych zamian, gdy zamieniamy pierwsz± parê

    // odwiedzamy ³añcuch pozycji zale¿nych od pierwszego ¿o³nierza,
    // mamy dwa przypadki: albo wrócimy do pozycji i-tej, albo nie
    int j = i;
    int x = soldiers[i].first;
    int k;
    while (true) {
      k = first[x];
      if (k == j)
        k = second[x];
      if (k == -1)
        break;                  // ³añcuch siê koñczy
      if (k == i)
        break;                  // ³añcuch zamyka siê w cykl

      if (x == soldiers[k].second) {
        ++count_rev;
        x = soldiers[k].first;
      }
      else {
        ++count;
        x = soldiers[k].second;
      }
      visited[k] = true;
      j = k;
    }

    if (k == -1) {              // ³añcuch nie zamkn±³ siê w cykl
      // odwiedzamy ³añcuch pozycji zale¿nych od drugiego ¿o³nierza
      int j = i;
      int x = soldiers[i].second;

      while (true) {
        k = first[x];
        if (k == j)
          k = second[x];
        if (k == -1)
          break;

        if (soldiers[k].first == x) {
          ++count_rev;
          x = soldiers[k].second;
        }
        else {
          ++count;
          x = soldiers[k].first;
        }
        visited[k] = true;
        j = k;
      }
    }
    sum += min(count, count_rev);
  }
  cout << sum << endl;
}
