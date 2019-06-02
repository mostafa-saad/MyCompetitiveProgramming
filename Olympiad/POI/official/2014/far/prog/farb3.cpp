/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              FarmerCraft                                   *
 *   Autor:                Krzysztof Kiljan                              *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Sprawdza tylko czas instalacji u soltysa.     *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<set>
using namespace std;

#define mp make_pair
#define st first
#define nd second
#define rep(i,n) for(int i=0;i<(int)n;i++)
#define pb push_back

const int MAXN = 500 * 1000 + 3;

int visited[MAXN];
int A[MAXN];

vector<int> E[MAXN];

//trzyma pary <x_i danego wierzcholka, nr wierzch>
set<pair<int,int> > aktSas[MAXN];
set<pair<int,int> >::iterator it;

int a,b,k,n;

int czas[MAXN];

void zeruj_visit()
{
    rep(i,MAXN)
    {
        visited[i] = 0;
    }
}
void zeruj()
{
    zeruj_visit();

    rep(i,MAXN)
    {
        czas[i] = A[i] = 0;
    }
}

//Wyznaczamy tablicę A wartosci w poddrzewach
int dfs(int start)
{
    visited[start] = 1;
    int ans = 0;

    for(int i=0; i<(int)E[start].size(); i++)
    {
        int akt = E[start][i];
        if(!visited[akt])
        {
            visited[akt] = 1;
            ans += dfs(akt);
        }
    }

    ans += E[start].size();
    if(start != 0) ans--;
    visited[start] = 2;
    A[start] = ans;
    return ans;
}


int kroki = 0;
int ans = 0;


void solve()
{
    dfs(0);

    rep(i,n)
    {
        A[i] *= 2;
    }

    printf("%d\n",A[0]+czas[0]);
}

void readIn()
{
    scanf("%d",&n);

    rep(i,n)
    {
        scanf("%d",&k);
        czas[i] = k;
    }

    rep(i,n-1)
    {
        scanf("%d %d",&a,&b);
        a--;
        b--;
        E[a].pb(b);
        E[b].pb(a);
    }

}

int main()
{
    zeruj();
    readIn();
    solve();
    return 0;
}
