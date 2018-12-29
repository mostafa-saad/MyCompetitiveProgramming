/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Ptaszek                                       *
 *   Autor:                Aleksander Lukasiewicz                        *
 *   Zlozonosc czasowa:    O(qn)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

const int MAXN = 1000000;
const int INF = 1000000008;

int L[MAXN + 3], front, back;
int n, k, d[MAXN + 3], w[MAXN + 3];

void Read()
{
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>d[i];
}

void Clean(int stop)
{
    while(front < back && L[ front ] < stop)
        front++;
}

inline int Get_W(int i)
{
    if(front==back)
        return INF;

    int M = L[front];
    return w[M] + ( ( d[M] > d[i] ) ? 0 : 1 );
}

void Update(int i)
{
    while(front < back && ( (w[i] < w[ L[ back-1 ] ]) || (w[i] == w[ L[ back-1 ] ] && d[i] > d[ L[ back-1 ] ]) ) )
        back--;

    L[ back++ ] = i;
}

int Solve()
{
    w[1] = 0;
    L[0] = 1;
    back = 1;
    for(int i=2; i<=n; i++)
    {
        int stop = max(1, i-k);
        Clean(stop);

        w[i] = Get_W(i);
        Update(i);
    }

    return w[n];
}

int main()
{
    ios_base::sync_with_stdio(0);

    int q;
    Read();
    cin >> q;
    while (q--) {
        cin >> k;
        cout<<Solve()<<endl;

        for (int i = 0; i <= n; i++) {
            w[i] = 0;
            L[i] = 0;
        }
        front = 0;
        back = 0;
    }

    return 0;
}

