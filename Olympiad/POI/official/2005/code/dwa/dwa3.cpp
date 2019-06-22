/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DWA (Dwa przyjêcia)                            *
 *   Plik:                dwa3.pas                                       *
 *   Autor:               Krzysztof Onak                                 *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
using namespace std;

const unsigned MAXN = 200;

int n;
bool e[MAXN][MAXN];
bool solution[MAXN];
bool inGraph[MAXN];

void read()
{
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      e[i][j] = false;
    int d;
    scanf("%d", &d);
    for (int j = 0; j < d; ++j) {
      int v;
      scanf("%d", &v);
      e[i][v - 1] = true;
    }
  }
  for (int i = 0; i < n; ++i)
    inGraph[i] = true;
}

void write()
{
  int count = 0;
  for (int i = 0; i < n; ++i)
    if (solution[i])
      ++count;
  printf("%d\n", count);
  for (int i = 0; i < n; ++i)
    if (solution[i]) {
      printf("%d", i + 1);
      if (--count > 0)
        printf(" ");
    }
  printf("\n");
}

void solve()
{
  int k;
  int neighbors = 0;
  int who[MAXN];
  for (k = 0; k < n; ++k)
    if (inGraph[k]) {
      neighbors = 0;
      for (int j = 0; j < n; ++j)
        if (inGraph[j] && e[k][j])
          who[neighbors++] = j;
      if (neighbors % 2 == 1)
        break;
    }
  if (k == n)
    return;
  inGraph[k] = false;
  for (int i = 0; i < neighbors; ++i)
    for (int j = 0; j < neighbors; ++j)
      if (i != j)
        e[who[i]][who[j]] = !e[who[i]][who[j]];
  solve();
  int party = 0;
  for (int i = 0; i < neighbors; ++i)
    if (solution[who[i]])
      ++party;
  solution[k] = party % 2 == 0;
}

int main()
{
  read();
  for (int i = 0; i < n; ++i)
    solution[i] = false;
  solve();
  write();
}
