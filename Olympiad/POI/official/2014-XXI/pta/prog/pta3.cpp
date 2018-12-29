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
#include<list>
using namespace std;

const int MAXN = 1000000;
const int INF = 1000000008;

list<int> L;
int n, k, d[MAXN + 3], w[MAXN + 3];

void Read()
{
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>d[i];
}

void Clean(int stop)
{
    while(!L.empty() && L.front() < stop)
        L.pop_front();
}

inline int Get_W(int i)
{
    if(L.empty())
        return INF;

    int M = L.front();
    return w[M] + ( ( d[M] > d[i] ) ? 0 : 1 );
}

void Update(int i)
{
    while(!L.empty() && ((w[i] < w[ L.back() ]) || (w[i] == w[ L.back() ] && d[i] > d[ L.back() ])) )
        L.pop_back();
    L.push_back(i);
}

int Solve()
{
    w[1] = 0;
    L.push_back(1);
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
        for (int i = 0; i <= n+1; i++)
            w[i] = 0;
        L.clear();
    }

    return 0;
}

