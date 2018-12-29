/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Turystyka                                     *
 *   Autor:                Marcin Andrychowicz                           *
 *   Opis:                 Rozwiazanie bledne                            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
typedef long long LL;
#define FORE(i,x) for(__typeof((x).begin()) i=(x).begin(); i != (x).end(); ++i)

const int MAXN = 20000;

int n,m,c[MAXN+7],res;
vector<int> G[MAXN+7];
bool cov[MAXN+7];

int main() {
    std::ios_base::sync_with_stdio(0);
    // wczytanie wejscia
    cin >> n >> m;
    for(int i=1; i<=n; i++)
        cin >> c[i];
    while(m--) {
        int a,b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    // rozwiazanie
    while(1) {
        double best = 1000000000;
        int choice = 0;
        for(int i=1; i<=n; i++) if(!cov[i]) {
                int count = 1;
                FORE(j,G[i])
                count += !cov[*j];
                double act = (double)c[i];
                if(act < best) {
                    best = act;
                    choice = i;
                }
            }
        if(!choice) break;
        res += c[choice];
        cov[choice] = true;
        FORE(i, G[choice])
        cov[*i] = true;
    }
    // wypisanie wyniku
    cout << res << endl;
}
