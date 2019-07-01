/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Karty                                         *
 *   Autor:                Jan Kanty Milczek                             *
 *   Zlozonosc czasowa:    O(n + m log n)                                *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#define F first
#define S second
using namespace std;

typedef pair<int, int> PII;

const int INF = 1000000001;

int n, m;
int karty[(1 << 18)][2];
bool drz[1 << 19][2][2];
int brzeg[1 << 19];
int rozmiar = 1;

void aktualizuj(int x) {
    int ls = 2 * x;
    int ps = 2 * x + 1;
    int lk = (brzeg[ls] + brzeg[ps]) / 2;
    int pk = lk + 1;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            drz[x][i][j] = false;
            for (int k = 0; k < 2; ++k)
                for (int l = 0; l < 2; ++l)
                    if (drz[ls][i][k] && karty[lk][k] <= karty[pk][l] && drz[ps][l][j])
                        drz[x][i][j] = true;
        }
}

void rebuild(int x) {
    x += rozmiar;
    while (x != 1) {
        x >>= 1;
        aktualizuj(x);
    }
}

void cpy(int *x, int *y) {
    y[0] = x[0];
    y[1] = x[1];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", karty[i], karty[i] + 1);
        if (karty[i][0] > karty[i][1])
            swap(karty[i][0], karty[i][1]);
    }
    while (rozmiar < n)
        rozmiar <<= 1;
    while (n < rozmiar) {
        karty[n][0] = karty[n][1] = INF;
        ++n;
    }
    for (int i = rozmiar + n - 1; i >= rozmiar; --i) {
        brzeg[i] = i - rozmiar;
        for (int w = 0; w < 2; ++w)
            drz[i][w][w] = true;
    }
    for (int i = rozmiar - 1; i > 0; --i) {
        if (i % 2)
            brzeg[i] = brzeg[2 * i + 1];
        else
            brzeg[i] = brzeg[2 * i];
        aktualizuj(i);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x;
        --y;
        int tmp[2];
        cpy(karty[x], tmp);
        cpy(karty[y], karty[x]);
        rebuild(x);
        cpy(tmp, karty[y]);
        rebuild(y);
        if (drz[1][0][1])
            printf("TAK\n");
        else
            printf("NIE\n");
    }
}
