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

list<int> L[MAXN + 3];
int n, k, d[MAXN + 3], w[MAXN + 3];

void Read()
{
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>d[i];
}

void Clean(int x, int stop)
{
    while(!L[x].empty() && L[x].front() < stop)
        L[x].pop_front();
}

inline int Get_Candidate(int x, int i)
{
    if(L[x].empty())
        return INF;

    return x + ( ( d[ L[x].front() ] > d[i] ) ? 0 : 1 );
}

void Update(int x, int i)
{
    while(!L[x].empty() && d[i] > d[ L[x].back() ])
        L[x].pop_back();
    L[x].push_back(i);
}

int Solve()
{
    w[1] = 0;
    int x = 0;
    L[0].push_back(1);
    for(int i=2; i<=n; i++)
    {
        int stop = max(1, i-k);
        Clean(x, stop);
        Clean(x+1, stop);

        if(L[x].empty())
            x++;

        int candidate1 = Get_Candidate(x, i);
        int candidate2 = Get_Candidate(x+1, i);

        w[i] = min(candidate1, candidate2);
        Update(w[i], i);
    }

    return w[n];
}

int main()
{
    ios_base::sync_with_stdio(0);
    Read();
    int q;
    cin >> q;
    while (q--) {
        cin >> k;
        cout<<Solve()<<endl;
        for (int i = 0; i <= n; i++) {
            w[i] = 0;
            L[i].clear();
        }
    }
    return 0;
}

