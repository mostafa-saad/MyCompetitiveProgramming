/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Ptaszek                                       *
 *   Autor:                Aleksander Lukasiewicz                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Przelatujemy zawsze z drzewa o najmniejszym   *
 *                         mozliwym koszcie z ostatnich k drzew          *
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
priority_queue< PII > Q;

void Read()
{
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>d[i];
}

int Solve()
{
    w[1] = 0;
    Q.push( make_pair( -w[1], 1 ) );
    for(int i=2; i<=n; i++)
    {
        PII v = Q.top();
        while(i-k > v.second)
        {
            Q.pop();
            v = Q.top();
        }
        w[i] = -v.first + (d[ v.second ] <= d[i] ? 1 : 0);
        Q.push( make_pair(-w[i], i) );
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
        while (!Q.empty())
            Q.pop();
        for (int i = 0; i <= n+1; i++)
            w[i] = 0;
    }

    return 0;
}

