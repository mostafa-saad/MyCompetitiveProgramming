/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Zaladunek                                     *
 *   Autor:                Pawel Parys                                   *
 *   Zlozonosc czasowa:    O(n * log(s+t_n))                             *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie alternatywne                      *
 *                         Wyszukujemy binarnie poprawny wynik (czas     *
 *                         przejazdu). Gdy wynik jest ustalony (aby      *
 *                         sprawdzic czy tyle czasu wystarczy)           *
 *                         przydzielamy pociagi zachlannie,              *
 *                         od konca czasu.                               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

#define REP(a,n) for (int a = 0; a<(n); ++a)

using namespace std;

typedef long long LL;

///////////////

#define MAXN 1000000

int N;
LL S; // dla pewnosci robimy LL
int poj[MAXN]; // kiedy pojawia sie pociag (dane z wejscia)

bool sprawdz(LL czas) { // czy da sie przejechac w takim czasie
    LL cur = N-1;
    while (cur>=0) {
        LL ile = czas-2*S-poj[cur]+1; // ile zdazy przejechac, gdy ostatni startuje w "poj[cur]" i wraca w "czas"
        if (ile<=0)
            return false;
        czas = poj[cur]-ile+1;
        cur -= ile;
    }
    return true;
}

int main() {
    scanf("%d%lld", &N, &S);
    REP(a, N) {
        scanf("%d", poj+a);
        if (a && poj[a]<=poj[a-1])
            poj[a] = poj[a-1]+1; // jak wiele pojawia sie w tej samej chwili, to przesuwamy na pozniej (i tak moga odjezdzac tylko po jednym)
    }
    LL L = poj[N-1], H = poj[N-1]+2*S+N; // w takim czasie na pewno sie da (H) / nie da (L)
    while (H-L>1) {
        LL M = (L+H)/2;
        (sprawdz(M) ? H : L) = M;
    }
    printf("%lld\n", H);
}
