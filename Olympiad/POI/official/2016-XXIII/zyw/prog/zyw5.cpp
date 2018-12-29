/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Zywoplot                                           *
 *   Autor programu:       Karol Pokorski                                     *
 *   Opis:                 Rozwiazanie alternatywne                           *
 *****************************************************************************/


#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1005;

pair<int,int> p[MAXN][MAXN];
char vertical[MAXN][MAXN], horizontal[MAXN][MAXN];
char vertical_output[MAXN][MAXN], horizontal_output[MAXN][MAXN];

pair<int,int> FindSet(const pair<int,int>& x) {
  if (p[x.first][x.second] != x)
    p[x.first][x.second] = FindSet(p[x.first][x.second]);
  return p[x.first][x.second];
}

void Union(const pair<int,int>& a, const pair<int,int>& b) {
  pair<int,int> a_repr = FindSet(a);
  pair<int,int> b_repr = FindSet(b);
  p[a_repr.first][a_repr.second] = b_repr;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) scanf("%s", vertical[i]);
  for (int i = 0; i < n-1; i++) scanf("%s", horizontal[i]);

  int edges_used = n*(m-1) + (n-1)*m, edges_val = 0;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m-1; j++) {
      edges_val += (vertical[i][j] == 'C') ? 1 : 0;
      vertical_output[i][j] = 'Z';
    }
  for (int i = 0; i < n-1; i++)
    for (int j = 0; j < m; j++) {
      edges_val += (horizontal[i][j] == 'C') ? 1 : 0;
      horizontal_output[i][j] = 'Z';
    }

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      p[i][j] = make_pair(i, j);

  for (int val = 0; val <= 1; val++) {
    char needed = (val == 1) ? 'C' : 'T';
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m-1; j++)
        if (vertical[i][j] == needed) {
          const pair<int,int> a = make_pair(i, j);
          const pair<int,int> b = make_pair(i, j+1);
          if (FindSet(a) != FindSet(b)) {
            Union(a, b);
            edges_used--;
            edges_val -= val;
            vertical_output[i][j] = '.';
          }
        }
    for (int i = 0; i < n-1; i++)
      for (int j = 0; j < m; j++)
        if (horizontal[i][j] == needed) {
          const pair<int,int> a = make_pair(i, j);
          const pair<int,int> b = make_pair(i+1, j);
          if (FindSet(a) != FindSet(b)) {
            Union(a, b);
            edges_used--;
            edges_val -= val;
            horizontal_output[i][j] = '.';
          }
        }
  }

  printf("%d %d\n", edges_used, edges_val);
  for (int i = 0; i < n; i++)
    printf("%s\n", vertical_output[i]);
  for (int i = 0; i < n-1; i++)
    printf("%s\n", horizontal_output[i]);

  return 0;
}
