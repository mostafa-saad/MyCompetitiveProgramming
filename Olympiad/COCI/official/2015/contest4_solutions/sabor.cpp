#include <cstdio>
#include <cstring>
using namespace std;

const int NN = 200000;
char stranka[NN + 1];
int neprijatelji[NN][6];
int br_nepr_kolega[NN];

void prebaci(int k) {
    for (int* nepr = neprijatelji[k]; *nepr != -1; ++nepr)
        if (stranka[*nepr] == stranka[k]) {
            --br_nepr_kolega[k];
            --br_nepr_kolega[*nepr];
        }
        else {
            ++br_nepr_kolega[k];
            ++br_nepr_kolega[*nepr];
        }
    stranka[k] = 'A' + 'B' - stranka[k];
    for (int* nepr = neprijatelji[k]; *nepr != -1; ++nepr)
        if (br_nepr_kolega[*nepr] > 2)
            prebaci(*nepr);
}

int main () {
    memset(neprijatelji, -1, sizeof(neprijatelji));

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        stranka[i] = 'A';

    for (int dan = 0; dan < 5; ++dan) {
        int p;
        scanf("%d", &p);
        while (p--) {
            int k, l;
            scanf("%d%d", &k, &l);
            --k; --l;
            neprijatelji[k][br_nepr_kolega[k]++] = l;
            neprijatelji[l][br_nepr_kolega[l]++] = k;
        }
    }

    for (int i = 0; i < n; ++i)
        if (br_nepr_kolega[i] > 2)
            prebaci(i);

    printf("%s\n", stranka);
}
