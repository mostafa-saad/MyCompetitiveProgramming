/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Inspektor                                     *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O(n^2 * m * log m)                            *
 *   Zlozonosc pamieciowa: O(m)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cassert>
#include <iostream>
#include <map>
using namespace std;

const int MAXN = 307; // maksymalna liczba zeznan
const int INF = 1000000000;

int N,M,MM,T[MAXN],K[MAXN],I[MAXN],t[MAXN];
int l[MAXN], r[MAXN], X[MAXN];
int dp[MAXN][MAXN][MAXN];
bool wol[MAXN];
void set_max(int& x,int y) {
    x = max(x,y);
}

int main() {
    std::ios_base::sync_with_stdio(0);
    int tests;
    cin >> tests;
    for(int test = 1; test <= tests; test++) {

        cin >> N >> MM;
        if(MM > MAXN)
            return -1;
        for(int i=1; i<=MM; i++)
            cin >> T[i] >> K[i] >> I[i];

        int binl=0,binr=MM;
        while(binr>binl) {
            int M=(binl+binr+1)/2;
            bool ok = true;

            for(int i=0; i<=MM+3; i++) {
                X[i] = INF;
                l[i] = 0;
                r[i] = 0;
            }

            for(int i=1; i<=M; i++)
                if(X[T[i]] == INF)
                    X[T[i]] = I[i] + 1;
                else if(X[T[i]] != I[i] + 1)
                    ok = false;

            int wolni = 0;

            for(int i=1; i<=N; i++) {
                int ll = MM+1, rr = 0;
                for(int j=1; j<=M; j++)
                    if(K[j] == i) {
                        ll = min(ll, T[j]);
                        rr = max(rr, T[j]);
                    }
                if(rr == 0)
                    wolni++;
                else {
                    for(int j=ll; j<=rr; j++)
                        if(--X[j] < 0)
                            ok = false;
                    l[ll]++;
                    r[rr]++;
                }
            }

            for(int i=0; i<=MM+1; i++)
                for(int m=0; m<=N; m++)
                    for(int p=0; p<=N; p++)
                        dp[i][m][p] = -1;

            dp[0][0][0] = wolni;
            if(ok) for(int i=0; i<=MM+1; i++) {
                    // przeniesienie wynikow z poprzedniego momentu czasu
                    if(i>0)
                        for(int m=0; m<=N; m++)
                            for(int p=0; p<=N; p++)
                                set_max(dp[i][min(m+r[i-1],N)][max(p-l[i],0)], dp[i-1][m][p]);
                    // wygladzenie
                    for(int m=0; m<=N; m++)
                        for(int p=0; p<=N; p++) {
                            set_max(dp[i][m+1][p], dp[i][m][p] - 1);
                            set_max(dp[i][m][p+1], dp[i][m][p]);
                        }
                    for(int m=N; m>0; m--)
                        for(int p=0; p<=N; p++)
                            set_max(dp[i][m-1][p], dp[i][m][p]);
                    // X
                    if(X[i] < INF/2)
                        for(int m=0; m<=N; m++)
                            for(int p=0; p<=N; p++)
                                if(m + p != X[i])
                                    dp[i][m][p] = -1;
                }

            if(dp[MM+1][0][0] < 0)
                ok = false;

            if(ok)
                binl = M;
            else
                binr = M-1;
        }

        cout << binr << endl;
    }
}
