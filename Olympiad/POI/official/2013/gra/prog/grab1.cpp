/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gra Tower Defense                             *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O(n+m)                                        *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Zwraca losowy podzbior k miast                *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define FORE(i,x) for(__typeof((x).begin()) i=(x).begin();i != (x).end();++i)

const int MAXN = 500000;
int n, m, k;
vector<int> edges[MAXN + 1], towers;
bool safe[MAXN + 1];

int main() {
    std::ios_base::sync_with_stdio(0);
    //wczytanie wejscia
    cin >> n >> m >> k;
    for(int i=1; i<=m; i++) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    //rozwiazanie
    vector<int> perm;
    for(int i=1; i<=n; i++) perm.push_back(i);
    
    random_shuffle(perm.begin(), perm.end());
    memset(safe, 0, sizeof(safe));
    for(int i=0; i<k; i++) {
        safe[perm[i]] = true;
        FORE(j,edges[perm[i]]) {
            safe[*j] = true;
            FORE(k,edges[*j])
                safe[*k] = true;
        }
    }
    
    cout << k << endl;
    for(int i=0; i<k; i++)
        cout << perm[i] << " ";
    return 0;
}
