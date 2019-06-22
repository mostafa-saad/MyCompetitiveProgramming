/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MET (Metro)                                    *
 *   Plik:                mets1.cpp                                      *
 *   Autor:               Szymon Wasik                                   *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Program wyznaczajacy najdluzsza sciezke        *
 *                        w czasie kwadratowym.                          *
 *                        Zlozonosc obliczeniowa: O(n^2)                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>

#define MAXN 1000000

using namespace std;

typedef pair<int, int> pii;

int n, l;
int mlen = 0, mw = 0, res;
vector<int> *g;
bool used[MAXN];
bool line[MAXN];
int prev[MAXN];
int deg[MAXN];

int bfs(int w)
{
  queue<pii> q;
  int last = 0;
  memset(used, false, sizeof(used));
  used[w] = true;
  q.push(make_pair(w, 0));
  while (!q.empty())
  {
    pii p = q.front();
    q.pop();
    last = p.second;
    for (vector<int>::iterator i = g[p.first].begin(); i != g[p.first].end(); ++i)
      if (!used[*i])
      {
        used[*i] = true;
        q.push(make_pair(*i, p.second + 1));
      }
  }
  return last;
}

void getpath(int w)
{
  queue<int> q;
  int last;
  memset(used, false, sizeof(used));
  used[w] = true;
  q.push(w);
  prev[w] = -1;
  while (!q.empty())
  {
    w = q.front();
    q.pop();
    last = w;
    for (vector<int>::iterator i = g[w].begin(); i != g[w].end(); ++i)
      if (!used[*i])
      {
        prev[*i] = w;
        used[*i] = true;
        q.push(*i);
      }
  }
  while (last != -1)
  {
    line[last] = true;
    last = prev[last];
  }
}

int getlen(int w)
{
  int res = 0;
  while (!line[w])
    res++, w = prev[w];
  return res;
}

void addpath(int w)
{
  while (!line[w])
    line[w] = true, w = prev[w];
}

int main()
{
  scanf("%d %d", &n, &l);
  if (l == 0) 
  {
    printf("0\n");
    return 0;
  }
  g = new vector<int>[n];
  memset(deg, 0, sizeof(deg));
  for (int i = 0; i < n-1; i++)
  {
    int a, b;
    scanf("%d %d", &a, &b);
    a--; b--;
    g[a].push_back(b);
    g[b].push_back(a);
    deg[a]++;
    deg[b]++;
  }
  for (int i = 0; i < n-1; i++)
    if (mlen < (res = bfs(i))) mlen = res, mw = i;  
  memset(line, false, sizeof(line));
  getpath(mw);
  for (int i = 0; i < l*2-2; i++)
  {
    mlen = 0, mw = 0;
    for (int i = 0; i < n; i++)
      if (deg[i] == 1 && (res = getlen(i)) > mlen) mlen = res, mw = i;
    addpath(mw);
  }   
  res = 0;
  for (int i = 0; i < n; i++)    
    if (line[i]) res++;
  printf("%d\n", res);
  return 0;
}
