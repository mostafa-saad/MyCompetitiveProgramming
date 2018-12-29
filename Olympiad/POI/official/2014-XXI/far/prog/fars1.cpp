/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              FarmerCraft                                   *
 *   Autor:                Krzysztof Kiljan                              *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Dla kazdego wezla znajdujemy kolejno syna,    *
 *                         ktory moze zostac odwiedzony jako ostatni,    *
 *                         przedostatni, itd.                            *
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
const int INF = 299999999;
int visited[MAXN];
int oj[MAXN];
int A[MAXN],B[MAXN];

vector<int> E[MAXN];

vector<int> aktSas[MAXN];

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
        oj[i] = -1;
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
            oj[akt] = start;
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


int suma_a(vector<int> v)
{
    int sum = 0;

    rep(i,v.size())
    {
        sum += A[v[i]];
    }

    return sum;
}


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
            oj[akt] = start;
            visited[akt] = 1;
            ans = dfs_b(akt);
            aktSas[start].pb(akt);
        }
    }

    int maks = 0;
    int wybrany = -1;
    int indeksWybr = -1;
    int sumaa = 0;

    while(!aktSas[start].empty())
    {
        sumaa = suma_a(aktSas[start]);
        maks = 0;
        wybrany = indeksWybr = -1;

        for(int i=0; i<(int)aktSas[start].size(); i++)
        {
            int akt = aktSas[start][i];

            if(B[akt] + sumaa - A[akt] > maks)
            {
                wybrany = akt;
                indeksWybr = i;
                maks = B[akt] + sumaa - A[akt];
            }
        }

        swap(aktSas[start][indeksWybr], aktSas[start].back());

        //printf("%d %d \n",wybrany ,aktSas[start].back());
        aktSas[start].pop_back();

        ans = max(ans, 1+ B[wybrany] + suma);

        suma += A[wybrany] + 2;
    }

    ans = max(ans, czas[start]);

    B[start] = ans;

    return ans;
}


int kroki = 0;
int ans = 0;


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
