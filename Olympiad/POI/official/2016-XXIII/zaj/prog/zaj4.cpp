/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Zajakniecia                                        *
 *   Autor programu:       Bartek Kostka                                      *
 *   Zlozonosc czasowa:    O(n^2)                                             *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 weryfikacyjne z poprawiaczem                       *
 *                         i zamienionymi wymiarami                           *
 *****************************************************************************/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 15007;
int n, m;
int a[MAXN], b[MAXN], preva[MAXN], prevb[MAXN], remember[MAXN];
int lcs[2][MAXN];

int main()
{
  ios_base::sync_with_stdio(0);
  cin >> n >> m;
  map <int, pair<int, int> > wys;
  for(int i=1; i<=n; i++)
  {
    cin >> a[i];
    wys[a[i]].first += 1;
  }
  for(int i=1; i<=m; i++)
  {
    cin >> b[i];
    wys[b[i]].second += 1;
  }
  int wskn = 0, wskm = 0;
  for(int i=1; i<=n; i++)
    if(min(wys[a[i]].first, wys[a[i]].second) > 1)
      a[++wskn] = a[i];
  for(int i=1; i<=m; i++)
    if(min(wys[b[i]].first, wys[b[i]].second) > 1)
      b[++wskm] = b[i];
  n = wskn;
  m = wskm;
  swap(a,b);
  swap(n,m);
  map <int, int> last;
  for(int i=1; i<=n; i++)
  {
    preva[i] = last[a[i]];
    last[a[i]] = i;
  }
  last.clear();
  for(int i=1; i<=m; i++)
  {
    prevb[i] = last[b[i]];
    last[b[i]] = i;
  }
  for(int i=1; i<=n; i++)
  {
    for(int j=1; j<=m; j++)
    {
      lcs[i%2][j] = max(lcs[(i-1)%2][j], lcs[i%2][j-1]);
      if(a[i] == b[j])
        if(preva[i] and prevb[j])
          lcs[i%2][j] = max(lcs[i%2][j], remember[prevb[j]] + 1);
    }
    for(int j=1; j<=m; j++)
      if(a[i] == b[j])
        remember[j] = lcs[(i-1)%2][j-1];
  }
  cout << 2*lcs[n%2][m] << "\n";
}
