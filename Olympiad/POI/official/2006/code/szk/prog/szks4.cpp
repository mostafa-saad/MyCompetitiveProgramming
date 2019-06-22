/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZK (Szko³y)                                   *
 *   Plik:                szks4.cpp                                      *
 *   Autor:               Pawe³ Parys                                    *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,l,h) for (int a=(l); a<=(h); ++a)

using namespace std;

#define SIZE 200    // maximal number of schools
#define INF 1000000000

int N, cur[SIZE], low[SIZE], high[SIZE], score[SIZE];
bool used[SIZE];

int best = INF;

inline int cost(int s, int p)
{
  return abs(cur[s]-p)*score[s];
}


void backtrack(int nr, int res)
{
  if (res>=best) return;
  if (nr==N)
  {
    best = res;
    return;
  }
  FOR (p, low[nr], high[nr])
  {
    if (used[p]) continue;
    used[p] = true;
    backtrack(nr+1, res+cost(nr, p));
    used[p] = false;
  }
}

int main()
{
  scanf("%d", &N);
  REP(a,N)
  {
    scanf("%d%d%d%d", cur+a, low+a, high+a, score+a);
    --cur[a]; --low[a]; --high[a];
    used[a] = false;
  }
  backtrack(0, 0);
  if (best==INF)
    printf("NIE\n");
  else
    printf("%d\n", best);
}
