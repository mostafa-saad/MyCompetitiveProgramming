/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Ptaszek                                       *
 *   Autor:                Aleksander Lukasiewicz                        *
 *   Zlozonosc czasowa:    O(qn log n)                                   *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Kolejka priorytetowa                          *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

typedef pair<int,int> PII;

const int MAXN = 1000000;
const int INF = 1000000008;

int n, k, d[MAXN + 3], w[MAXN + 3];
priority_queue< pair<PII,int> > Q;

void Read()
{
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>d[i];
}

int Solve()
{
    w[1] = 0;
    Q.push( make_pair( make_pair(0, d[1]),  1) );
    for(int i=2; i<=n; i++)
    {
        pair<PII, int> v = Q.top();
        while(i-k > v.second)
        {
            Q.pop();
            v = Q.top();
        }
        w[i] = -v.first.first + (v.first.second <= d[i] ? 1 : 0);
        Q.push( make_pair( make_pair(-w[i], d[i]), i ) );
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
        while (!Q.empty())
            Q.pop();
        cout<<Solve()<<"\n";
        for (int i = 0; i <= n+1; i++)
            w[i] = 0;
    }

    return 0;
}

