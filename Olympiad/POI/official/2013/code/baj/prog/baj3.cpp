/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Bajtokomputer                                 *
 *   Autor:                Adam Karczmarz                                *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie alternatywne                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define REP(AA,BB) for(int AA=0; AA<(BB); ++AA)
#define FOR(AA,BB,CC) for(int AA=(BB); AA<(CC); ++AA)
#define FC(AA,BB) for(__typeof((AA).begin()) BB=(AA).begin(); BB!=(AA).end(); ++BB)
#define SZ(AA) ((int)((AA).size()))
#define ALL(AA) (AA).begin(), (AA).end()
#define PB push_back
#define MP make_pair

using namespace std;

typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
typedef long double LD;

const int MAXN = 1000100, INF = MAXN;
int c[MAXN + 10], d[2][3];

int main(void) {
    int n;
    scanf("%d", &n);
    REP (i, n) {
        scanf("%d", &c[i]);
    }
    for (int i = 0; i < n; ++i) {
        int *cur = d[i % 2] + 1, *prev = d[1 - i % 2] + 1;
        for (int v = -1; v <= 1; ++v) {
            if (i == 0) {
                cur[v] = v == c[i] ? 0 : INF;
            } else {
                cur[v] = INF;
                for (int u = -1; u <= v; ++u) {
                    if (c[i] == v) {
                        cur[v] = min(cur[v], prev[u]);
                    } else if ((v - c[i]) * u > 0) {
                        cur[v] = min(cur[v], prev[u] + (v - c[i]) / u);
                    }
                }
            }
        }
    }
    int res = INF;
    for (int v = -1; v <= 1; ++v) {
        res = min(res, d[(n - 1) % 2][v + 1]);
    }
    if (res >= INF) {
        puts("BRAK");
    } else {
        printf("%d\n", res);
    }
    return 0;
}

