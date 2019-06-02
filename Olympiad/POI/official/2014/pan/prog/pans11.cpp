/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Panele sloneczne                              *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n sqrt m log m)                             *
 *   Zlozonosc pamieciowa: O(sqrt m)                                     *
 *   Opis:                 Rozwiazanie wolniejsze                        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>

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
    vector< pair<int, int> > czas;
    for (int l = 1; l * l <= m; l++) {
        pair<int, int> Ix = zmniejsz_przedzial(P.a, P.b, l);
        pair<int, int> Iy = zmniejsz_przedzial(P.c, P.d, l);
        if (Ix.first <= Ix.second) {
            czas.push_back(make_pair(Ix.first, 0));
            czas.push_back(make_pair(Ix.second, 2));
        }
        if (Iy.first <= Iy.second) {
            czas.push_back(make_pair(Iy.first, 1));
            czas.push_back(make_pair(Iy.second, 3));
        }
    }
    sort(czas.begin(), czas.end());
    int otwarte_x = 0, otwarte_y = 0;
    while (!czas.empty()) {
        pair<int, int> wyd = czas.back();
        czas.pop_back();
        switch (wyd.second) {
            case 0:
                otwarte_x--;
            break;
            case 1:
                otwarte_y--;
            break;
            case 2:
                otwarte_x++;
                if (otwarte_y > 0) {
                    wynik = max(wynik, wyd.first);
                }
            break;
            case 3:
                otwarte_y++;
                if (otwarte_x > 0) {
                    wynik = max(wynik, wyd.first);
                }
            break;
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
