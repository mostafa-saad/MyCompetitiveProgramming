/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Park wodny                                         *
 *   Autor programu:       Bartosz Kostka                                     *
 *   Zlozonosc czasowa:    O(n^4)                                             *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 2007;
char tab[MAXN][MAXN];
int odw[MAXN][MAXN];

static int n;
int da[] = {0,0,-1,1}, db[] = {1,-1,0,0};
vector <int> V = {0};

bool onboard(int a, int b)
{
  return 0 <= min(a,b) and max(a,b) < n;
}

int dfs(int a, int b, int c)
{
  int cou = 1;
  odw[a][b] = c;
  for(int i=0; i<4; i++)
  {
    int na = a+da[i], nb = b+db[i];
    if(not(onboard(na,nb)))
      continue;
    if(odw[na][nb] == 0 and tab[na][nb] == 'B')
      cou += dfs(na,nb,c);
  }
  return cou;
}

vector <int> REP;

int make()
{
  int nr = 0;
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      if(odw[i][j] == 0 and tab[i][j] == 'B')
        V.push_back(dfs(i,j,++nr));
  int res = V[0];
  for(int i=1; i<=nr; i++)
    res = max(res, V[i]);
  for(int i=0; i<=nr; i++)
    REP.emplace_back(i);
  return res;
}

int find(int x)
{
  if(REP[x] == x)
    return x;
  return REP[x] = find(REP[x]);
}

set <int> CHANGED;

int res;

void unia(int a, int b, vector <int> &ILE)
{
  int fa = find(a), fb = find(b);
  if(fa == fb)
    return;
  CHANGED.insert(a);
  CHANGED.insert(b);
  REP[fb] = fa;
  ILE[fa] += ILE[fb];
  res = max(res, ILE[fa]);
  ILE[fb] = 0;
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin >> n;
  for(int i=0; i<n; i++)
    cin >> tab[i];
  vector <pair <int, int>> A;
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      if(tab[i][j] == 'A')
        A.emplace_back(i,j);
  res = make();
  auto W = V;
  for(int i=0; i<(int)A.size(); i++)
    for(int j=i+1; j<(int)A.size(); j++)
    {
      auto X = {A[i], A[j]};
      for(auto ele : X)
      {
        int a, b;
        tie(a,b) = ele;
        for(int i=0; i<4; i++)
        {
          int ma = a + da[i], mb = b + db[i];
          if(tab[ma][mb] == 'B')
          {
            CHANGED.insert(odw[ma][mb]);
            W[odw[ma][mb]]++;
            res = max(res, W[odw[ma][mb]]);
            odw[a][b] = odw[ma][mb];
            break;
          }
        }
      }
      for(auto ele : X)
      {
        int a, b;
        tie(a,b) = ele;
        for(int i=0; i<4; i++)
          for(int j=i+1; j<4; j++)
          {
            int ma = a + da[i], mb = b + db[i];
            int na = a + da[j], nb = b + db[j];
            if(onboard(ma,mb) and onboard(na,nb) and odw[ma][mb] and odw[na][nb])
              unia(odw[ma][mb], odw[na][nb], W);
        }
      }
      for(auto ele : X)
      {
        int a, b;
        tie(a,b) = ele;
        odw[a][b] = 0;
      }
      for(auto ele : CHANGED)
      {
        W[ele] = V[ele];
        REP[ele] = ele;
      }
      CHANGED.clear();
    }
  cout << res << "\n";
}
