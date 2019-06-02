/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Karty                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n + m sqrt(n))                              *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

typedef pair<int,int> PI;

const int infty = (int)1e9+1;
const int maxn = 200*1000;
const int maxs = 2000;

PI P[2*maxn+1];
int B[2][2*maxn+1];
bool A[2][maxs];
int s,k;

void recompute(int j)
{
    int x = j*s;
    int y = j*s+s-1;
    A[0][j] = A[1][j] = true;
    B[0][x] = P[x].first;
    B[1][x] = P[x].second;
    for(int q=0; q<=1; q++)
    {
        for(int i=x+1; i<=y; i++)
        {
            if (P[i].first>=B[q][i-1])
                B[q][i] = P[i].first;
            else if (P[i].second>=B[q][i-1])
                B[q][i] = P[i].second;
            else {
                A[q][j] = false;
                break;
            }
        }
    }
}

int main()
{
    int n,m;
    scanf("%d",&n);
    s = max((int)sqrt(n),3);
    for(int i=0; i<n; i++)
    {
        scanf("%d %d",&P[i].first,&P[i].second);
        if (P[i].first>P[i].second)
            swap(P[i].first,P[i].second);
    }
    while(n%s!=0)
    {
        P[n].first = P[n].second = infty;
        n++;
    }
    k = n/s;
    fprintf(stderr,"%d\n",k);
    for(int i=0; i<k; i++)
        recompute(i);
    scanf("%d",&m);
    for(int j=0; j<m; j++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        x--;
        y--;
        swap(P[x],P[y]);
        recompute(x/s);
        recompute(y/s);
        int p = -infty;
        bool ok = true;
        for(int i=0; ok && i<k; i++)
        {
            ok = false;
            if (p<=P[i*s].first && A[0][i])
            {
                p = B[0][i*s+s-1];
                ok = true;
            }
            else if (p<=P[i*s].second && A[1][i])
            {
                p = B[1][i*s+s-1];
                ok = true;
            }
        }
        printf(ok ? "TAK\n" : "NIE\n");
    }
    return 0;
}
