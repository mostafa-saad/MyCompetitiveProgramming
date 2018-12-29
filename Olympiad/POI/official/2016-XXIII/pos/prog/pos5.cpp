/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Poslaniec                                          *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 107;
const int MAXD = 57;
int mat[MAXD][MAXN][MAXN];
int res[MAXD][MAXN][MAXN];
int dp[MAXD][2];

struct query{
  int a, b, d;
};

vector <query> Q;

int main()
{
  int n, m, z;
  cin >> n >> m >> z;
  for(int i=0; i<n; i++)
    mat[0][i][i] = 1;
  while(m--)
  {
    int a, b;
    cin >> a >> b;
    a--; b--;
    mat[1][a][b] = 1;
  }
  int q;
  cin >> q;
  int maxd = 0;
  while(q--)
  {
    query tmp;
    cin >> tmp.a >> tmp.b >> tmp.d;
    tmp.a--; tmp.b--;
    maxd = max(maxd, tmp.d);
    Q.push_back(tmp);
  }
  for(int d=2; d<=maxd; d++)
  {
    for(int i=0; i<n; i++)
      for(int j=0; j<n; j++)
        for(int k=0; k<n; k++)
        {
          mat[d][i][j] += (1LL * mat[d-1][i][k] * mat[1][k][j])%z;
          if(mat[d][i][j] > z)
            mat[d][i][j] %= z;
        }
  }
  // magic :]
  dp[0][0] = -1;
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
    {
      for(int d=1; d<=maxd; d++)
      {
        dp[d][0] = 0;
        dp[d][1] = 0;
        for(int e=0; e<d; e++)
        {
          dp[d][0] -= (1LL * dp[e][0] * mat[d-e][i][i]) % z;
          dp[d][0] = (dp[d][0] + z) % z;
          dp[d][0] -= (1LL * dp[e][1] * mat[d-e][j][i]) % z;
          dp[d][0] = (dp[d][0] + z) % z;

          dp[d][1] -= (1LL * dp[e][1] * mat[d-e][j][j]) % z;
          dp[d][1] = (dp[d][1] + z) % z;
					dp[d][1] -= (1LL * dp[e][0] * mat[d-e][i][j]) % z;
          dp[d][1] = (dp[d][1] + z) % z;
        }
      }
      for(int d=1; d<=maxd; d++)
        res[d][i][j] = dp[d][1];
    }
  for(auto ele : Q)
    cout << res[ele.d][ele.a][ele.b] << "\n";
}
