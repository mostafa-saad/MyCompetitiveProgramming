#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int N;
int l[10003], r[10003], h[10003], maxh[1003];

char slika[1003][1003];

int main(void) {

    memset(slika, '.', sizeof slika);

    scanf("%d", &N);
    for (int i = 0; i < N; ++i){
        scanf("%d%d%d", &l[i], &r[i], &h[i]);
        --r[i];
    }

    int opseg = 0, lo = -1, hi = -1, maxvis = 0;
    for (int i = 1; i <= 1000; ++i) {

        for (int j = 0; j < N; ++j) {
            if (l[j] <= i && r[j] >= i) maxh[i] = max(maxh[i], h[j]);
        }
    
        opseg += abs(maxh[i] - maxh[i - 1]) + (maxh[i] != 0);
    
        int _lo = min(maxh[i], maxh[i - 1]), _hi = max(maxh[i], maxh[i - 1]);
        for (int j = _lo; j <= _hi; ++j) slika[j][i - (maxh[i] < maxh[i - 1])] = '#';
    
        slika[maxh[i]][i] = '#';
        slika[0][i] = slika[0][i - 1] = '*';

        if (maxh[i] > 0) {
            if (lo == -1) lo = i;
            hi = i;
        }

        maxvis = max(maxvis, maxh[i]);

    }

    printf("%d\n", opseg);
    for (int i = maxvis; i >= 0; --i) {
        for (int j = lo; j <= hi; ++j) printf("%c", slika[i][j]);
        printf("\n");
    }

    return 0;

}
