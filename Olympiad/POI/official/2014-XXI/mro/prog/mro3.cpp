/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Mrowisko                                      *
 *   Zlozonosc czasowa:    O((n+g) log g)                                *
 *   Zlozonosc pamieciowa: O(n+g)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef long long int ll;

const int infty = 2e9;

int n, g, k;

vector<int>graf[1000005];

int v1, v2;

ll mn[1000005];
ll mx[1000005];

void dfs(int w, int o)
{
    if((int)graf[w].size() == 1)
    {
        mn[w] = mn[o];
        mx[w] = mx[o];
    }
    else
    {
        mn[w] = mn[o] * (graf[w].size() - 1);
        mx[w] = mx[o] * (graf[w].size() - 1) + graf[w].size() - 2;
    }
    if(mn[w] > infty) mn[w] = infty;
    if(mx[w] > infty) mx[w] = infty;
    for(int i = 0; i < (int)graf[w].size(); i++)
        if(graf[w][i] != o) dfs(graf[w][i], w);
}

vector<pair<int, int> >zda;

int main()
{
    scanf("%d%d%d", &n, &g, &k);
    for(int i = 0; i < g; i++)
    {
        int x;
        scanf("%d", &x);
        zda.push_back(make_pair(x, 0));
    }
    scanf("%d%d", &v1, &v2);
    graf[v1].push_back(0);
    graf[v2].push_back(0);
    for(int i = 2; i < n; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        graf[a].push_back(b);
        graf[b].push_back(a);
    }
    mn[0] = mx[0] = k;
    dfs(v1, 0);
    dfs(v2, 0);
    for(int i = 1; i <= n; i++)
    {
        if((int)graf[i].size() == 1)
        {
            zda.push_back(make_pair(mn[i], -1));
            zda.push_back(make_pair(mx[i], 1));
        }
    }
    sort(zda.begin(), zda.end());
    ll wynik = 0LL;
    int ile = 0;
    for(int i = 0; i < (int)zda.size(); i++)
    {
        if(zda[i].second == -1) ile++;
        else if(zda[i].second == 1) ile--;
        else wynik += ile;
    }
    printf("%lld\n", wynik * k);
    return 0;
}
