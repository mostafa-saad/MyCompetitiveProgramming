/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gra Tower Defense                             *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O(n+m)                                        *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Zwrocone numery wiez powtarzaja sie           *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
#include <vector>
#include <assert.h>
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
    for(int i=1; i<=n; i++) if(!safe[i]) {
            towers.push_back(i);
            safe[i] = true;
            FORE(j, edges[i]) {
                safe[*j] = true;
                FORE(k, edges[*j])
                    safe[*k] = true;
            }
        }
    //wypisanie wyniku
    towers.push_back(towers.back());
    cout << towers.size() << endl;
    FORE(i, towers)
        cout << *i << " ";
    cout << endl;
    return 0;
}
