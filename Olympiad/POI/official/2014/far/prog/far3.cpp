/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              FarmerCraft                                   *
 *   Autor:                Marek Sommer                                  *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int n;
vector<int>graf[500005];
int t[500005];

bool cmp(const pair<int,int> &a, const pair<int,int> &b)
{
    return a.second-a.first > b.second-b.first;
}

pair<int,int> licz(int w, int o)
{
    pair<int,int> wynik = make_pair(0, t[w]);
    vector<pair<int, int> > v;
    for(int i = 0; i < (int)graf[w].size(); i++)
    {
        if(graf[w][i] == o) continue;
        v.push_back(licz(graf[w][i], w));
    }
    sort(v.begin(), v.end(), cmp);
    for(int i = 0; i < (int)v.size(); i++)
    {
        wynik.second = max(wynik.second, wynik.first + v[i].second + 1);
        wynik.first += v[i].first + 2;
    }
    return wynik;
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", t + i);
    for(int i = 1; i < n; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        graf[a].push_back(b);
        graf[b].push_back(a);
    }
    pair<int,int> p = licz(1, -1);
    printf("%d\n", max(p.second, p.first + t[1]));
    return 0;
}
