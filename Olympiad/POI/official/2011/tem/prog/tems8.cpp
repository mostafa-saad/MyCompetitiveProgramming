/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Maciej Andrejczuk                                *
 *   Zlozonosc czasowa: O(n * (MAXX - MINX))                             *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <deque>

using namespace std;

typedef pair<int, int> PII;
#define FI first
#define SE second

#define MAXX 50
#define MINX -50
int t[2][MAXX - MINX + 3];

int main() {
    int n;
    int pp = scanf("%d", &n);
    int ret = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        pp = scanf("%d %d", &a, &b);
        int curr = i % 2;
        int prev = 1 - curr;
        for (int j = MINX; j < a; j++) {
            int k = j - MINX;
            t[curr][k] = 0;
        }
        for (int j = a; j <= b; j++) {
            int k = j - MINX;
            if (k > 0) t[curr][k] = max(t[curr][k - 1], 1);
            t[curr][k] = max(t[curr][k], t[prev][k] + 1);
        }
        for (int j = b + 1; j <= MAXX; j++) {
            int k = j - MINX;
            t[curr][k] = t[curr][k - 1];
        }
        ret = max(ret, t[curr][MAXX - MINX]);
    }
    printf("%d\n", ret);
}

