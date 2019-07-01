/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Bajtokomputer                                 *
 *   Autor:                Maciej Matraszek                              *
 *   Zlozonosc czasowa:    O(n^3 log n)                                  *
 *   Zlozonosc pamieciowa: O(n^3)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Poprzez programowanie dynamiczne dla kazdej   *
 *                         trojki (liczba -1, liczba 0, liczba 1)        *
 *                         reprezentujacej prefiks obliczany jest wynik  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
const int INFI = 1000000005;
typedef pair<int, int> PII;
typedef pair<int, PII> PIII;
typedef vector<int> VI;
typedef long long LL;

const int MAXN = 1000*1000+9;
int DATA[MAXN];
int N;
map<PIII, int> M;

// Majac prefiks '-1'*l_1 + '0'*l0 + '1'*l1, ile trzeba wykonac ruchow,
// zeby dokonczyc do poprawnego ciagu.
int licz(int l_1, int l0, int l1) {
    int n = l_1 + l0 + l1;
    PIII p = PIII(l_1, PII(l0, l1));
    if (M.count(p))
        return M[p];
    if (n >= N)
        return 0;

    VI moz;
    moz.push_back(INFI);
    switch(DATA[n]) {
    case -1:
        // -1-1 -> -1-1-1
        if (!l0 && !l1) moz.push_back(licz(l_1+1,0,0));
        // -1-1?? -> -1-1-1-1-1
        if (l_1) moz.push_back(licz(l_1+l0+l1+1,0,0)+l0+2*l1);
        // -1-1?1 -> -1-1?11
        if (l1) moz.push_back(licz(l_1,l0,l1+1)+2);
        break;
    case 0:
        // -10 -> -100 / -1 -> -10
        if (!l1) moz.push_back(licz(l_1,l0+1,0));
        // ??1 -> ??11
        if (l1) moz.push_back(licz(l_1,l0,l1+1)+1);
        // -1??1 -> -1-1-100
        if (l1 && l_1) moz.push_back(licz(l_1+l0+l1-1,2,0)+l0+2*l1-1);
        break;
    case 1:
//            // -1?? -> -1-1-10
//            if (l_1) moz.push_back(licz(l_1+l0+l1,1,0)+l0+2*l1+1);
        // ?? -> ??1
        moz.push_back(licz(l_1,l0,l1+1));
        break;
    }
    LL wyn = *min_element(moz.begin(), moz.end());
    M[p] = wyn;
    return wyn;
}

int main() {
    scanf("%d", &N);
    for(int i = 0; i < N; ++i)
        scanf("%d", DATA+i);
    int wyn = licz(0,0,0);
    if (wyn == INFI)
        puts("BRAK");
    else
        printf("%d\n", wyn);
}
