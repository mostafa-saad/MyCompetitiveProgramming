/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Poslaniec                                          *
 *   Autor:                Wojtek Nadara                                      *
 *   Zlozonosc czasowa:    O(n^3 * d + n^2*d^2 + q)                           *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <iostream>
#define D 52
#define M mod
#define N 154
#define uint long long int
using namespace std;
uint m[N][N][D+2];
uint dp[D][2];
uint que [500007][3];
uint res[N][N][D];
int main()
{
	ios_base::sync_with_stdio(false);

    int n, kr;//, d;
    uint mod;
    cin>>n>>kr>>mod;
    for(int i=1; i<=kr; i++)
    {
			    int a, b;
        cin>>a>>b;
        m[a][b][1]=1;
        // m[b][a][1]=1;
    }
    for(int i=1; i<=n; i++)
    {
        m[i][i][0]=1;
    }
    int q;
    cin>>q;
    for(int i=0;i<q;i++)
        cin >>que[i][0] >> que[i][1] >> que[i][2];
    int mxd = -1;
    for(int i=0;i<q;i++)
        if(que[i][2] > mxd)
            mxd = que[i][2];

    for(int t=2; t<=mxd; t++)
    {
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                for(int k=1; k<=n; k++)
                {
                    m[i][j][t]+=m[i][k][t-1]*m[k][j][1];
                    m[i][j][t]%=M;
                }
            }
        }
    }
    for(int a=1; a<=n; a++)
    {
		for(int b = 1; b <= n; b++)
		{
			dp[0][0]=-1;
			for(int i=1; i<=mxd; i++)
			{
				dp[i][0]=0;
				dp[i][1]=0;
				for(int j=0; j<=i-1; j++)
				{
					dp[i][0]-=dp[j][0]*m[a][a][i-j];
					dp[i][0]%=M;
					dp[i][1]-=dp[j][0]*m[a][b][i-j];
					dp[i][1]%=M;
					dp[i][0]-=dp[j][1]*m[b][a][i-j];
					dp[i][0]%=M;
					dp[i][1]-=dp[j][1]*m[b][b][i-j];
					dp[i][1]%=M;
				}
			}
			for(int i=1; i <= mxd; i++)
				res[a][b][i] = (dp[i][1]%M+M)%M;
		}
    }

    for(int i = 0; i < q; i++)
		cout << res[que[i][0]][que[i][1]][que[i][2]] << endl;

    return 0;
}
