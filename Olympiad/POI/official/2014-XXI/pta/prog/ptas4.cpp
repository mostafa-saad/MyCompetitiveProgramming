/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Ptaszek                                       *
 *   Autor:                Aleksander Lukasiewicz                        *
 *   Zlozonosc czasowa:    O(qn*2^n)                                     *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

typedef long long int LL;

const int MAXN = 1000000;
const int INF = 1000000008;

int n, k, d[MAXN + 3], moves[MAXN + 3];

void Read()
{
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>d[i];
}

int Solve()
{
    if(n==1) return 0;
    if(n==2) return (d[1] > d[2] ? 0 : 1);

    int res = INF;
    for(LL mask = (1<<(min(n,60)-2))-1; mask>=0; mask--)
    {
        moves[0] = 1;
        int size = 1;
        for(int i=0; i<n-2; i++)
            if(mask&(1<<i))
                moves[size++] = i+2;
        moves[size++] = n;

        bool esc = false;
        int counter = 0;
        for(int i=1; i<size; i++)
        {
            if(moves[i] - moves[i-1] > k)
            {
                esc = true;
                break;
            }
            if(d[ moves[i] ] >= d[ moves[i-1] ])
                counter++;
        }
        if(!esc && counter < res)
            res = counter;
    }

    return res;
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
    }

    return 0;
}

