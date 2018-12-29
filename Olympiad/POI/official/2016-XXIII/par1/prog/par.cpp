/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Park wodny                                         *
 *   Autor programu:       Bartosz Kostka                                     *
 *   Zlozonosc czasowa:    O(n^2)                                             *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/


#include "bits/stdc++.h"

#define x first
#define y second

using namespace std;

const int MAXN = 2007;
char tab[MAXN][MAXN];
int odw[MAXN][MAXN];

static int n;
int da[] = {0,0,-1,1}, db[] = {1,-1,0,0};
vector <int> V = {0}, W;

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
vector <pair <int, int>> E = {{0,0}}, F = {{0,0}};
int nr;

int make()
{
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      if(odw[i][j] == 0 and tab[i][j] == 'B')
      {
        V.push_back(dfs(i,j,++nr));
        E.emplace_back(i,j);
        F.emplace_back(i,j);
      }
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

void consider(vector <pair <int, int> > X)
{
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

int main()
{
  ios_base::sync_with_stdio(0);
  cin >> n;
  for(int i=0; i<n; i++)
    cin >> tab[i];
  vector <pair <pair <int, int>, pair <int, int>>> A;
  for(int i=0; i<n-1; i++)
    for(int j=0; j<n; j++)
      if(tab[i][j] == 'A' and tab[i+1][j] == 'A')
        A.push_back({{i,j},{i+1,j}});
  for(int i=0; i<n; i++)
    for(int j=0; j<n-1; j++)
      if(tab[i][j] == 'A' and tab[i][j+1] == 'A')
        A.push_back({{i,j},{i,j+1}});
  res = make();
  W = V;
  for(int i=0; i<(int)A.size(); i++)
  {
    vector <pair <int, int>> X = {A[i].first, A[i].second};
    consider(X);
  }
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      if(int c = odw[i][j])
      {
        E[c].x = min(E[c].x, i);
        F[c].x = max(F[c].x, i);
        E[c].y = min(E[c].y, j);
        F[c].y = max(F[c].y, j);
      }
  for(int i=1; i<=nr; i++)
  {
    set <pair <int, int> > S;
    S.insert(make_pair(E[i].x-1, E[i].y));
    S.insert(make_pair(E[i].x, E[i].y-1));
    S.insert(make_pair(E[i].x-1, F[i].y));
    S.insert(make_pair(E[i].x, F[i].y+1));
    S.insert(make_pair(F[i].x+1, E[i].y));
    S.insert(make_pair(F[i].x, E[i].y-1));
    S.insert(make_pair(F[i].x+1, F[i].y));
    S.insert(make_pair(F[i].x, F[i].y+1));
    vector <pair <int, pair <int, int>>> T;
    set <int> TM;
    TM.insert(0);
    for(int k=E[i].x+1; k<=F[i].x-1; k++)
      if(onboard(k,E[i].y-2) and TM.find(odw[k][E[i].y-2]) == TM.end())
      {
        T.push_back({V[odw[k][E[i].y-2]], {k,E[i].y-1}});
        TM.insert(odw[k][E[i].y-2]);
      }
    for(int k=E[i].x+1; k<=F[i].x-1; k++)
      if(onboard(k,F[i].y+2) and TM.find(odw[k][F[i].y+2]) == TM.end())
      {
        T.push_back({V[odw[k][F[i].y+2]], {k,F[i].y+1}});
        TM.insert(odw[k][F[i].y+2]);
      }
    for(int k=E[i].y+1; k<=F[i].y-1; k++)
      if(onboard(F[i].x+2,k) and TM.find(odw[F[i].x+2][k]) == TM.end())
      {
        T.push_back({V[odw[F[i].x+2][k]], {F[i].x+1,k}});
        TM.insert(odw[F[i].x+2][k]);
      }
    for(int k=E[i].y+1; k<=F[i].y-1; k++)
      if(onboard(E[i].x-2, k) and TM.find(odw[E[i].x-2][k]) == TM.end())
      {
        T.push_back({V[odw[E[i].x-2][k]], {E[i].x-1,k}});
        TM.insert(odw[E[i].x-2][k]);
      }
    sort(T.begin(), T.end());
    reverse(T.begin(), T.end());
    for(int k=0; k<min(2,(int)T.size()); k++)
      S.insert(T[k].second);
    vector <pair <int, int>> VS;
    for(auto ele : S)
      if(onboard(ele.x, ele.y))
        VS.push_back(ele);
    for(int k=0; k<(int)VS.size(); k++)
      for(int l=k+1; l<(int)VS.size(); l++)
      {
        auto X = {VS[k], VS[l]};
        consider(X);
      }
  }
  cout << res << "\n";
}
