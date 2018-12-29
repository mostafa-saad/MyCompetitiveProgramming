/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Poslaniec                                          *
 *   Autor:                Wojtek Nadara (zmienione w C99 przez: Michał Glapa)*
 *   Zlozonosc czasowa:    O(n^3 * d + q*d^2)                                 *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <stdio.h>
#define D 52
#define M mod
#define N 154
#define uint long long int
uint m[N][N][D+2];
uint dp[D][2];
uint res[N][N][D+2];
int main()
{
    int n, kr, d;
    uint mod;
    int a, b;
    scanf("%d %d %lld",&n,&kr,&mod);
    int i ; for(i=1; i<=kr; i++)
    {
        scanf("%d %d",&a,&b);
        m[a][b][1]=1;
        // m[b][a][1]=1;
    }
    for(i=1; i<=n; i++)
    {
        m[i][i][0]=1;
    }
    int t ; for(t=2; t<=D; t++)
    {
        int i ; for(i=1; i<=n; i++)
        {
            int j ; for(j=1; j<=n; j++)
            {
                int k ; for(k=1; k<=n; k++)
                {
                    m[i][j][t]+=m[i][k][t-1]*m[k][j][1];
                    m[i][j][t]%=M;
                }
            }
        }
    }
    
    /*int z ; for(z=1; z<=q; z++)
    {
        
        dp[0][0]=-1;
        int i ; for(i=1; i<=d; i++)
        {
            dp[i][0]=0;
            dp[i][1]=0;
            int j ; for(j=0; j<=i-1; j++)
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
    }*/
    
    //int a, b;
    for(a=1; a<=n; a++)
    {
		for(b = 1; b <= n; b++)
		{
			dp[0][0]=-1;
			for(i=1; i<D; i++)
			{
				dp[i][0]=0;
				dp[i][1]=0;
				int j; for(j=0; j<=i-1; j++)
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
			for(i=1; i < D; i++)
				res[a][b][i] = (dp[i][1]%M+M)%M;
		}
    }
    
    int q;
    scanf("%d",&q);
    
    for(i = 0; i < q; i++){
		scanf("%d%d%d",&a,&b,&d);
		printf("%lld\n", res[a][b][d]);
	}
    return 0;
}
