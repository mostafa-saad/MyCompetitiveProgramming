/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Zaladunek                                     *
 *   Autor:                Pawel Parys                                   *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Heurystyka: pociagi z A odjezdzaja od razu gdy*
 *                         sie pojawia, a z B odjezdzaja gdy tylko nie   *
 *                         koliduje to z zadnymi przejazdami z A do B.   *
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
    printf("%lld\n", poj[N-1]+2*S);
}
