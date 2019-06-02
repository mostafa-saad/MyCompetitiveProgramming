/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Zaladunek                                     *
 *   Autor:                Pawel Parys                                   *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Heurystyka: przegladamy kolejne chwile czasu  *
 *                         i gdy tylko jakis pociag w A lub B moze       *
 *                         wyruszyc na trase, to rusza (gdy tor jest     *
 *                         wolny, a pociagi stoja i w A, i w B, to rusza *
 *                         ten z A).                                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

#define REP(a,n) for (int a = 0; a<(n); ++a)

using namespace std;

typedef long long LL;

///////////////

#define MAXN 1000000

int N;
LL S; // dla pewnosci robimy LL
int poj[MAXN]; // kiedy pojawia sie pociag (dane z wejscia)

int main() {
    scanf("%d%lld", &N, &S);
    REP(a, N) {
        scanf("%d", poj+a);
        if (a && poj[a]<=poj[a-1])
            poj[a] = poj[a-1]+1; // jak wiele pojawia sie w tej samej chwili, to przesuwamy na pozniej (i tak moga odjezdzac tylko po jednym)
    }
    int ile_w_b = 0;
    LL czas_w_b = 0; // kiedy najwczesniej cos moze odjechac z B
    LL czas_w_a = 0; // kiedy najwczesniej cos moze odjechac z A
    REP(a, N) {
        if (czas_w_b<poj[a] && ile_w_b) {
            ile_w_b = 0;
            czas_w_a = czas_w_b+S;
        }
        LL odj = max(czas_w_a, (LL)poj[a]);
        czas_w_b = odj+S;
        ++ile_w_b;
        czas_w_a = odj+1;
    }
    printf("%lld\n", czas_w_b+S+ile_w_b-1);
}
