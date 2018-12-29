/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Poslaniec                                          *
 *   Autor programu:       Wojtek Nadara                                      *
 *   Zlozonosc czasowa:    O(n^3 * d * q)                                     *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/

#include <iostream>
#define D 52
#define M mod
#define N 152
#define uint long long int
using namespace std;
uint m[N][N][D+2];
uint dr[N][N][D+2];
int main()
{
	ios_base::sync_with_stdio(false);
    int n, kr, d;
    int a, b, mod;
    cin>>n>>kr>>mod;
    for(int i=1; i<=kr; i++)
    {
        cin>>a>>b;
        m[a][b][1]=1;
        // m[b][a][1]=1;
    }
    for(int i=1; i<=n; i++)
    {
        m[i][i][0]=1;
        dr[i][i][0]=1;
    }
    for(int t=2; t<=D; t++)
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
    int q;
    cin>>q;
    for(int z=1; z<=q; z++)
    {
        cin>>a>>b>>d;
        if(d==1)
        {
            cout<<m[a][b][1]<<endl;
            continue;
        }
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                dr[i][j][1]=m[i][j][1];
                if(i==a || i==b || j==a || j==b)
                {
                    dr[i][j][1]=0;
                }
            }
        }
        d-=2;
        for(int t=2; t<=d; t++)
        {
            for(int i=1; i<=n; i++)
            {
                for(int j=1; j<=n; j++)
                {
                    dr[i][j][t]=0;
                    for(int k=1; k<=n; k++)
                    {
                        dr[i][j][t]+=dr[i][k][t-1]*dr[k][j][1];
                        dr[i][j][t]%=M;
                    }
                }
            }
        }
        uint wyn=0;
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                wyn+=m[a][i][1]*dr[i][j][d]*m[j][b][1];
                wyn%=M;
            }
        }
        cout<<wyn<<endl;
    }
    return 0;
}
