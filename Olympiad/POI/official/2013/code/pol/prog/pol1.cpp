/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Jan Kanty Milczek                             *
 *   Zlozonosc czasowa:    O(n*sqrt(n))                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> kraw[250001];
bool odw[250001];
int rozmiar[250001];

long long policz_plecak_bro(int ile, int *rozm) {
    sort(rozm, rozm + ile);
    rozm[ile] = 0;
    int jaki = rozm[0], ilosc = 1;

    int magia[n];
    fill(magia, magia + n, 1000000000);
    magia[0] = 0;

    for (int i = 1; i <= ile; ++i)
        if (rozm[i] == jaki)
            ++ilosc;
        else {
            for (int k = 0; k < n; ++k)
                if (magia[k] != 1000000000)
                    magia[k] = 0;
            for (int k = 0; k < n - jaki; ++k)
                if (magia[k] < ilosc && magia[k + jaki] > magia[k] + 1)
                    magia[k + jaki] = magia[k] + 1;
            jaki = rozm[i];
            ilosc = 1;
        }
    for (int i = (n - 1) / 2;; --i)
        if (magia[i] != 1000000000)
            return static_cast<long long>(i) * (n - 1 - i);
}

void dfs(int x) {
    odw[x] = true;
    rozmiar[x] = 1;
    for (vector<int>::iterator it = kraw[x].begin(); it != kraw[x].end(); ++it)
        if (!odw[*it]) {
            dfs(*it);
            rozmiar[x] += rozmiar[*it];
        }
}

long long podaj_wynik_bro(int x) {
    fill(odw, odw + n + 1, false);
    dfs(x);

    long long wynik = 0LL;
    for (int i = 1; i <= n; ++i)
        wynik += static_cast<long long>(rozmiar[i] - 1);

    int rozm[kraw[x].size() + 1];
    for (int i = 0; i < (int)kraw[x].size(); ++i)
        rozm[i] = rozmiar[kraw[x][i]];

    return wynik + policz_plecak_bro(kraw[x].size(), rozm);
}

long long znajdz_centroid_i_podaj_wynik_bro(int x) {
    odw[x] = true;
    rozmiar[x] = 1;

    int tenwgore = n - 1;
    bool centroid = true;
    for (vector<int>::iterator it = kraw[x].begin(); it != kraw[x].end(); ++it)
        if (!odw[*it]) {
            long long tmp = znajdz_centroid_i_podaj_wynik_bro(*it);
            if (tmp)
                return tmp;
            rozmiar[x] += rozmiar[*it];
            if (rozmiar[*it] > n / 2)
                centroid = false;
            tenwgore -= rozmiar[*it];
        }
    if (tenwgore > n / 2)
        centroid = false;

    if (centroid)
        return podaj_wynik_bro(x);
    else
        return 0LL;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int w1, w2;
        scanf("%d%d", &w1, &w2);
        kraw[w1].push_back(w2);
        kraw[w2].push_back(w1);
    }
    printf("%d %Ld\n", n - 1, znajdz_centroid_i_podaj_wynik_bro(1));
}
