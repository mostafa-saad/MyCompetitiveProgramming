/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Karty                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(nm)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Prosty algorytm dynamiczny z optymalizacja    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int,int> PI;

const int infty = (int)1e9+1;
const int maxn = 200*1000;

PI P[2*maxn+1];
int B[2*maxn+1];

int recompute(int x, int y)
{
    for(int i=x; i<=y; i++)
    {
        if (P[i].first>=B[i-1])
            B[i] = P[i].first;
        else if (P[i].second>=B[i-1])
            B[i] = P[i].second;
        else  return i;
    }
    return -1;
}

int main()
{
    int n,m;
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
    {
        scanf("%d %d",&P[i].first,&P[i].second);
        if (P[i].first>P[i].second)
            swap(P[i].first,P[i].second);
    }
    B[0] = -infty;
    scanf("%d",&m);
    int fail = recompute(1,n);
    for(int i=0; i<m; i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        if (x>y)
            swap(x,y);
        int s = B[y];
        swap(P[x],P[y]);
        if (fail==-1)
        {
            fail = recompute(x,y);
            if (fail==-1 && B[y]>s)
                fail = recompute(y+1,n);
        } else
        {
            if (x<=fail)
                fail = recompute(x,n);
        }
        printf(fail==-1 ? "TAK\n" : "NIE\n");
    }
    return 0;
}
