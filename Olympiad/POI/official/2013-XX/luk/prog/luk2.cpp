/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Luk triumfalny                                *
 *   Autor:                Wiktor Kuropatwa                              *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> D[300005];
int add[300005];
int n,ignore;

void read()
{
    ignore = scanf("%d", &n);
    for(int i = 1; i<n; i++)
    {
        int a,b;
        ignore = scanf("%d%d", &a, &b);
        D[a].push_back(b);
        D[b].push_back(a);
    }
}
void root(int u, int p)
{
    for(int i = 0; i<(int)D[u].size(); i++)
    {
        if(D[u][i] != p)
            root(D[u][i],u);
        else
        {
            swap(D[u][i], D[u].back());
            D[u].pop_back();
            i--;
        }
    }
}
void dfs(int u, int s)
{
    if(D[u].size() == 0)
    {
        add[u] = 0;
        return;
    }
    for(int i = 0; i<(int)D[u].size(); i++)
        dfs(D[u][i],s);
    add[u] = 0;
    for(int i = 0; i<(int)D[u].size(); i++)
        add[u] += add[D[u][i]] + 1;
    add[u] -= s;
    add[u] = max(add[u],0);
}
bool check(int s)
{
    dfs(1,s);
    return !add[1];
}
int binSearch()
{
    int p = 0, q = n;
    while(q-p>1)
    {
        int s = (p+q)/2;
        if(check(s))
            q = s;
        else
            p = s;
    }
    if(check(p))
        return p;
    return q;
}
int main()
{
    read();
    root(1,1);
    printf("%d\n", binSearch());
    return 0;
}
