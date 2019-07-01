/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              FarmerCraft                                   *
 *   Autor:                Krzysztof Kiljan                              *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Zachlannie wybieramy poddrzewo, w ktorym      *
 *                         znajduje sie wierzcholek o najwiekszym        *
 *                         potrzebnym czasie.                            *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;

#define mp make_pair
#define st first
#define nd second
#define rep(i,n) for(int i=0;i<(int)n;i++)
#define pb push_back

const int MAXN = 500 * 1000 + 3;

int maksWPoddrzewie[MAXN];
int visited[MAXN];
int oj[MAXN];

vector<int> E[MAXN];

//trzyma pary <maks w danym poddrzewie, nr wierzch>
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
        czas[i] = maksWPoddrzewie[i] = 0;
        oj[i] = -1;
    }
}

//Wyznaczamy najwieksze wartosci w poddrzewach
int dfs(int start)
{
    visited[start] = 1;
    int ans = czas[start];
    for(int i=0; i<(int)E[start].size(); i++)
    {
        int akt = E[start][i];
        if(!visited[akt])
        {
            oj[akt] = start;
            visited[akt] = 1;
            ans = max(ans,dfs(akt));
        }
    }

    visited[start] = 2;
    maksWPoddrzewie[start] = ans;
    return ans;
}

void ustawAktSas(int v)
{


    rep(i,E[v].size())
    {
        int akt = E[v][i];
        if(akt != oj[v])
            aktSas[v].insert(mp(maksWPoddrzewie[akt],akt));
    }
}

int kroki = 0;
int ans = 0;
int dfs2(int start)
{
    visited[start] = 1;

    ans = max(ans,czas[start]+kroki);

    while(!aktSas[start].empty())
    {
        it = aktSas[start].end();
        it--;
        pair<int,int> p = *it;
        int akt = p.nd;

        aktSas[start].erase(it);
        if(!visited[akt])
        {
            kroki++;
            dfs2(akt);
            kroki++;
        }
    }

    return ans;
}

void solve()
{
    dfs(0);
    rep(i,n) ustawAktSas(i);
    zeruj_visit();
    ans = dfs2(0);

    ans= max(ans,2*(n-1)+czas[0]);
    printf("%d\n",ans);
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
