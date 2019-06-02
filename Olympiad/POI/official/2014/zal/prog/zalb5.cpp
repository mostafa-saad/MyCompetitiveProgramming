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
 *                         koliduje to z zadnymi przejazdami z A do B    *
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
    LL czas_w_b = 0; // kiedy wszystkie rozwazone wczesniej pociagi dojada do B
    REP(a, N) {
        ile_w_b -= min((LL)ile_w_b, max(0LL, poj[a]-S-czas_w_b+1)); // tyle pociagow moze wrocic zanim sie pojawie
        ++ile_w_b;
        czas_w_b = poj[a]+S;
    }
    printf("%lld\n", czas_w_b+S+ile_w_b-1);
}
