/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Dookola swiata                                *
 *   Autor:                Jan Kanty Milczek                             *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Program liczacy wynik dla c (tu: c=10)        *
 *                         punktow startowych, z ktorych da sie wykonac  *
 *                         najdluzsze skoki (wg. dlugosci, a nie liczby  *
 *                         lotnisk).                                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <queue>

using namespace std;

const int MaxN = 1000000;

int n, l[MaxN], s, oile[MaxN];
typedef priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > kolejka;
kolejka best;

int lmod(int x) {
    while (x >= n)
        x -= n;
    return x;
}

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 0; i < n; ++i)
        scanf("%d", l + i);
    while (s--) {
        int d;
        scanf("%d", &d);
        int j = 0, sum = 0;
        bool nie = false;
        for (int i = 0; i < n; ++i) {
            while (sum + l[lmod(j)] <= d) {
                sum += l[lmod(j)];
                ++j;
            }
            best.push(make_pair(sum, i));
            if (best.size() > 10)
                best.pop();
            oile[i] = j - i;
            if (oile[i] == 0)
                nie = true;
            sum -= l[i];
        }
        if (nie) {
            printf("NIE\n");
            continue;
        }
        int Wynik = 2000000000;
        while (!best.empty()) {
            int start = best.top().second;
            best.pop();
            int wynik = 0, gdzie = start;
            while (gdzie < start + n) {
                ++wynik;
                gdzie += oile[lmod(gdzie)];
            }
            if (wynik < Wynik)
                Wynik = wynik;
        }
        printf("%d\n", Wynik);
    }
}
