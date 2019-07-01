/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Jacek Tomasiewicz                                *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#define wartosc first
#define pozycja second
#define MAX_N (1<<20)
using namespace std;

const int INF = 1100000000;
int x[MAX_N], y[MAX_N];
deque<pair<int, int> > L;

void dodaj(int wartosc, int pozycja) {
    while (!L.empty() && L.front().wartosc <= wartosc)
        L.pop_front();
    L.push_front(make_pair(wartosc, pozycja));
}
void usun(int pozycja) {
    if (L.back().pozycja <= pozycja)
        L.pop_back();
}
int maksimum() {
    if (L.empty())
        return -INF;
    return L.back().wartosc;
}

int main()
{
    int n, wynik=0;  
    int pp = scanf("%i", &n);
    for(int i = 1; i <= n; i++)
        pp = scanf("%i%i", &x[i], &y[i]);

    int j=1;
    for(int i = 1; i <= n; i++){
        while(j <= n && maksimum() <= y[j]) {
            dodaj(x[j], j);
            j++;
        }
        wynik = max(wynik, j - i);
        usun(i);
    }
    printf("%i\n", wynik);
    return 0;
}
