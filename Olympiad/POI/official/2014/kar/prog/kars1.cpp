/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Karty                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(nm)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Prosty algorytm dynamiczny                    *
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


int main()
{
    int n,m;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        scanf("%d %d",&P[i].first,&P[i].second);
        if (P[i].first>P[i].second)
            swap(P[i].first,P[i].second);
    }
    scanf("%d",&m);
    for(int j=0; j<m; j++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        x--;
        y--;
        swap(P[x],P[y]);
        int p = -infty;
        bool ok = true;
        for(int i=0; i<n; i++)
        {
            if (P[i].first>=p)
                p = P[i].first;
            else if (P[i].second>=p)
                p = P[i].second;
            else {
                ok = false;
                break;
            }
        }
        printf(ok ? "TAK\n" : "NIE\n");
    }
    return 0;
}
