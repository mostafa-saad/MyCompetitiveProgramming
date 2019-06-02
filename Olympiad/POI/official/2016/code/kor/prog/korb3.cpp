/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Korale                                             *
 *   Autor programu:       Karol Pokorski                                     *
 *   Opis:                 Rozwiazanie bledne                                 *
 *                         wzorcowe bez long longow                           *
 *****************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;

struct DpInfo {
    int sum;
    int last;
    int vecElem;
    DpInfo() {};
    DpInfo(int sum, int last, int vecElem):
        sum(sum), last(last), vecElem(vecElem) {};
};

int n, k, T[MAXN];
vector<vector<DpInfo> > R;

int main() {
    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; i++)
        scanf("%d", &T[i]);

    R.resize(n+1);
    R[n].push_back(DpInfo(0, n+1, -1));

    for (int i = n-1; i >= 0; i--) {
        R.push_back(vector<DpInfo>());
        R[i].resize(min(2*(int)R[i+1].size(), k));

        int pos1 = 0, pos2 = 0, pos3 = 0;
        while (pos3 < k) {
            if (pos1 < (int)R[i+1].size()) {
                if (R[i+1][pos1].sum < R[i+1][pos2].sum+T[i]) {
                    R[i][pos3] = R[i+1][pos1];
                    pos1++;
                }
                else {
                    R[i][pos3] = DpInfo(R[i+1][pos2].sum+T[i], i+1, pos2);
                    pos2++;
                }
            }
            else if (pos2 < (int)R[i+1].size()) {
                R[i][pos3] = DpInfo(R[i+1][pos2].sum+T[i], i+1, pos2);
                pos2++;
            }
            else
                break;
            pos3++;
        }
    }

    printf("%d\n", R[0][k-1].sum);
    vector<int> result;
    int curVec = R[0][k-1].last;
    int curElem = R[0][k-1].vecElem;
    while (curVec <= n) {
        const DpInfo& dpi = R[curVec][curElem];
        result.push_back(curVec);
        curVec = dpi.last;
        curElem = dpi.vecElem;
    }

    for (int i = 0; i < (int)result.size(); i++) {
        if (i > 0) printf(" ");
        printf("%d", result[i]);
    }
    printf("\n");

    return 0;
}
