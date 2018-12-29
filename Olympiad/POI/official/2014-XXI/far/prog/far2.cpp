/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              FarmerCraft                                   *
 *   Autor:                Krzysztof Kiljan                              *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
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
int A[MAXN],B[MAXN];

vector<int> E[MAXN];

//trzyma pary <x_i danego wierzcholka, nr wierzch>
//set zapewnia sortowanie
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
        czas[i] = A[i] = B[i] = 0;
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

pair<int,int> p;

int dfs_b(int start)
{
    visited[start] = 1;
    int ans = 0;

    int suma = 0; //Maksymalnie 10^6

    for(int i=0; i<(int)E[start].size(); i++)
    {
        int akt = E[start][i];
        if(!visited[akt])
        {
            visited[akt] = 1;
            ans = dfs_b(akt);
            aktSas[start].insert(mp(ans + A[start] - A[akt] ,akt));
        }
    }

    while(!aktSas[start].empty())
    {
        it = aktSas[start].end();
        it--;
        p = *it;
        aktSas[start].erase(it);
        ans = max(ans, 1 + B[p.nd] + suma);
        suma += A[p.nd] + 2;
    }

    ans = max(ans, czas[start]);

    B[start] = ans;

    return ans;
}


void solve()
{
    dfs(0);
    zeruj_visit();
    rep(i,n)
    {
        A[i] *= 2;
    }
    dfs_b(0);
    B[0] = max(B[0], A[0] + czas[0]);

    printf("%d\n",B[0]);
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
