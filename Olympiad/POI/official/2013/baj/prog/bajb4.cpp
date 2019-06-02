/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Bajtokomputer                                 *
 *   Autor:                Adam Karczmarz                                *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         -1 na poczatku, nie oplaca sie robic bloku 0  *
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

const int MAXN = 1000100;
int c[MAXN], ile[MAXN][3];

inline int get(int a, int b, int k) {
    return ile[b][k + 1] - (a > 0 ? ile[a - 1][k + 1] : 0);
}

int main(void) {
    int n;
    scanf("%d", &n);
    REP (i, n) {
        scanf("%d", &c[i]);
    }
    c[n++] = 1;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            REP (j, 3) {
                ile[i][j] = ile[i - 1][j];
            }
        }
        ++ile[i][c[i] + 1];
    }
    int fnz = -1;
    REP (i, n) {
        if (c[i] != 0) {
            fnz = i;
            break;
        }
    }
    // same zera
    if (fnz == -1) {
        puts("0");
        return 0;
    }
    // zero na poczatku, potem pierwsza != 0 wartosc to -1
    if (c[0] == 0 && c[fnz] == -1) {
        puts("BRAK");
        return 0;
    }
    // jest cos niezerowego
    int res = 0;
    // 0 na początku, nic nie mozemy zrobic z pierwsza jedynka
    if (c[0] == 0) {
        res = 2 * get(fnz, n - 1, -1) + get(fnz, n - 1, 0);
    } else if (c[0] == 1) { // jedynka na poczatku
        res = 2 * get(0, n - 1, -1) + get(0, n - 1, 0);
    } else { // -1 na poczatku, musi istnieć blok ujemny
        res = 2 * get(0, n - 1, 1) + get(0, n - 1, 0);
        // sprawdzamy wszystkie bloki zerowe
        for (int i = 0; i < n; ) {
            if (c[i] != 0) {
                ++i;
                continue;
            }
            int j;
            for (j = i; j < n && c[j] == 0; ++j);
            if (c[j] == 1) {
                int can = 2 * get(j, n - 1, -1) + get(j, n - 1, 0);
                if (c[i - 1] == 1) {
                    can += 2 * get(0, i - 2, 1) + get(0, i - 2, 0) + 1;
                } else {
                    can += 2 * get(0, i - 1, 1) + get(0, i - 1, 0);
                }
                res = min(res, can);
            }
            i = j;
        }
    }
    printf("%d\n", res);
    return 0;
}

