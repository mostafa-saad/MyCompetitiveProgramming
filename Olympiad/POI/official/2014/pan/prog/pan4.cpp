/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Panele sloneczne                              *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n sqrt m)                                   *
 *   Zlozonosc pamieciowa: O(1)                                          *
 *   Opis:                 Rozwiazanie alternatywne                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

struct Zapytanie {
    int a, b, c, d;
};

pair<int, int> zmniejsz_przedzial(int a, int b, int l) {
    return make_pair((a + l - 1) / l, b / l);
}

bool zgodne(int k, Zapytanie &P) {
    pair<int, int> p1 = zmniejsz_przedzial(P.a, P.b, k);
    pair<int, int> p2 = zmniejsz_przedzial(P.c, P.d, k);
    return p1.first <= p1.second && p2.first <= p2.second;
}

int daj_wynik(Zapytanie &P) {
    int wynik = 0;
    int m = max(P.b, P.d);
    // Przypadek 1. wynik <= sqrt(m)
    for (int k = 1; k * k <= m; k++) {
        if (zgodne(k, P)) {
            wynik = k;
        }
    }
    // Przypadek 2. wynik >= sqrt(m)
    int x = 1, y = 1;
    pair<int, int> Ix(P.a, P.b), Iy(P.c, P.d);
    while (x * x <= m && y * y <= m) {
        if (min(Ix.second, Iy.second) >= max(Ix.first, Iy.first)) {
            wynik = max(wynik, min(Ix.second, Iy.second));
            break;
        } else if(Ix.second < Iy.first) {
            do {
                y++;
                Iy = zmniejsz_przedzial(P.c, P.d, y);
            } while (y * y <= m && Iy.first > Iy.second);
        } else {
            do {
                x++;
                Ix = zmniejsz_przedzial(P.a, P.b, x);
            } while (x * x <= m && Ix.first > Ix.second);
        }
    }
    return wynik;
}


int main() {
    int n, m;
    Zapytanie P;
    scanf("%d", &n);

    for (int query_num = 0; query_num < n; query_num++) {
        scanf("%d%d%d%d", &P.a, &P.b, &P.c, &P.d);
        printf("%d\n", daj_wynik(P));
    }

    return 0;
}
