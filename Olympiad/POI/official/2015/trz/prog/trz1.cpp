/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Trzy wieze                                         *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/
#include <cstdio>
#include <cassert>
#include <algorithm>
const int MAXLEN = 1000000;

struct Diffrence {
    int d[3];
} triple[MAXLEN+1];

char str[MAXLEN+1];
int useful[8], usefulCount;

int bitcount(int t) {
    return __builtin_popcount(t);
}

bool different(int a, int b) {
    for (int i=0; i<3; i++)
        if (triple[a].d[i] == triple[b].d[i])
            return false;
    return true;
}

bool isUseful(int it) {
    if (usefulCount >= 8)
        return false;

    for (unsigned mask=1; mask<8; mask++) {
        int count = 0;
        for (int i=0; i<usefulCount; i++) {
            bool success = true;
            for (int t=0; t<3 && success; t++)
                if (mask & (1 << t)) {
                    if (triple[useful[i]].d[t] != triple[it].d[t])
                        success = false;
                }

            count += success;
        }
        
        int bits = bitcount(mask);
        if (bits == 1 && count >= 4)
            return false;
        else if (bits == 2 && count >= 2)
            return false;
        else if (bits == 3 && count >= 1)
            return false;
    }

    return true;
}

int sameLetterTower(const char* str, int n) {
    int it = 0, res = 0;
    while (it < n) {
        int letter = str[it], count = 0;
        while (it < n && str[it] == letter)
            count++, it++;
        res = std::max(res, count);
    }

    return res;
}

int solve(const char* str, int n) {
    int count[3] = { };
    for (int i=0; i<n; i++) {
        if (str[i] == 'B')
            count[0]++;
        else if (str[i] == 'C')
            count[1]++;
        else if (str[i] == 'S')
            count[2]++;

        triple[i+1].d[0] = count[0]-count[1];
        triple[i+1].d[1] = count[1]-count[2];
        triple[i+1].d[2] = count[0]-count[2];
    }
    
    int best = sameLetterTower(str, n);
    for (int i=0; i<=n; i++) {
        if (isUseful(i))
            useful[usefulCount++] = i;

        for (int j=0; j<usefulCount; j++)
            if (different(i, useful[j]))
                best = std::max(best, i-useful[j]);
    }
    
    return best;
}

int main() {
    int n;
    assert(scanf("%d%s", &n, str) == 2);
    printf("%d\n", solve(str, n));
}
