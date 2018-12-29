/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Bajtokomputer                                 *
 *   Autor:                Maciej Matraszek                              *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Heurystyka                                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <functional>
#include <cassert>
using namespace std;
const int INFI = 1000000005;

const int MAXN = 1000*1000+9;
int DATA[MAXN];
int N;

int odp(int wyn) {
    if (wyn == INFI)
        puts("BRAK");
    else
        printf("%d\n", wyn);
    exit(0);
}

int ile(int od, int czego) {
    int wyn = 0;
    for (int i = od; i < N; ++i)
        wyn += DATA[i] == czego;
    return wyn;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", DATA+i);
    if (DATA[0] == 0) {
        int p = adjacent_find(DATA, DATA+N, greater<int>()) - DATA;
        if(DATA[p] != -1)
            odp(ile(p, -1)*2 + ile(p, 0));
        else
            odp(INFI);
    } else if (DATA[0] == 1) {
        odp(ile(0, -1)*2 + ile(0, 0));
    } else {
        reverse(DATA, DATA+N);
        int p = adjacent_find(DATA, DATA+N, less<int>()) - DATA;
        odp(ile(p, 1)*2 + ile(p, 0));
    }
    return 0;
}
