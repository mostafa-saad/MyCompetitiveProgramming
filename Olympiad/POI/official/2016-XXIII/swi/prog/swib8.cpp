/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Swiateczny lancuch                                 *
 *   Autor programu:       Krzysztof Kiljan                                   *
 *   Zlozonosc czasowa:    O((n + m) * LEN * FU(n)))                          *
 *   Opis:                 Rozwiazanie bledne                                 *
 *                         Z kazdego przedzialu bierzemy 2000 pierwszych      *
 *                         i 2000 ostatnich zalozen                           *
 *****************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN = 500013;
const int LEN = 2000;

int n, m, a, b, l;


struct FAU{
int w[MAXN];
int p[MAXN];

FAU() {
  for(int i = 0; i < MAXN; i++)
    w[i] = p[i] = -1;
}

void Union(int x, int y) {
  if ((x = Find(x)) == (y = Find(y))) return;

  if (w[x] > w[y]) p[y] = x;
  else p[x] = y;

  if(w[x]== w[y]) w[y]++;
}

int Find(int a) {
  return (p[a] < 0) ? a : p[a] = Find(p[a]);
}
};

FAU roots, f;


void addRange(int a, int b, int len)
{
  int ppocz = a;
  int pkoniec = a + len - 1;

  for(int j = 0; j < min(len, LEN); ppocz++, j++)
  {
    f.Union(ppocz, b + j);
  }

  for(int j = 0; j < min(len, LEN) && pkoniec >= ppocz; pkoniec--, j++)
  {
    f.Union(pkoniec, b + len - 1 - j);
  }
}

void readInput()
{
  scanf("%d%d", &n, &m);

  for(int i = 0; i < m; i++)
  {
    scanf("%d %d %d", &a, &b, &l);
    a--;
    b--;
    addRange(a, b, l);
    f.Union(a, b);
  }

}


void solve()
{

  set <int> s;
  for(int i = 0; i < n; i++)
    s.insert(f.Find(i));

  printf("%d\n", s.size());
}

int main()
{
    readInput();
    solve();
    return 0;
}
