/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Autor:                Karol Pokorski                                *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Odgadywanie kandydata na podstawie malej      *
 *                         probki. Jesli przedzial jest krotki, dokonuje *
 *                         sprawdzenia brutalnie. W przeciwnym wypadku   *
 *                         nie sprawdza.                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
const int RANDOM_CHECK = 101;
const int THRESHOLD = 201;

int t[MAXN], selCheck[RANDOM_CHECK+2];

int main() {
    int n, m;

    scanf("%d%d", &n, &m);
    srand(3*n+2*m);
    for (int i = 0; i < n; i++)
        scanf("%d", &t[i]);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--;
        b--;

        for (int j = 0; j < RANDOM_CHECK; j++) {
            int x = a+rand()%(b-a+1);
            selCheck[j] = t[x];
        }

        sort(selCheck, selCheck+RANDOM_CHECK);

        int maxIdx = selCheck[0], maxOccur = 1, curOccur = 1;
        for (int j = 1; j < RANDOM_CHECK; j++) {
            if (selCheck[j] == selCheck[j-1]) {
                curOccur++;
                if (curOccur > maxOccur) {
                    maxIdx = selCheck[j];
                    maxOccur = curOccur;
                }
            }
            else
                curOccur = 1;
        }
        maxOccur = max(maxOccur, curOccur);

        int elemChecked = RANDOM_CHECK;

        if (b-a+1 < THRESHOLD) {
            maxOccur = 0;
            elemChecked = b-a+1;

            for (int i = a; i <= b; i++)
                maxOccur += (t[i] == maxIdx);
        }

        if (maxOccur > elemChecked/2)
            printf("%d\n", maxIdx);
        else
            printf("0\n");
    }

    return 0;
}
