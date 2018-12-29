/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Ptaszek                                       *
 *   Autor:                Aleksander Lukasiewicz                        *
 *   Zlozonosc czasowa:    O(qn log n)                                   *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         std::set                                      *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<algorithm>
#include<set>
using namespace std;

typedef pair<int,int> PII;

const int MAXN = 1000000;
const int INF = 1000000008;

int n, k, d[MAXN + 3], w[MAXN + 3];
set< pair<PII,int> > S;

void Read()
{
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>d[i];
}

int Solve()
{
    w[1] = 0;
    S.insert( make_pair( make_pair(0, -d[1]),  1) );
    for(int i=2; i<=n; i++)
    {
        set< pair<PII,int> >::iterator it = S.begin();
        pair<PII, int> v = *it;
        while(i-k > v.second)
        {
            S.erase(it);
            it++;
            v = *it;
        }
        w[i] = v.first.first + (-v.first.second <= d[i] ? 1 : 0);
        S.insert( make_pair( make_pair(w[i], -d[i]), i ) );
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
        S.clear();
        cout<<Solve()<<"\n";
        for (int i = 0; i <= n+1; i++)
            w[i] = 0;
    }

    return 0;
}
