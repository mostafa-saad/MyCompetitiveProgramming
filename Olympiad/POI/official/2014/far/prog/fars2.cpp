/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              FarmerCraft                                   *
 *   Autor:                Marek Sommer                                  *
 *   Zlozonosc czasowa:    O(n!)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int infty = 2e9;

vector<int> graf[500005];
int c[500005];

pair<int,int> licz(int w, int o)
{
    pair<int, int> wynik = make_pair(infty, 0);
    vector<pair<int, int> > syny;
    for(int i = 0; i < (int)graf[w].size(); i++)
    {
        if(graf[w][i] == o) continue;
        syny.push_back(licz(graf[w][i], w));
        wynik.second += syny.back().second + 2;
    }
    vector<int> permutacja;
    for(int i = 0; i < (int)syny.size(); i++) permutacja.push_back(i+1);
    do
    {
        int czas = 0;
        int ost = c[w];
        for(int i = 0; i < (int)permutacja.size(); i++)
        {
            int v = permutacja[i] - 1;
            czas++;
            ost = max(ost, syny[v].first + czas);
            czas += syny[v].second;
            czas++;
        }
        wynik.first = min(wynik.first, ost);
    }
    while(next_permutation(permutacja.begin(), permutacja.end()));
    return wynik;
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", c+i);
    for(int i = 1; i < n; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        graf[a].push_back(b);
        graf[b].push_back(a);
    }
    pair<int,int> wynik = licz(1, -1);
    printf("%d\n", max(wynik.first, wynik.second + c[1]));
    return 0;
}
