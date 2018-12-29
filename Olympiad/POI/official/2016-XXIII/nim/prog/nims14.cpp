/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Nim z utrudnieniem                                 *
 *   Autor programu:       Lech Duraj                                         *
 *   Zlozonosc czasowa:    O(md)                                              *
 *   Zlozonosc pamieciowa: O(md)                                              *
 *   Opis:                 Rozwiazanie alternatywne                           *
 *                         nie przejmujace sie limitem pamieci                *
 *****************************************************************************/


#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int base = 1000*1000*1000 + 7;
const int maxd = 10;


int main()
{
    int n, d;
    cin >> n >> d;
    vector<int> A(n);
    for(int i=0; i<n; i++)
        cin >> A[i];
    sort(A.begin(),A.end());
    vector<int> R[maxd];
    for(int j=0; j<d; j++)
        R[j].resize(1,0);
    R[0][0] = 1;
    for(int i=0; i<n; i++)
    {
        vector<int> S[maxd];
        for(int j=0; j<d; j++)
            S[j].resize(2*A[i],0);
        for(int j=0; j<d; j++)
            for(int q=0; q<(int)R[j].size(); q++)
            {
                int k = (j+1) % d;
                if (R[j][q]==0)
                    continue;
                S[j][q] = (S[j][q] + R[j][q]) % base;
                S[k][q^A[i]] = (S[k][q^A[i]] + R[j][q]) % base;
            }
        for(int j=0; j<d; j++)
            swap(R[j],S[j]);
        for(int j=0; j<d; j++)
            S[j].clear();
    }
    int answer = R[n%d][0];
    if (n%d==0)
        answer--;
    if (answer==-1)
        answer += base;
    cout << answer << endl;
}
