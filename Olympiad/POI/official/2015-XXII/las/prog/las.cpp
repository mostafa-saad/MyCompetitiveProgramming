/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Lasuchy                                            *
 *   Autor programu:       Piotr Smulewicz                                    *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <vector>
#include <iostream>
std::vector<int> torty;
int n, pom;
void zmien(std::vector<int> &wynik, int poz) {
    int next = poz % n + 1;
    int prew = (poz + n - 2) % n + 1;
    int war_next = torty[next] * (1 + (wynik[next] != next));
    int war_prew = torty[poz] * (1 + (wynik[prew] == prew));
    if (war_next < war_prew && wynik[poz] != poz) {
        wynik[poz] = poz;
    }
}
int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin >> n;
    std::vector<int> wynik(n + 1);
    torty.push_back(-1);
    for (int i = 1; i <= n; i++) {
        std::cin >> pom;
        torty.push_back(pom);
        wynik[i] = i % n + 1;
    }
    for (int k = 0;k<2;k++)
    for (int i = 1; i <= n; i++) {
        zmien(wynik, i);
    }
    for (int k = 0;k<2;k++)
    for (int i = n; i >= 1; i--) {
        zmien(wynik, i);
    }
    for (int i = 1; i <= n; i++) {
        if(i != 1)
          std::cout << " ";
        std::cout << wynik[i];
    }
    std::cout << "\n";
    return 0;
}
