/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Ptaszek                                       *
 *   Autor:                Aleksander Lukasiewicz                        *
 *   Zlozonosc czasowa:    O(qn log n)                                   *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Drzewo przedzialowe indeksowane wysokosciami  *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<algorithm>
#include<queue>
#include<list>
using namespace std;

typedef pair<int,int> PII;

const int MAXN = 1000000;
const int MAXSIZE = 2097152;
const int INF = 1000000008;

PII rd[MAXN + 3];
int n, k, M, d[MAXN + 3], w[MAXN + 3], Tree[MAXSIZE + 10];
list<int> candidates[MAXN + 3];

void Read()
{
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>d[i];
}

void Renumber()
{
    for(int i=1; i<=n; i++)
        rd[i] = make_pair(d[i], i);

    sort(rd+1, rd+n+1);

    int new_h = 0;
    d[ rd[1].second ] = new_h;

    for(int i=2; i<=n; i++)
    {
        if(rd[i].first > rd[i-1].first)
            new_h++;
        d[ rd[i].second ] = new_h;
    }
}

void Build_Tree()
{
    M = 1;
    while(M<n)
        M*=2;
    w[0] = INF;
}

int Get_Min(int a, int b)
{
    int va = M + a, vb = M + b;
    int res = min(w[ Tree[va] ], w[ Tree[vb] ]);
    while (va/2 != vb/2)
    {
        if (va%2 == 0) res = min(res, w[ Tree[va + 1] ]);
        if (vb%2 == 1) res = min(res, w[ Tree[vb - 1] ]);
        va/=2;
        vb/=2;
    }
    return res;
}

void Update(int a, int val)
{
    int v = M+a;
    Tree[v] = val;

    while(v!=1)
    {
        v/=2;
        Tree[v] = (w[ Tree[2*v] ] < w[ Tree[2*v+1] ] ? Tree[2*v] : Tree[2*v+1]);
    }
}

int Solve()
{
    if (n == 2) {
        if (d[1] <= d[2])
            return 1;
        else
            return 0;
    }

    w[1] = 0;
    Update(d[1], 1);

    for(int i=2; i<=n; i++)
    {
        int old = i-k-1;
        if(old >= 1 && Tree[ M+d[old] ] == old)
        {
            while(!candidates[ d[old] ].empty() && candidates[ d[old] ].front() <= old)
                candidates[ d[old] ].pop_front();

            if(candidates[ d[old] ].empty())
                Update(d[old], 0);
            else
                Update(d[old], candidates[ d[old] ].front());
        }

        w[i] = min( Get_Min(0, d[i]) + 1 , Get_Min(d[i]+1, n-1) );
        if(w[ Tree[ M+d[i] ] ] > w[i])
        {
            Update(d[i], i);
            while(!candidates[ d[i] ].empty()) candidates[ d[i] ].pop_front();
        }
        else
            candidates[ d[i] ].push_back(i);
    }

    return w[n];
}

int main()
{
    int q;
    ios_base::sync_with_stdio(0);
    Read();
    Renumber();
    cin >> q;
    while (q--) {
        Build_Tree();
        cin >> k;
        cout<<Solve()<<"\n";
        for (int i = 0; i <= n+1; i++) {
            w[i] = 0;
            candidates[i].clear();
            rd[i] = make_pair(0, 0);
        }
        for (int i = 0; i <= n+1; i++)
            Update(i, 0);
    }

    return 0;
}

