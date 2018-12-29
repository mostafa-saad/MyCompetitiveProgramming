/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Swiateczny lancuch                                 *
 *   Autor programu:       Krzysztof Kiljan                                   *
 *   Zlozonosc czasowa:    O(n * sqrt n * FU(n)))                             *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                         Dzielimy rzadania na dlugosci O(sqrt(n)),          *
 *                         laczymy je odpowiednio za pomoca Find-Union        *
 *****************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN = 500013;
const int LEN = 1000;

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
vector<int> v[MAXN];


void addRange(int a, int b, int len)
{
  int ppocz = a;
  int pkoniec = a + len - 1;
  int oIle = 0;

  for(int j = 0; ppocz % LEN != 0 && j < len; ppocz++, j++, oIle++)
  {
    f.Union(a + j, b + j);
  }

  for(int j = 0; pkoniec % LEN != LEN - 1 && j < len; pkoniec--, j++)
  {
    f.Union(pkoniec, b + len - 1 - j);
  }

  while (ppocz < pkoniec)
  {
    v[b + oIle].push_back(ppocz / LEN);
    if(v[b+oIle].size() > 1)
    {
      roots.Union(v[b+oIle][0], v[b+oIle][1]);
      v[b+oIle].pop_back();
    }

    oIle += LEN;
    ppocz += LEN;
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
    f.Union(a,b);
  }

}

void dealWithRoots()
{
  for(int i = 0; i < n; i++)
    if(v[i].size() > 0)
    {
      int nr = v[i].back() * LEN;
      for(int j = 0; j < LEN; j++)
      {
        f.Union(nr + j, i + j);
      }
      v[i].clear();
    }
}

void dealWithRootFU()
{
  for(int i = 0; i < n / LEN; i++)
  {
    int nr = roots.Find(i);
    if(nr != i)
    {
      for(int j = 0; j < LEN; j++)
      {
        f.Union(nr * LEN + j, i * LEN + j);
      }
    }
  }
}

void solve()
{
  dealWithRoots();
  dealWithRootFU();

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
