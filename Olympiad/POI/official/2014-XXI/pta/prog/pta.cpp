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

int L[2][MAXN + 3], front[2], back[2];
int n, k, d[MAXN + 3], w[MAXN + 3];

void Read()
{
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>d[i];
}

void Clean(int x, int stop)
{
    int ind = x%2;
    while(front[ind] < back[ind] && L[ind][ front[ind] ] < stop)
        front[ind]++;
}

inline int Get_Candidate(int x, int i)
{
    int ind = x%2;
    if(front[ind]==back[ind])
        return INF;

    int M = L[ind][ front[ind] ];
    return x + ( ( d[M] > d[i] ) ? 0 : 1 );
}

void Update(int x, int i)
{
    int ind = x%2;
    while(front[ind] < back[ind] && d[i] > d[ L[ind][ back[ind] - 1 ] ])
        back[ind]--;

    L[ind][ back[ind]++ ] = i;
}

int Solve()
{
    w[1] = 0;
    int x = 0;
    L[0][0] = 1;
    back[0] = 1;
    for(int i=2; i<=n; i++)
    {
        int stop = max(1, i-k);
        Clean(x, stop);
        Clean(x+1, stop);

        if(front[x%2] == back[x%2])
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
    int q;
    Read();
    cin >> q;
    while (q--) {
        cin >> k;
        cout<<Solve()<<endl;
        for (int i = 0; i <= n; i++) {
            L[0][i] = 0;
            L[1][i] = 0;
            w[i] = 0;
        }
        front[0] = 0;
        front[1] = 0;
        back[0] = 0;
        back[1] = 0;
    }
    return 0;
}
