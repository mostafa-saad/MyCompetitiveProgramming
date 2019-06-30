/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klo4.cpp                                         *
 *   Autor:             Maciej Andrejczuk                                *
 *   Opis:              Rozwiazanie weryfikujace.                        *
 *   Zlozonosc czasowa: O(n * m)                                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
#define MAXN 1000000

int t[MAXN + 3];
LL a[MAXN + 3];  // sumy częściowe
vector<int> lewy, prawy;

int solve(int n, int k)
{
    lewy.push_back(0);
    for (int i = 1; i <= n; i++) {
        a[i] = a[i - 1] + t[i] - k;
        if (a[i] < a[lewy.back()])
            lewy.push_back(i);
    }
    prawy.push_back(n);
    for (int i = n - 1; i >= 1; i--) {
        if (a[i] > a[prawy.back()])
            prawy.push_back(i);
    }
    int p = 0;
    int ret = 0;
    for (int i = (int)prawy.size() - 1; i >= 0; i--) {
        LL q = a[prawy[i]];
        while (a[lewy[p]] > q) p++;
        ret = max(ret, prawy[i] - lewy[p]);
    }
    lewy.clear();
    prawy.clear();
    return ret;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", t + i);
    }
    for (int i = 0; i < m; i++) {
        int k;
        scanf("%d", &k);
        printf("%d ", solve(n, k));
    }
    printf("\n");
}

