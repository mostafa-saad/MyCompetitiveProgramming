#include <cstdio>
using namespace std;

const int NN = 500000;
const int MM = 650;
int a[NN], b[NN];
int k[MM + 1][MM + 1];
int s[MM + 1][MM + 1];

int zbroj(int p, int q, int P, int Q) {
    if (P < 0 || Q < 0)
        return 0;
    int ret = s[P][Q];
    if (p > 0)
        ret -= s[p - 1][Q];
    if (q > 0)
        ret -= s[P][q - 1];
    if (p > 0 && q > 0)
        ret += s[p - 1][q - 1];
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", a+i, b+i);
        ++k[a[i]][b[i]];
    }
    for (int i = 0; i <= MM; ++i)
        for (int j = 0; j <= MM; ++j) {
            s[i][j] = k[i][j];
            if (i > 0)
                s[i][j] += s[i - 1][j];
            if (j > 0)
                s[i][j] += s[i][j - 1];
            if (i > 0 && j > 0)
                s[i][j] -= s[i - 1][j - 1];
        }

    for (int i = 0; i < n; ++i) {
        printf("%d ", zbroj(a[i] + 1, b[i] + 1, MM, MM) + 1);
        printf("%d\n", n - zbroj(0, 0, a[i] - 1, b[i] - 1) -
                k[0][b[i]] * (a[i] == MM) - k[a[i]][0] * (b[i] == MM));
    }
}
