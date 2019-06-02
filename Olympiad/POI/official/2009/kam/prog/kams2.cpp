/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kamyki (KAM)                                              *
 *   Plik:     kams2.java                                                *
 *   Autor:    Szymon Wrzyszcz                                           *
 *   Opis:     Rozwiazanie wykladnicze uzywajace programowania           *
 *             dynamicznego                                              *
 *                                                                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// sprawdza czy nie ma juz zadnych kamieni
int koniec(vector<int> &v) {
  for (int i=0; i<(int)v.size(); i++)
    if (v[i] > 0)
      return 0;
  return 1;
}


map<vector<int>, int> M;

// zwraca 1 gdy uklad v jest wygrywajacy, 0 wpp
int wygra(vector<int> &v) {
  if (koniec(v))
    return 0;

  if (M.find(v) != M.end())
    return M[v];

  M[v] = 0;

  for (int i=0; i<(int)v.size(); i++) {
    int k = (i==0)?(v[0]):(v[i]-v[i-1]);
    while (k >= 1) {
      v[i] -= k;
      if (!wygra(v)) {
	v[i] += k;
	M[v] = 1;
	return 1;
      }
      v[i] += k;
      k--;
    }
  }
  return 0;
}

int main() {
  int u, n;
  vector<int> v;
  scanf("%d", &u);
  while (u--) {
    scanf("%d", &n);
    v.resize(n);
    for (int i=0; i<n; i++)
      scanf("%d", &v[i]);
    puts(wygra(v)?"TAK":"NIE");
  }
  return 0;
}
