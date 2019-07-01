/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Hotele                                        *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^3)                                        *
 *   Zlozonosc pamieciowa: O(n^2)                                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Zbyt duza zlozonosc pamieciowa                *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

const int N = 2 * 1000;

vector<int> drz[N];
int d[N][N];

void dfs(int v, int p, int dist, int r) {
    d[v][r] = d[r][v] = dist;
    for(int i = 0; i < (int)drz[v].size(); i++) if(drz[v][i] != p)
            dfs(drz[v][i], v, dist + 1, r);
}


int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--, b--;
        drz[a].push_back(b);
        drz[b].push_back(a);
    }
    for(int i = 0; i < n; i++) dfs(i, -1, 0, i);
    int wyn = 0;
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++) {
            int cd = d[i][j];
            for(int k = j + 1; k < n; k++) {
                if(d[i][k] == cd && d[j][k] == cd) wyn++;
            }
        }
    printf("%d\n", wyn);
    return 0;
}
