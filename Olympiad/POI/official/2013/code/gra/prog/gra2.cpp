/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gra Tower Defense                             *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n+m)                                        *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define foreach(t,v) for(typeof(v.begin()) t = v.begin(); t!=v.end(); t++)

const int maxn = 500*1000;


int main()
{
    int n,m,k;
    vector<int> G[maxn+1];
    bool marked[maxn+1];
    scanf("%d %d %d",&n,&m,&k);
    for(int i=0; i<m; i++)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for(int i=1; i<=n; i++)
        marked[i] = false;
    vector<int> towers;
    for(int i=1; i<=n; i++)
        if (!marked[i])
        {
            towers.push_back(i);
            marked[i] = true;
            foreach(t,G[i])
            {
                marked[*t] = true;
                foreach(s,G[*t])
                marked[*s] = true;
            }
        }
    printf("%d\n",(int)towers.size());
    foreach(t,towers)
    printf("%d ",*t);
}
