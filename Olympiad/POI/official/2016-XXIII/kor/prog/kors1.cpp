/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Korale                                             *
 *   Autor programu:       Karol Pokorski                                     *
 *   Zlozonosc czasowa:    O(2^n)                                             *
 *   Opis:                 Rozwiazanie naiwne                                 *
 *                                                                            *
 *****************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int LL;

const int MAXN = 62;

int n, k;
LL T[1000005];
vector<pair<LL,LL> > result;

void Go(int pos, LL subsetSum, LL subsetBitmask) {
    if (pos == n) {
        result.push_back(make_pair(subsetSum, subsetBitmask));
        return;
    }
    Go(pos+1, subsetSum, subsetBitmask);
    Go(pos+1, subsetSum + T[pos], subsetBitmask | (1LL << (MAXN - pos)));
}

int main() {
    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; i++)
        scanf("%Ld", &T[i]);

    Go(0, 0LL, 0LL);

    sort(result.begin(), result.end(),
    [](const pair<LL,LL>& a, const pair<LL,LL>& b) -> bool {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });

    LL resultSubsetSum = result[k-1].first;
    LL resultSubsetBitmask = result[k-1].second;

    printf("%Ld\n", resultSubsetSum);
    bool printed = false;
    for (int i = 0; i < n; i++) {
        if ((resultSubsetBitmask & (1LL << (MAXN - i))) != 0LL) {
            if (printed) printf(" ");
            printed = true;
            printf("%d", i+1);
        }
    }
    printf("\n");
    
    return 0;
}
