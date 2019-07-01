/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Karty                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n + m log n)                                *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Dziala poprawnie gdy liczba na awersie równa  *
 *                         sie liczbie na rewersie + nieco uogolnia.     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

const int maxn = 200000;
int A[2][maxn];
set<int> bad[2];
int n;

void c_delete(set<int> &S, int x)
{
    if (S.find(x)!=S.end())
        S.erase(x);
}

void change(int q, int x, int v)
{
    if (x<n-1) c_delete(bad[q],x);
    if (x>0) c_delete(bad[q],x-1);
    A[q][x] = v;
    if (x<n-1 && A[q][x]>A[q][x+1]) bad[q].insert(x);
    if (x>0 && A[q][x-1]>A[q][x]) bad[q].insert(x-1);
}

int main()
{
    int m,x,y;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        scanf("%d %d",&x,&y);
        A[0][i] = min(x,y);
        A[1][i] = max(x,y);
    }
    for(int i=0; i<n-1; i++)
    {
        change(0,i,A[0][i]);
        change(1,i,A[1][i]);
    }
    scanf("%d",&m);
    for(int i=0; i<m; i++)
    {
        scanf("%d %d",&x,&y);
        x--;
        y--;
        for(int q=0; q<2; q++)
        {
            int tx = A[q][x];
            int ty = A[q][y];
            change(q,x,ty);
            change(q,y,tx);
        }
        bool ok;
        if (bad[0].empty() || bad[1].empty())
            ok = true;
        else
        {
            int u = *bad[0].begin();
            int v = *bad[1].rbegin();
            ok = (u>v) || (u==v && A[0][u]<=A[1][u+1]);
        }
        printf(ok ? "TAK\n" : "NIE\n");
    }
}
