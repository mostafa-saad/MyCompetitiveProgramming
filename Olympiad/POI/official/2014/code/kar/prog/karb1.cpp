/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Karty                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n + m)                                      *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Dziala poprawnie gdy dla kazdej karty liczba  *
 *                         na awersie równa sie liczbie na rewersie      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 200000;
int A[maxn];
int badcount;
int n;

void change(int x, int v)
{
    if (x<n-1) badcount -= (A[x]>A[x+1]);
    if (x>0) badcount -= (A[x-1]>A[x]);
    A[x] = v;
    if (x<n-1) badcount += (A[x]>A[x+1]);
    if (x>0) badcount += (A[x-1]>A[x]);
}

int main()
{
    int m,x,y;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        scanf("%d %d",&x,&y);
        A[i] = min(x,y);
    }
    badcount = 0;
    for(int i=0; i<n-1; i++)
        badcount += A[i]>A[i+1];
    scanf("%d",&m);
    for(int i=0; i<m; i++)
    {
        scanf("%d %d",&x,&y);
        x--;
        y--;
        int tx = A[x];
        int ty = A[y];
        change(x,ty);
        change(y,tx);
        printf(badcount==0 ? "TAK\n" : "NIE\n");
    }
}
