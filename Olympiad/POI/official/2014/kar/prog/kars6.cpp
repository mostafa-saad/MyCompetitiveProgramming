/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Karty                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n + m 2^n)                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

typedef pair<int,int> PI;

const int infty = (int)1e9+1;
const int maxn = 200*1000;

PI P[2*maxn+1];


int main()
{
    int n,m;
    scanf("%d",&n);
    assert(n<64);         // honorowe seppuku
    for(int i=0; i<n; i++)
        scanf("%d %d",&P[i].first,&P[i].second);
    scanf("%d",&m);
    for(int j=0; j<m; j++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        x--;
        y--;
        swap(P[x],P[y]);
        bool ok = false;
        for(unsigned long long q=0; (!ok) && (q<(1ULL<<n)); q++)
        {
            int t = -infty;
            int b = 0;
            while(b<n)
            {
                int s = (q & (1<<b)) ? P[b].first : P[b].second;
                if (s>=t)
                    t = s;
                else
                    break;
                b++;
                if (b==n)
                    ok = true;
            }
        }
        printf(ok ? "TAK\n" : "NIE\n");
    }
    return 0;
}
