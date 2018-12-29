/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Inspektor                                     *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O((n + m) log m)                              *
 *   Zlozonosc pamieciowa: O(m)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cassert>
#include <iostream>
using namespace std;

const int MAXM = 100000; // maksymalna liczba zeznan

int T[MAXM + 1]; // moment, ktorego dotyczy i-te zeznanie
int K[MAXM + 1]; // informatyk, ktory je zlozyl
int I[MAXM + 1]; // ile osob bylo wowczas w biurze oprocz niego

int pierwsze[MAXM + 1]; // moment, w ktorym i-ty informatyk zlozyl pierwsze zeznanie
int ostatnie[MAXM + 1]; // moment, w ktorym i-ty informatyk zlozyl ostatnie zeznanie
int przychodza[MAXM + 1]; // liczba informatykow, ktorzy zlozyli swoje pierwsze zeznanie w chwili i
int wychodza[MAXM + 1]; // liczba informatykow, ktorzy zlozyli swoje ostatnie zeznanie w chwili i
int X[MAXM + 1]; // ilu informatykow jest w biurze wedlug zeznan w i-tej chwili


int main() {
    std::ios_base::sync_with_stdio(0);
    int tests;
    cin >> tests;
    for(int test = 1; test <= tests; test++) {

        // wczytywanie danych
        int N; // liczba informatykow
        int M; // liczba zeznan
        cin >> N >> M;
        for(int i = 1; i <= M; i++)
            cin >> T[i] >> K[i] >> I[i];

        int l = 1, r = M; //wynik znajduje sie w przedziale [l, r]
        while(r > l) {
            int q = (l + r + 1) / 2;

            bool ok = true; // czy zeznania 1,..,q moga byc prawdziwe?

            // czyszczenie tablic
            for(int i = 1; i <=  M; i++) {
                przychodza[i] = 0;
                wychodza[i] = 0;
                pierwsze[i] = M + 1;
                ostatnie[i] = 0;
                X[i] = 0;
            }

            //liczenie tablic przychodza i wychodza
            for(int i = 1; i <= q; i++) {
                pierwsze[K[i]] = min(pierwsze[K[i]], T[i]);
                ostatnie[K[i]] = max(ostatnie[K[i]], T[i]);
            }
            for(int i = 1; i <= N; i++)
                if(ostatnie[i] != 0) {
                    przychodza[pierwsze[i]]++;
                    wychodza[ostatnie[i]]++;
                }

            // liczenie tablicy ilu
            for(int i = 1; i <= q; i++)
                if(X[T[i]] != 0 && X[T[i]] != I[i] + 1)
                    ok = false; // sprzeczne zeznania
                else
                    X[T[i]] = I[i] + 1;

            // reszta rozwiazania
            int spi = N; // ilu informatykow nie przyszlo jeszcze do pracy
            int jest = 0; // ilu informatykow jest na pewno w biurze
            int przedwczesnie = 0; // ilu przyszlo do pracy przedwczesnie
            int moze = 0; // ilu informatykow jest, ale zlozylo juz swoje ostatnie zeznanie i moze wyjsc
            for(int i = 1; i <= M; i++)
                if(X[i] != 0 && ok) { // jesli jakiekolwiek zeznanie dotyczy chwili i

                    // pierwsze zeznania
                    for(int j = 0; j < przychodza[i]; j++) {
                        if(przedwczesnie > 0)
                            przedwczesnie--;
                        else
                            spi--;
                        jest++;
                    }

                    // musi byc X[i] informatykow
                    while(X[i] > jest + przedwczesnie + moze) {
                        przedwczesnie++;
                        spi--;
                    }
                    if(X[i] < jest)
                        ok = false;
                    else while(X[i] < jest + przedwczesnie + moze) {
                            if(moze > 0)
                                moze--;
                            else
                                przedwczesnie--;
                        }
                    assert(!ok || X[i] == jest + przedwczesnie + moze);
                    assert(jest >= 0);
                    assert(przedwczesnie >= 0);
                    assert(moze >= 0);

                    // ostatnie zeznania
                    for(int j = 0; j < wychodza[i]; j++) {
                        jest--;
                        moze++;
                    }

                    if(spi < 0)
                        ok = false;
                }

            if(ok)
                l = q;
            else
                r = q - 1;
        }

        //wypisanie wyniku
        cout << l << endl;
    }

    return 0;
}

