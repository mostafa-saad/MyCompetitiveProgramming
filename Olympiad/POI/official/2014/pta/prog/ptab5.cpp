/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Ptaszek                                       *
 *   Autor:                Aleksander Lukasiewicz                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Heurystyka, ktora brutalnie przeszukuje tylko *
 *                         czesc poprzednikow drzewa, jesli wartosc      *
 *                         k okazuje sie byc zbyt duza                   *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

const int MAXN = 1000000;
const int INF = 1000000008;

int n, k, d[MAXN + 3], w[MAXN + 3];

void Read()
{
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>d[i];
}

int Solve()
{
    k = min(100, k);
    w[1] = 0;
    for(int i=2; i<=n; i++)
    {
        w[i] = INF;
        int stop = max(1, i-k);
        for(int j=i-1; j>=stop; j--)
            w[i] = min(w[i], w[j]+( d[j]<=d[i] ? 1 : 0) );
    }

    return w[n];
}

int main()
{
    int q;
    ios_base::sync_with_stdio(0);
    Read();
    cin >> q;
    while (q--) {
        cin >> k;
        cout<<Solve()<<"\n";
        for (int i = 0; i <= n+1; i++)
            w[i] = 0;
    }

    return 0;
}

