/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DWU (Dwuszereg)                                *
 *   Plik:                dwub2.cpp                                      *
 *   Autor:               Arkadiusz Paterek                              *
 *   Opis:                Rozwiazanie niepoprawne                        *
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
vector < int > first;            // first[x] == pozycja pierwszego ¿o³nierza o numerze x
vector < int > second;           // second[x] == pozycja drugiego ¿o³nierza o numerze x

bool wrong_pos(int i)
{
  int x = soldiers[i].first;
  int y = soldiers[i].second;
  if (x == y)
    return false;

  int j;

  if (first[x] == i)
    j = second[x];
  else
    j = first[x];

  if (j != -1 && soldiers[j].first == x)
    return true;

  if (first[y] == i)
    j = second[y];
  else
    j = first[y];

  if (j != -1 && soldiers[j].second == y)
    return true;

  return false;
}

int main()
{
  int n;
  cin >> n;
  soldiers.resize(n);
  first.resize(MAX_X + 1, -1);
  second.resize(MAX_X + 1, -1);

  FOR(i, n) {
    int x;
    cin >> x;
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

  int cnt = 0;
  FOR(i, n)
      if (wrong_pos(i))
    ++cnt;
  cout << 2 * cnt / 3 << endl;

  return 0;
}
