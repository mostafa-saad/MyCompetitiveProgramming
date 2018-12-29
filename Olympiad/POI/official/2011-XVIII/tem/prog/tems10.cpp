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

#define MAX_DELTA 2000002
#define MAX_N 1000001

int A[MAX_N];
int B[MAX_N];
int t[2][MAX_DELTA];

int main() {
    int n;
    int pp = scanf("%d", &n);
    int ret = 0;
    int minx = MAX_DELTA;
    int maxx = 0;

    for (int i = 0; i < n; i++) {
        int a, b;
        pp = scanf("%d %d", &a, &b);
        minx = min(minx, a);
        maxx = max(maxx, b);
        A[i] = a;
        B[i] = b;
    }
    for (int i = 0; i < n; i++) {
        int curr = i % 2;
        int prev = 1 - curr;
        for (int j = minx; j < A[i]; j++) {
            int k = j - minx;
            t[curr][k] = 0;
        }
        for (int j = A[i]; j <= B[i]; j++) {
            int k = j - minx;
            if (k > 0) t[curr][k] = max(t[curr][k - 1], 1);
            t[curr][k] = max(t[curr][k], t[prev][k] + 1);
        }
        for (int j = B[i] + 1; j <= maxx; j++) {
            int k = j - minx;
            t[curr][k] = t[curr][k - 1];
        }
        ret = max(ret, t[curr][maxx - minx]);
    }
    printf("%d\n", ret);
}

