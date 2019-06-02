/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Nim z utrudnieniem                                 *
 *   Autor programu:       Lech Duraj                                         *
 *   Zlozonosc czasowa:    O(m*d)                                             *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/


#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int base = 1000*1000*1000 + 7;
const int maxd = 10;
const int maxxor = (1 << 20) + 1;

int maxb(int x)
{
    int r = 1;
    while(r<=x)
        r *= 2;
    return r;
}

int main()
{
    int n, d;
    cin >> n >> d;
    vector<int> A(n);
    for(int i=0; i<n; i++)
        cin >> A[i];
    sort(A.begin(),A.end());
    int R[maxd][maxxor];
    for(int q=0; q<maxxor; q++)
        for(int j=0; j<d; j++)
            R[j][q] = 0;
    R[0][0] = 1;
    for(int i=0; i<n; i++)
    {
        int m = max(maxb(A[i]),2);
        for(int q=0; q<m; q++)
        {
            int s = q^A[i];
            if (q > s)
                continue;
            int newq[maxd], news[maxd];
            for(int j=0; j<d; j++)
            {
                int k = (j+1)%d;
                newq[k] = (R[j][s]+R[k][q])%base;
                news[k] = (R[j][q]+R[k][s])%base;
            }
            for(int j=0; j<d; j++)
            {
                R[j][q] = newq[j];
                R[j][s] = news[j];
            }
        }
    }
    int answer = R[n%d][0];
    if (n%d==0)
        answer--;
    if (answer==-1)
        answer += base;
    cout << answer << endl;
}
